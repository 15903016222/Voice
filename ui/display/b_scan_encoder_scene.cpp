#include "b_scan_encoder_scene.h"
#include <QDebug>
#include <math.h>

#include <source/beams.h>
#include <source/source.h>

#include "Tracer.h"

#define FLOAT_ZERO  0.0000001

BscanEncoderScene::BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) :
    BscanScene(palette, group, parent),
    m_offsetX(0.0),
    m_currentX(SCAN_START),
    m_maxShowedX(SCAN_START),
    m_moveOffsetX(0.0)
{

}


void BscanEncoderScene::draw_vertical_beam()
{

    DEBUG_INIT("BscanScene", __FUNCTION__);

    S_CommonProperties commonProperties;

    calculate_common_properties(commonProperties);

    if(!m_scrolling) {

        set_vertical_image_data(commonProperties);

    } else {

        set_scroll_vertical_image_data(commonProperties);
    }

    ++m_beamsShowedCount;
}




void BscanEncoderScene::redraw_vertical_beam()
{
    /* 从SCAN_SATART到m_currentX进行重画 */
    if(m_scrolling) {

        /* 计算最新的start、end */
        double currentStart = SCAN_START + m_offsetX;
        double currentEnd   = currentStart + m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION;

        if(m_currentX > currentEnd) {
            /* 当前currentX超出最新的end */

            /* 探测以currentX为中心，确定最新start、end */
            currentStart   = m_currentX + (m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION) / 2.0;
            currentEnd     = m_currentX - (m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION) / 2.0;

            if(currentEnd < m_maxShowedX) {
                /* 小于最大的显示 */
            } else {

            }

        } else {
            /* 当前currentX在最新的显示区域 */
        }



//        m_currentX = SCAN_START;
//        m_offsetX = 0.0;
    } else {
        m_currentX = SCAN_START;
    }
    /* 重画完成后，设置m_currentX = x最新 */
}


void BscanEncoderScene::set_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties)
{
    DEBUG_INIT("BscanScene", __FUNCTION__);

    double x = ((int)((m_beamsPointer->get(0)->encoder_x() / ENCODER_RESOLUTION + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    /* 设置当前beam数据 */
    set_vertical_beam_data(x, commonProperties, (quint8 *) m_beamsPointer->raw_data());

    double retain = 10.0;   /* 10.0 ： 保留小数点一位； 1.0 ： 保留整数位 */

    int intervalX = (m_currentX - x + 0.05) * retain;

    int symbol = 1;
    if(intervalX < 0 ) {
        symbol = -1;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " m_currentX = " << m_currentX
             << " m_maxShowedX = " << m_maxShowedX
             << " dealing x = " << x << " interval = " << intervalX;

    DplSource::BeamsPointer tmpBeams;

    for(int i = 0; i < abs(intervalX); ++i) {

        double targetX = m_currentX - (i * symbol) / retain;

        //TODO
        //tmpBeams = DplSource::Source::instance()->beams(m_group, targetX, m_beamsPointer->get(0)->encoder_y());
        tmpBeams = m_beamsPointer;

        if(tmpBeams.isNull()) {
            qDebug() << "[" << __FUNCTION__ << "]" << " tmpBeams is NULL.";
            continue;
        }

        set_vertical_beam_data(targetX, commonProperties, (quint8 *)tmpBeams->raw_data());
    }

    m_currentX = x;
    if(m_currentX > m_maxShowedX) {
        m_maxShowedX = m_currentX;
    }
}


void BscanEncoderScene::set_vertical_beam_data(double x, const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
        DEBUG_INIT("BscanScene", __FUNCTION__);

    /* 没有滚动显示，当前区域可显示所扫查范围 */
    int beamIndex;

    if((x > SCAN_START || is_equal(x, SCAN_START))
            && (x < SCAN_END || is_equal(x, SCAN_END))
            && (x > ENCODER_ORIGIN || is_equal(x, ENCODER_ORIGIN))) {

        if(x > 0.0) {
            beamIndex = (fabs(SCAN_START) + x) / SCAN_RESOLUTION;
        } else {
            beamIndex = fabs(x - SCAN_START) / SCAN_RESOLUTION;
        }

        for(int lineNum = 0; lineNum < m_size.height(); ++lineNum) {

            quint8 *line  = (quint8*) m_image->scanLine(lineNum);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                int pos = (int)(beamIndex * commonProperties.pixCount + j);

                if(pos < m_size.width()) {
                    line[pos] = waveData[(int)(lineNum * commonProperties.ratio)];
                }
            }
        }
    }
}

void BscanEncoderScene::set_scroll_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties)
{
        DEBUG_INIT("BscanScene", __FUNCTION__);

    double x = ((int)((m_beamsPointer->get(0)->encoder_x() / ENCODER_RESOLUTION + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    double targetBeamPosition = ((x - SCAN_START) / SCAN_RESOLUTION) * m_pixPerBeamRatio;

    qDebug() << "[" << __FUNCTION__ << "]"
             << " true targetBeamPosition = " << targetBeamPosition
             << " m_image w = " << m_image->width()
             << " h = " << m_image->height()
             << " wave size = " << m_beamsPointer->get(0)->wave().size()
             << " m_beamsPointer->size = " << m_beamsPointer->size();

    targetBeamPosition -= ((m_offsetX / SCAN_RESOLUTION) * m_pixPerBeamRatio);

    double currentStart = SCAN_START + m_offsetX;
    double currentEnd   = currentStart + m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION;

    qDebug() << "[" << __FUNCTION__ << "]"
             << " m_currentX = " << m_currentX
             << " m_maxShowedX = " << m_maxShowedX
             << " dealing x = " << x
             << " currentStart = " << currentStart
             << " currentEnd = " << currentEnd
             << " scroll targetBeamPosition = " << targetBeamPosition;

    if(is_equal(x, currentStart)
            || (x > currentStart && x < currentEnd)
            || is_equal(x, currentEnd)) {

        /* 当前位置在该显示区域 */
        qDebug() << "[" << __FUNCTION__ << "]" << " show here."
                 << " x = " << x << " m_offsetX = " << m_offsetX;

        set_vertical_image_data_tmp(commonProperties);


    } else if((x > currentEnd && x < SCAN_END)
              || is_equal(x, SCAN_END)) {

        /* 往SCAN_END滚动 */
        /* 重画之前所有的beams */

        m_moveOffsetX = x - currentEnd;
        m_offsetX += m_moveOffsetX;

        if(m_moveOffsetX < (m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION)) {
            /* 移动数值小于显示数值，偏移拷贝image */
            QImage tmp = m_image->copy((int)((m_moveOffsetX / SCAN_RESOLUTION) * m_pixPerBeamRatio + 0.5), 0, m_image->width(), m_image->height());
            m_image->swap(tmp);
        } else {
            /* 移动数值大于显示区域数值，直接填充white */
            m_image->fill(Qt::white);
        }

        qDebug() << "[" << __FUNCTION__ << "]" << " scroll end."
                    << " x = " << x
                    << " m_offsetX = " << m_offsetX
                    << " m_moveOffsetX = " << m_moveOffsetX
                    << " offset pix = " << (m_moveOffsetX / SCAN_RESOLUTION) * m_pixPerBeamRatio
                    << " commonProperties.ratio = " << commonProperties.ratio;

        set_vertical_image_data_tmp(commonProperties);


    } else if((x < currentStart && x > SCAN_START)
              || is_equal(x, SCAN_START)) {

        /* 往SCAN_START滚动 */
        /* 重画之前所有的beams */
        m_moveOffsetX = x - currentStart;
        m_offsetX += m_moveOffsetX;

        if(m_moveOffsetX < (m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION)) {
            /* 移动数值小于显示数值，偏移拷贝image */
            QImage tmp = m_image->copy((int)((m_moveOffsetX / SCAN_RESOLUTION) * m_pixPerBeamRatio - 0.5), 0, m_image->width(), m_image->height());
            m_image->swap(tmp);
        } else {
            /* 移动数值大于显示区域数值，直接填充white */
            m_image->fill(Qt::white);
        }

        qDebug() << "[" << __FUNCTION__ << "]" << " scroll start."
                 << " x = " << x
                 << " m_offsetX = " << m_offsetX
                 << " m_moveOffsetX = " << m_moveOffsetX
                 << " offset pix = " << (m_moveOffsetX / SCAN_RESOLUTION) * m_pixPerBeamRatio;

        set_vertical_image_data_tmp(commonProperties);

    } else if(x > SCAN_END){

        m_offsetX = SCAN_END - SCAN_START - m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION;
        qDebug() << "[" << __FUNCTION__ << "]" << " x > SCAN_END not in rang. new m_offsetX = " << m_offsetX;

    } else if(x < SCAN_START) {

        m_offsetX = 0.0;
        qDebug() << "[" << __FUNCTION__ << "]" << " x < SCAN_START not in rang. new m_offsetX = " << m_offsetX;

    }

    m_currentX = x;
    if(m_currentX > m_maxShowedX) {
        m_maxShowedX = m_currentX;
    }

}

void BscanEncoderScene::set_vertical_image_data_tmp(const BscanScene::S_CommonProperties &commonProperties)
{
        DEBUG_INIT("BscanScene", __FUNCTION__);

    double x = ((int)((m_beamsPointer->get(0)->encoder_x() / ENCODER_RESOLUTION + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    /* 设置当前beam数据 */
    m_trueData = true;
    set_vertical_beam_data_tmp(x, commonProperties, (quint8 *) m_beamsPointer->raw_data());
    m_trueData = false;
    double retain = 10.0;   /* 10.0 ： 保留小数点一位； 1.0 ： 保留整数位 */

    int intervalX = (m_currentX - x + 0.05) * retain;

    int symbol = 1;
    if(intervalX < 0 ) {
        symbol = -1;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " m_currentX = " << m_currentX
             << " m_maxShowedX = " << m_maxShowedX
             << " dealing x = " << x << " interval = " << intervalX;

//    DplSource::BeamsPointer tmpBeams;

    for(int i = 0; i < abs(intervalX); ++i) {

        double targetX = m_currentX - (i * symbol) / retain;

        //TODO
        //tmpBeams = DplSource::Source::instance()->beams(m_group, targetX, m_beamsPointer->get(0)->encoder_y());
//        tmpBeams = m_beamsPointer;

//        if(tmpBeams.isNull()) {
//            qDebug() << "[" << __FUNCTION__ << "]" << " tmpBeams is NULL.";
//            continue;
//        }

        set_vertical_beam_data_tmp(targetX, commonProperties, (quint8 *)m_beamsPointer->raw_data());
    }

    m_currentX = x;
    if(m_currentX > m_maxShowedX) {
        m_maxShowedX = m_currentX;
    }
}

void BscanEncoderScene::set_vertical_beam_data_tmp(double x, const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
     //DEBUG_INIT("BscanScene", __FUNCTION__);

    /* 没有滚动显示，当前区域可显示所扫查范围 */
    int beamIndex;

    if((x < SCAN_START)
        || (x > SCAN_END)) {
            return;
    }

    if(x < ENCODER_ORIGIN) {
        return;
    }

    /*   if((x > SCAN_START || is_equal(x, SCAN_START))
               && (x < SCAN_END || is_equal(x, SCAN_END))
               && (x > ENCODER_ORIGIN || is_equal(x, ENCODER_ORIGIN))) */
    {

        if(x > 0.0) {
            beamIndex = (fabs(SCAN_START) + x - m_offsetX) / SCAN_RESOLUTION;
        } else {
            beamIndex = fabs(x - m_offsetX - SCAN_START) / SCAN_RESOLUTION;
        }

        for(int lineNum = 0; lineNum < m_image->height(); ++lineNum) {

            quint8 *line  = (quint8*) m_image->scanLine(lineNum);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                int pos = (int)(beamIndex * commonProperties.pixCount + j);

                if(lineNum + 1 ==  m_image->height()) {
                    qDebug() << "[set_vertical_beam_data_tmp] pox = " << pos
                             << " wave = " << (int)(lineNum * commonProperties.ratio)
                             << " beamIndex = " << beamIndex;
                }

                if(pos < m_image->width() && pos >= 0) {
                    if(m_trueData) {
                        line[pos] = waveData[(int)(lineNum * commonProperties.ratio)];
                    }else {
                        line[pos] = (int)x % 255;
//                        line[pos] = (quint8)((int)x % 255);
                    }
                }
            }
        }
    }
}




bool BscanEncoderScene::is_equal(double value1, double value2)
{
    return (((value1 - value2) < FLOAT_ZERO) && ((value1 - value2) > -FLOAT_ZERO)) ? true : false;
}
