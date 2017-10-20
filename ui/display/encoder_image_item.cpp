#include "encoder_image_item.h"

#include <source/scan.h>
#include <source/source.h>
#include <source/beams.h>

EncoderImageItem::EncoderImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent)
    : BaseImageItem(palette, grp, parent)
{

}


bool EncoderImageItem::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(BaseImageItem::need_refresh(beams)) {
        init_encoder_properties();
        init_scan_properties();
        return true;
    }

    /* 编码器参数改变，需要刷新 */
    if(m_encoder.mode() != m_encoderPointer->mode()
            || m_encoder.polarity() != m_encoderPointer->polarity()
            || (!is_equal(m_encoder.resolution(), m_encoderPointer->resolution()))
            || (!is_equal(m_encoder.origin(), m_encoderPointer->origin()))) {

        if(m_driving == DplSource::Axis::ENCODER_X) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_x();
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_y();
        }

        init_encoder_properties();
        init_scan_properties();
        return true;
    }

    /* 扫查参数改变，需要刷新 */
    if((!is_equal(m_axis.resolution(), DplSource::Scan::instance()->scan_axis()->resolution()))
            || (!is_equal(m_axis.start(), DplSource::Scan::instance()->scan_axis()->start()))
            || (!is_equal(m_axis.end(), DplSource::Scan::instance()->scan_axis()->end()))) {

        if(m_driving == DplSource::Axis::ENCODER_X) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_x();
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            m_encoderPointer = DplSource::Scan::instance()->encoder_y();
        }

        init_encoder_properties();
        init_scan_properties();

        return true;
    }

    return false;

}


void EncoderImageItem::draw_vertical_beam()
{
    S_CommonProperties commonProperties;
    calculate_common_properties(commonProperties);

    if(m_scrolling) {
        set_scroll_env(commonProperties);
    }

    draw_vertical_image(commonProperties);
}


bool EncoderImageItem::redraw_vertical_beam()
{
    if(!m_redrawFlag) {
        return false;
    }

    /* 从SCAN_SATART到m_currentX进行重画 */
    DplSource::BeamsPointer lastBeamsPointer;
    double scanStart = DplSource::Scan::instance()->scan_axis()->start();
    double scanEnd = DplSource::Scan::instance()->scan_axis()->end();

    /* 计算最新的start、end */
    double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();
    double currentStart     = scanStart + m_offsetX;
    double currentEnd       = currentStart + m_image->width() / m_pixPerBeamRatio * scanResolution;

    if(m_scrolling) {
        /* 缩小 */
        if(m_currentX > currentEnd) {
            /* 当前currentX超出最新的end */
            /* 探测以currentX为中心，确定最新start、end */
            currentStart   = m_currentX - (m_image->width() / m_pixPerBeamRatio * scanResolution) / 2.0;
            currentEnd     = m_currentX + (m_image->width() / m_pixPerBeamRatio * scanResolution) / 2.0;
        }

        /* 放大*/
        if(currentEnd > scanEnd) {
            /* 当前currentEnd超出扫查终点时 */
            /* 确定最新start、end */
            currentStart = scanEnd - m_image->width() / m_pixPerBeamRatio * scanResolution;
            currentEnd   = scanEnd;
        }

        m_currentEnd    = currentEnd;
        m_currentStart  = currentStart;

        if(currentEnd < m_maxBeamInfo.x) {
            /* 小于最大的显示 */
            m_currentX  = currentStart;
            lastBeamsPointer = DplSource::Source::instance()->beams(m_group->index(), currentEnd, m_maxBeamInfo.y);
            set_move_x(currentEnd, m_maxBeamInfo.y);

        } else {

            /* currentEnd 大于等于 m_maxBeamInfo.x */
            m_currentX = currentStart;
            lastBeamsPointer = DplSource::Source::instance()->beams(m_group->index(), m_maxBeamInfo.x, m_maxBeamInfo.y);
            set_move_x(m_maxBeamInfo.x, m_maxBeamInfo.y);
        }

    } else {

        m_currentX = scanStart;
        lastBeamsPointer = DplSource::Source::instance()->beams(m_group->index(), m_maxBeamInfo.x, m_maxBeamInfo.y);
        set_move_x(m_maxBeamInfo.x, m_maxBeamInfo.x);

    }

    if(lastBeamsPointer.isNull()) {
        qDebug() << "[" << __FUNCTION__ << "]" << " last beamsPointer is NULL.";
        return false;
    }

    if(!m_redrawFlag) {
        m_beamsPointer = lastBeamsPointer;
    }

    m_offsetX   = m_currentX - scanStart;

    S_CommonProperties commonProperties;
    calculate_common_properties(commonProperties);

    draw_vertical_image(commonProperties);

    if(m_redrawFlag) {
        m_moveX = currentEnd;
    }

    m_redrawFlag = false;
    return true;
}

void EncoderImageItem::draw_vertical_image(const BaseImageItem::S_CommonProperties &commonProperties)
{
    double x = ((int)((get_dealing_x(m_beamsPointer) + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    /* 设置当前beam数据 */
    set_one_vertical_beam(x, commonProperties, m_beamsPointer);

    double retain = 10.0;   /* 10.0 ： 保留小数点一位； 1.0 ： 保留整数位 */
    int intervalX = (m_currentX - x + 0.05) * retain;

    if(m_redrawFlag) {
        retain = 1.0;
        intervalX = (m_currentX - x + 0.5) * retain;
    }

    int symbol = 1;
    if(intervalX < 0 ) {
        symbol = -1;
    }

    DplSource::BeamsPointer tmpBeams;

    for(int i = 0; i <= abs(intervalX); ++i) {

        double targetX = m_currentX - (i * symbol) / retain;

        if(m_axis.driving() == DplSource::Axis::ENCODER_X) {
            tmpBeams = DplSource::Source::instance()->beams(m_group->index(), (int)targetX, m_beamsPointer->get(0)->encoder_y());
        } else if(m_axis.driving() == DplSource::Axis::ENCODER_Y) {
            tmpBeams = DplSource::Source::instance()->beams(m_group->index(), m_beamsPointer->get(0)->encoder_x(), (int)targetX);
        }

        if(tmpBeams.isNull()) {
            qDebug() << "[" << __FUNCTION__ << "]" << " tmpBeams is NULL.";
            continue;
        }

        set_one_vertical_beam(targetX, commonProperties, tmpBeams);
    }

    m_currentX = x;

    if(m_currentX > m_maxBeamInfo.x) {

        m_maxBeamInfo.x = m_currentX;

        if(m_driving == DplSource::Axis::ENCODER_X) {
            m_maxBeamInfo.y = ((int)((m_beamsPointer->get(0)->encoder_y()
                                        / m_encoderPointer->resolution() + 0.005) * 100)) / 100.0;
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            m_maxBeamInfo.y = ((int)((m_beamsPointer->get(0)->encoder_x()
                                        / m_encoderPointer->resolution() + 0.005) * 100)) / 100.0;
        }
    }
}


void EncoderImageItem::set_one_vertical_beam(double x, const BaseImageItem::S_CommonProperties &commonProperties, const DplSource::BeamsPointer &beamsPointer)
{
    /* 没有滚动显示，当前区域可显示所扫查范围 */
    double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
    double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
    double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();

    if((x < scanStart)
        || (x > scanEnd)) {
        return;
    }

    if(x < m_encoderPointer->origin()) {
        return;
    }

    int beamIndex;

    if(scanStart < 0.0) {
        if(x > 0.0) {
            beamIndex = (fabs(scanStart) + x - m_offsetX) / scanResolution;
        } else {
            beamIndex = fabs(x - m_offsetX - scanStart) / scanResolution;
        }
    } else {
        beamIndex = (x - (scanStart + m_offsetX)) / scanResolution;
    }


    if((beamIndex + 1) == commonProperties.maxIndex && (commonProperties.align != 0)) {
        /* 非对齐,最后一条beam */
//        int offset =  commonProperties.pixCount - commonProperties.align;
//        QImage tmp = m_image->copy(offset, 0, m_image->width(), m_image->height());
//        m_image->swap(tmp);

        set_vertical_image_data(beamIndex, commonProperties, LAST_BEAM, beamsPointer);

    } else {
        set_vertical_image_data(beamIndex, commonProperties, NORMAL_BEAM, beamsPointer);
    }

    ++m_beamsShowedCount;
}


void EncoderImageItem::set_scroll_env(const BaseImageItem::S_CommonProperties &commonProperties)
{
    double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
    double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
    double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();
    double scanWidth        = m_image->width() / m_pixPerBeamRatio * scanResolution;

    double x = ((int)((get_dealing_x(m_beamsPointer) + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    double currentStart = scanStart + m_offsetX;
    double currentEnd   = currentStart + scanWidth;

     if(is_equal(x, currentStart)
            || (x > currentStart && x < currentEnd)
            /*|| is_equal(x, currentEnd)*/){
        /* 当前位置在该显示区域 */
    } else if(is_equal(x, currentEnd)
              || (x > currentEnd && x < scanEnd)
              || is_equal(x, scanEnd)) {

        /* 往SCAN_END滚动,重画已显示的beams */

        m_moveOffsetX = x - currentEnd + 1;
        m_offsetX += m_moveOffsetX;

        if(m_moveOffsetX < scanWidth) {
            /* 移动数值小于显示数值，偏移拷贝image */
            QImage tmp = m_image->copy((int)((m_moveOffsetX / scanResolution) * m_pixPerBeamRatio + 0.5), 0, m_image->width(), m_image->height());
            m_image->swap(tmp);
        } else {
            /* 移动数值大于显示区域数值，直接填充white */
            m_image->fill(Qt::white);
        }

    } else if((x < currentStart && x > scanStart)
              || is_equal(x, scanStart)) {

        /* 往SCAN_START滚动,重画已显示的beams */
        m_moveOffsetX = x - currentStart;
        m_offsetX += m_moveOffsetX;

        if(m_moveOffsetX < (m_image->width() / m_pixPerBeamRatio * scanResolution)) {
            /* 移动数值小于显示数值，偏移拷贝image */
            QImage tmp = m_image->copy((int)((m_moveOffsetX / scanResolution) * m_pixPerBeamRatio - 0.5), 0, m_image->width(), m_image->height());
            m_image->swap(tmp);
        } else {
            /* 移动数值大于显示区域数值，直接填充white */
            m_image->fill(Qt::white);
        }
    } else if(x > scanEnd) {
        m_offsetX = scanEnd - scanStart - scanWidth;
    } else if(x < scanStart) {
        m_offsetX = 0.0;
    }
}


bool EncoderImageItem::is_equal(double value1, double value2)
{
    return (((value1 - value2) < FLOAT_ZERO) && ((value1 - value2) > -FLOAT_ZERO)) ? true : false;
}


void EncoderImageItem::init_encoder_properties()
{
    m_encoder.set_enabled(m_encoderPointer->is_enabled());
    m_encoder.set_mode(m_encoderPointer->mode());
    m_encoder.set_origin(m_encoderPointer->origin());
    m_encoder.set_polarity(m_encoderPointer->polarity());
    m_encoder.set_resolution(m_encoderPointer->resolution());
}


void EncoderImageItem::init_scan_properties()
{
    m_axis.set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    m_axis.set_end(DplSource::Scan::instance()->scan_axis()->end());
    m_axis.set_start(DplSource::Scan::instance()->scan_axis()->start());
    m_axis.set_resolution(DplSource::Scan::instance()->scan_axis()->resolution());
}

void EncoderImageItem::set_driving(DplSource::Axis::Driving driving)
{
    m_driving = driving;

    m_offsetX       = 0.0;
    m_moveOffsetX   = 0.0;
    m_currentX      = DplSource::Scan::instance()->scan_axis()->start();
    m_maxBeamInfo.x   = DplSource::Scan::instance()->scan_axis()->start();
    m_maxBeamInfo.y   = DplSource::Scan::instance()->scan_axis()->start();

    if(m_driving == DplSource::Axis::ENCODER_X) {
        m_encoderPointer = DplSource::Scan::instance()->encoder_x();
    } else if(m_driving == DplSource::Axis::ENCODER_Y) {
        m_encoderPointer = DplSource::Scan::instance()->encoder_y();
    }
}

double EncoderImageItem::get_dealing_x(const DplSource::BeamsPointer &beamsPointer)
{
    double x = 0.0;

    if(beamsPointer.isNull()) {
        return 0.0;
    }

    if(m_redrawFlag) {
        double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();
        double currentStart     = DplSource::Scan::instance()->scan_axis()->start() + m_offsetX;
        double currentEnd       = currentStart + m_image->width() / m_pixPerBeamRatio * scanResolution;
        if(m_maxBeamInfo.x > currentEnd) {
            x = currentEnd;
        } else {
            x = m_maxBeamInfo.x;
        }
    } else {
        if(m_driving == DplSource::Axis::ENCODER_X) {
            x = beamsPointer->get(0)->encoder_x() / m_encoderPointer->resolution();
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            x = beamsPointer->get(0)->encoder_y() / m_encoderPointer->resolution();
        }
    }

    return x;
}

void EncoderImageItem::set_move_x(double moveX, double moveY)
{
    if(m_driving == DplSource::Axis::ENCODER_X) {
        m_moveX = moveX;
    } else if(m_driving == DplSource::Axis::ENCODER_Y) {
        m_moveX = moveY;
    }
}


