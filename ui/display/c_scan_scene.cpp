#include "c_scan_scene.h"

#include <QWriteLocker>
#include <QDebug>
#include <QPainter>

#include <source/scan.h>
#include <device/device.h>



CscanScene::CscanScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent) :
    QGraphicsScene(parent),
    m_driving(DplSource::Scan::instance()->scan_axis()->driving()),
    m_scrolling(false),
    m_pixPerBeamRatio(DEFAULT_PIX_PER_BEAM),
    m_currentStart(0.0),
    m_currentEnd(0.0),
    m_size(width(), height()),
    m_image(NULL),
    m_redrawFlag(false),
    m_beamsShowedCount(0.0),
    m_source(TestStub::instance()->get_source()),
    m_group(grp),
    m_palette(palette)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

bool CscanScene::set_pix_per_beam(double ratio)
{
    QWriteLocker lock(&m_rwLock);

    if(ratio < 0.0) {
        return false;
    }

    m_pixPerBeamRatio = ratio;

    return true;
}

void CscanScene::set_size(const QSize &size)
{
    QWriteLocker lock(&m_rwLock);

    if((size.height() == m_size.height())
            && (size.width() == m_size.width())
            && (m_image != NULL))  {
        return;
    }

    m_size = size;

    if(m_image != NULL) {
        delete m_image;
        m_image = NULL;
    }

    qDebug() << "[" << __FUNCTION__ << "]" << " w = " << size.width() << " h " << size.height();

    m_image = new QImage(m_size, QImage::Format_Indexed8);
    m_image->setColorTable(m_palette->colors());
    m_image->fill(Qt::white);

    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());

    /* 根据最新的size以及当前显示的beam数，
     * 重新计算是否scroll */
    if(m_size.width() != 0
            && m_size.height() != 0
            && (!m_beamsPointer.isNull())) {

        check_scroll_window(size);
        m_redrawFlag = true;
    }

    qDebug() << "[" << __FUNCTION__ << "]" << " m_redrawFlag = " << m_redrawFlag;
}

void CscanScene::draw_vertical_beam()
{

}

bool CscanScene::redraw_vertical_beam()
{
    return false;
}


void CscanScene::calculate_common_properties(CscanScene::S_CommonProperties &commonProperties)
{
    commonProperties.ratio      = m_beamsPointer->point_qty() / (double)m_image->height(); /* 一个像素点代表多少个point */
    commonProperties.pixCount   = m_pixPerBeamRatio;
    commonProperties.maxIndex   = m_image->width() / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */
    commonProperties.align      = m_image->width() % (int)(m_pixPerBeamRatio + 0.5);

    if(commonProperties.align != 0) {
         commonProperties.maxIndex += 1;
    }

//    qDebug() << "[" << __FUNCTION__ << "]"
//             << " ratio = " << commonProperties.ratio
//             << " pixCount = " << commonProperties.pixCount
//             << " maxIndex = " << commonProperties.maxIndex
//             << " align = " << commonProperties.align
//             << " m_pixPerBeamRatio = " << m_pixPerBeamRatio;
}

void CscanScene::calculate_redraw_properties(CscanScene::S_CommonProperties &commonProperties, CscanScene::S_RedrawProperties &redrawProperites)
{
    /* index从0开始 */
    redrawProperites.currentFrameIndex  = m_beamsPointer->get(0)->index() / DplDevice::Device::instance()->total_beam_qty();
    redrawProperites.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();

    if(m_scrolling) {
        /* 滚动显示 */
        redrawProperites.redrawCount = commonProperties.maxIndex;
    } else {
        /* 未滚动显示 */
        redrawProperites.redrawCount = m_beamsShowedCount;
    }

    redrawProperites.beginShowIndex = redrawProperites.currentFrameIndex - redrawProperites.redrawCount + 1;
}

void CscanScene::set_vertical_image_data(int beamsShowedCount,
                                         const CscanScene::S_CommonProperties &commonProperties,
                                         const DplSource::BeamsPointer &beamsPointer)
{
//    qDebug() << "[" << __FUNCTION__ << "]"
//             << " m_image w = " << m_image->width()
//             << " h = " << m_image->height()
//             << " m_size w = " << m_size.width()
//             << " h = " << m_size.height();

    if((beamsShowedCount + 1) == commonProperties.maxIndex && (commonProperties.align != 0)) {
        /* 非对齐,最后一条beam */
        int offset =  commonProperties.pixCount - commonProperties.align;
        QImage tmp = m_image->copy(offset, 0, m_image->width(), m_image->height());
        m_image->swap(tmp);

        draw_c_scan_vertical_image_data(beamsShowedCount, commonProperties, LAST_BEAM, beamsPointer);

    } else {
        draw_c_scan_vertical_image_data(beamsShowedCount, commonProperties, NORMAL_BEAM, beamsPointer);
    }

}


void CscanScene::scroll_vertical_image(const CscanScene::S_CommonProperties &commonProperties,
                                       const DplSource::BeamsPointer &beamsPointer)
{
    QImage tmp = m_image->copy(commonProperties.pixCount, 0, m_image->width(), m_image->height());
    m_image->swap(tmp);

    draw_c_scan_vertical_image_data(0, commonProperties, LAST_BEAM, beamsPointer);
}


void CscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QWriteLocker lock(&m_rwLock);
    if(m_image != NULL) {
        painter->drawImage(rect, *m_image);
    }
}


void CscanScene::draw_c_scan_vertical_image_data(int beamsShowedCount,
                                                 const CscanScene::S_CommonProperties &commonProperties,
                                                 E_BEAM_TYPE type,
                                                 const DplSource::BeamsPointer &beamsPointer)
{
    double beamQty = beamsPointer->beam_qty();
    double perBeamSpace = m_image->height() / beamQty;

    int beginLine  = 0;
    int endLine    = 0;
    int targetLine = 0;

    for(int num = 0; num < beamQty; ++num) {

        beginLine = perBeamSpace * num + 0.5;
        endLine   = beginLine + perBeamSpace + 0.5;
        int drawLine = endLine - beginLine;

        double gateValue;
        if(!get_peak_value(beamsPointer, num, gateValue))
        {
            continue;
        }

        double gateValueTmp;
        get_peak_value(m_beamsPointer, num, gateValueTmp);

//        qDebug() << "[" << __FUNCTION__ << "]" << " gateValue = " << gateValue
//                 << " gateValueTmp = " << gateValueTmp
//                 << " drawLine = " << drawLine
//                 << " beamsShowedCount = " << beamsShowedCount;


        for(int offset = 0; offset < drawLine; ++offset) {

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                targetLine = beginLine + offset;

                if(targetLine >= m_image->height() || targetLine < 0) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " error target line = " << targetLine;
                    continue;
                }

                int pos;
                if(type == LAST_BEAM) {
                    pos = m_image->width() - 1 - j;
                } else {
                    int tmpPos = beamsShowedCount * commonProperties.pixCount;
                    pos = (int)(tmpPos + j);
                }

                quint8 *line    = (quint8*) m_image->scanLine(targetLine);

                if(pos >= m_image->width() || pos < 0) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " error pos = " << pos;
                    continue;
                }

                line[pos] = gateValue;
            }
        }
    }
}


bool CscanScene::get_peak_value(const DplSource::BeamsPointer &beamsPointer, int beamCount, double &gateValue)
{
    if(beamCount > beamsPointer->beam_qty()) {
        return false;
    }

   DplSource::BeamPointer beamPoint = beamsPointer->get(beamCount);

   if(beamPoint.isNull()) {
       return false;
   }

   switch (TestStub::instance()->get_source()) {
   case TestStub::SOURCE_A:
   {
       gateValue = beamPoint->gate_peak(DplSource::Beam::GATE_A);
       return true;
       break;
   }
   case TestStub::SOURCE_B:
   {
       gateValue = beamPoint->gate_peak(DplSource::Beam::GATE_B);
       return true;
       break;
   }
   case TestStub::SOURCE_T:
   {
       return get_source_peak_value(beamsPointer, beamCount, gateValue);
       break;
   }
   case TestStub::SOURCE_I:
   {
       if (m_group->ut_unit() == DplDevice::Group::Time) {
           gateValue = beamPoint->gate_peak_position(DplSource::Beam::GATE_I) / 1000.0;
       } else {
           gateValue = beamPoint->gate_peak_position(DplSource::Beam::GATE_I) * m_group->sample()->velocity() / 200000.0;
       }
       return true;

       break;
   }
   case TestStub::SOURCE_OFF:
   {
       return false;
       break;
   }
   default:
       return false;
       break;
   }


}

bool CscanScene::get_source_peak_value(const DplSource::BeamsPointer &beamsPointer, int beamCount, double &gateValue)
{
    TestStub::THICKNESS_SOURCE thicknessSourceType = TestStub::instance()->get_thickness_source();

    switch (thicknessSourceType) {
    case TestStub::A_POSITION:                      /* A^ */
    {
        get_gate_position(DplSource::Beam::GATE_A, beamsPointer, beamCount, gateValue);
        break;
    }
    case TestStub::A_POSITION_MINUS_I_POSITION:     /* A^ - I^ */
    case TestStub::A_POSITION_MINUS_I_AMPLITUDE:    /* A^ - I/ */
    {
        get_gate_position_distance(DplSource::Beam::GATE_A,
                                   DplSource::Beam::GATE_I,
                                   beamsPointer,
                                   beamCount,
                                   gateValue);
        break;
    }
    case TestStub::B_POSITION:                       /* B^ */
    {
        get_gate_position(DplSource::Beam::GATE_A,
                          beamsPointer,
                          beamCount,
                          gateValue);
        break;
    }
    case TestStub::B_POSITION_MINUS_I_POSITION:      /* B^ - I^*/
    case TestStub::B_POSITION_MINUS_I_AMPLITUDE:     /* B^ - I/ */
    {
        get_gate_position_distance(DplSource::Beam::GATE_B,
                                   DplSource::Beam::GATE_I,
                                   beamsPointer,
                                   beamCount,
                                   gateValue);
        break;
    }
    case TestStub::B_POSITION_MINUS_A_POSITION:      /* B^ - A^ */
    {
        get_gate_position_distance(DplSource::Beam::GATE_B,
                                   DplSource::Beam::GATE_A,
                                   beamsPointer,
                                   beamCount,
                                   gateValue);
        break;
    }
    case TestStub::I_POSITION:            /* I^ */
    case TestStub::I_AMPLITUDE:           /* I/ */
    {
        get_gate_position(DplSource::Beam::GATE_A, beamsPointer, beamCount, gateValue);
        break;
    }
    default:
        break;
    }
}

void CscanScene::get_gate_position(DplSource::Beam::GateType type,
                                   const DplSource::BeamsPointer &beamsPointer,
                                   int beamCount,
                                   double &gateValue)
{

}

void CscanScene::get_gate_position_distance(DplSource::Beam::GateType type1,
                                            DplSource::Beam::GateType type2,
                                            const DplSource::BeamsPointer &beamsPointer,
                                            int beamCount,
                                            double &gateValue)
{

}


void CscanScene::check_scroll_window(const QSize &oldSize)
{
    int newWidth = m_size.width();
    int oldWidth = oldSize.width();

    int newMaxIndex   = newWidth / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */

    /* size变小,同时已显示数超过最新size的最大显示数 */
    /* size变大，同时当前已为滚动状态 */
    if((oldWidth >= newWidth && m_beamsShowedCount > newMaxIndex)
            || (oldWidth <= newWidth && m_scrolling && m_beamsShowedCount > newMaxIndex)) {
        /* 滚动 */
        m_scrolling = true;
    } else {
        m_scrolling = false;
    }
}

bool CscanScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    QWriteLocker lock(&m_rwLock);

    /* 更改扫查方式后（时间/编码器），需要更新C扫 */
    if(m_driving != DplSource::Scan::instance()->scan_axis()->driving()) {
        return true;
    }

    /* C扫的源更改后，需要更新C扫 */
    if(m_source != TestStub::instance()->get_source()) {
        m_source = TestStub::instance()->get_source();
        qDebug() << "=========================sourc update==============================";
        qDebug() << "=========================sourc update==============================";
        return true;
    }

    if((!m_beamsPointer.isNull()) && beams->beam_qty() != m_beamsPointer->beam_qty()) {
        qDebug() << "=========================beam_qty update==============================";
        qDebug() << "=========================beam_qty update==============================";
        return true;
    }

    /* TODO */
    /* 闸门开始值、宽度、幅度更改后，需更新C扫 */
    //m_group->gate(static_cast<DplGate::Gate::Type>(m_gateItem->current_index()))->set_visible(!index);

    /* 聚焦类型更改后，需要更新C扫 */

    /* （VPA/角度/beamQty）更改后，需要更新C扫 */

    /* Thickness数据源：A^、A^ - I^、A^ - I/等 */

    return false;
}

bool CscanScene::redraw_beams(const DplSource::BeamsPointer &beams)
{
    QWriteLocker lock(&m_rwLock);

    if(m_beamsPointer.isNull()) {
        m_beamsPointer = beams;
    }

    return redraw_vertical_beam();

}

void CscanScene::set_beams(const DplSource::BeamsPointer &beams)
{
    QWriteLocker lock(&m_rwLock);

    if(m_image == NULL) {
        qDebug() << "[" << __FUNCTION__ << "]" << " image is NULL. warning!!!!!";
        m_image = new QImage(m_size, QImage::Format_Indexed8);
        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);
    }

    m_beamsPointer = beams;

    draw_vertical_beam();

    emit image_changed();

    qDebug() << "[" << __FUNCTION__ <<  "]" << " beamsShowCount = " << m_beamsShowedCount;

}
