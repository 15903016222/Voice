#include "b_scan_encoder_scene.h"
#include <QDebug>
#include <math.h>

#include <source/beams.h>
#include <source/source.h>


#define FLOAT_ZERO  0.0000001

BscanEncoderScene::BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) :
    BscanScene(palette, group, parent),
    m_offsetX(0.0),
    m_currentX(0.0)
{

}

void BscanEncoderScene::draw_horizontal_beam()
{

}

void BscanEncoderScene::draw_vertical_beam()
{
    S_CommonProperties commonProperties;

    calculate_common_properties(commonProperties);

    if(!m_scrolling) {

        set_vertical_image_data(commonProperties);

    } else {

        set_scroll_vertical_image_data(commonProperties);
    }

    ++m_beamsShowedCount;
}


void BscanEncoderScene::redraw_horizontal_beam()
{

}


void BscanEncoderScene::redraw_vertical_beam()
{

}


void BscanEncoderScene::set_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties)
{
    double x = ((int)((m_beamsPointer->get(0)->encoder_x() / ENCODER_RESOLUTION + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    /* 设置当前beam数据 */
    set_vertical_beam_data(x, commonProperties, (quint8 *) m_beamsPointer->raw_data());

    int intervalX = (m_currentX - x + 0.05)  * 10 ; /* 保留小数点一位 */
    int symbol = 1;
    if(intervalX < 0 ) {
        symbol = -1;
    }

    qDebug() << "[" << __FUNCTION__ << "]" << " x = " << x << " interval = " << intervalX;

    DplSource::BeamsPointer tmpBeams;

    for(int i = 0; i < abs(intervalX); ++i) {

        double targetX = m_currentX - (i * symbol) / 10.0;

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
}


void BscanEncoderScene::set_vertical_beam_data(double x, const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
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
    double x = ((int)((m_beamsPointer->get(0)->encoder_x() / ENCODER_RESOLUTION + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    qDebug() << "[" << __FUNCTION__ << "]" << " need scroll window sometimes. m_pixPerBeamRatio = " << m_pixPerBeamRatio
             << " x = " << x;

    double targetBeamPosition = (int)((x - SCAN_START) / SCAN_RESOLUTION + 0.5) * m_pixPerBeamRatio;
    targetBeamPosition -= ((m_offsetX / SCAN_RESOLUTION + 0.5) * m_pixPerBeamRatio);

    double currentStart = SCAN_START + m_offsetX;
    double currentEnd   = currentStart + m_image->width() / m_pixPerBeamRatio * SCAN_RESOLUTION;

    if(x > currentStart && x < currentEnd) {
        /* 当前位置在该显示区域 */
        qDebug() << "[" << __FUNCTION__ << "]" << " show here."
                 << " x = " << x;

    } else if(x > currentEnd && x < SCAN_END) {
        /* 往SCAN_END滚动 */
        /* 重画之前所有的beams */
        m_offsetX = x - SCAN_START;
        qDebug() << "[" << __FUNCTION__ << "]" << " scroll end."
                    << " x = " << x;

    } else if(x < currentStart && x > SCAN_START) {
        /* 往SCAN_START滚动 */
        /* 重画之前所有的beams */
        m_offsetX = x - SCAN_START;
        qDebug() << "[" << __FUNCTION__ << "]" << " scroll start."
                    << " x = " << x;
    }
}


void BscanEncoderScene::set_horizontal_image_data(const BscanScene::S_CommonProperties &commonProperties)
{

}


bool BscanEncoderScene::is_equal(double value1, double value2)
{
    return (((value1 - value2) < FLOAT_ZERO) && ((value1 - value2) > -FLOAT_ZERO)) ? true : false;
}
