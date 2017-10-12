#include "b_scan_encoder_scene.h"
#include <QDebug>
#include <math.h>

#include <source/beams.h>
#include <source/source.h>
#include <source/scan.h>
#include <source/driving.h>
#include <fpga/fpga.h>

#include "Tracer.h"

#define FLOAT_ZERO  0.0000001
#define NO_BEAMS

BscanEncoderScene::BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette,
                                     int group,
                                     QObject *parent) :
    BscanScene(palette, group, parent),
    m_offsetX(0.0),
    m_moveOffsetX(0.0)
{
    set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    init_encoder_properties();
    init_scan_properties();
}

bool BscanEncoderScene::need_refresh()
{
    if(BscanScene::need_refresh()) {
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

void BscanEncoderScene::set_driving(DplSource::Axis::Driving driving)
{

    m_driving = driving;

    m_offsetX       = 0.0;
    m_moveOffsetX   = 0.0;

    m_currentX      = DplSource::Scan::instance()->scan_axis()->start();

    m_maxShowedWave.x   = DplSource::Scan::instance()->scan_axis()->start();
    m_maxShowedWave.y   = DplSource::Scan::instance()->scan_axis()->start();

    if(m_driving == DplSource::Axis::ENCODER_X) {
        m_encoderPointer = DplSource::Scan::instance()->encoder_x();
    } else if(m_driving == DplSource::Axis::ENCODER_Y) {
        m_encoderPointer = DplSource::Scan::instance()->encoder_y();
    }
}

void BscanEncoderScene::setTmpX(double moveX, double moveY)
{
    if(m_driving == DplSource::Axis::ENCODER_X) {
        m_moveX = moveX;
    } else if(m_driving == DplSource::Axis::ENCODER_Y) {
        m_moveX = moveY;
    }
}

void BscanEncoderScene::init_encoder_properties()
{
    m_encoder.set_enabled(m_encoderPointer->is_enabled());
    m_encoder.set_mode(m_encoderPointer->mode());
    m_encoder.set_origin(m_encoderPointer->origin());
    m_encoder.set_polarity(m_encoderPointer->polarity());
    m_encoder.set_resolution(m_encoderPointer->resolution());
}

void BscanEncoderScene::init_scan_properties()
{
    m_axis.set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    m_axis.set_end(DplSource::Scan::instance()->scan_axis()->end());
    m_axis.set_start(DplSource::Scan::instance()->scan_axis()->start());
    m_axis.set_resolution(DplSource::Scan::instance()->scan_axis()->resolution());
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

    DEBUG_INIT("BscanEncoderScene", __FUNCTION__);

    /* 从SCAN_SATART到m_currentX进行重画 */
    DplSource::BeamsPointer lastBeamsPointer;
    double scanStart = DplSource::Scan::instance()->scan_axis()->start();
    double scanEnd = DplSource::Scan::instance()->scan_axis()->end();

    /* 计算最新的start、end */
    double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();
    double currentStart     = scanStart + m_offsetX;
    double currentEnd       = currentStart + m_image->width() / m_pixPerBeamRatio * scanResolution;

    qDebug() << "[" << __FUNCTION__ << "]"
             << " currentStart = " << currentStart
             << " currentEnd = " << currentEnd;

    if(m_scrolling) {

        /* 缩小 */
        if(m_currentX > currentEnd) {
            /* 当前currentX超出最新的end */
            /* 探测以currentX为中心，确定最新start、end */
            currentStart   = m_currentX - (m_image->width() / m_pixPerBeamRatio * scanResolution) / 2.0;
            currentEnd     = m_currentX + (m_image->width() / m_pixPerBeamRatio * scanResolution) / 2.0;

            qDebug() << "[" << __FUNCTION__ << "]"
                     << " m_currentX > currentEnd :  new currentStart = " << currentStart
                     << " new currentEnd = " << currentEnd;
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

        if(currentEnd < m_maxShowedWave.x) {
            /* 小于最大的显示 */
            m_currentX  = currentStart;
            lastBeamsPointer = DplSource::Source::instance()->beams(m_group, currentEnd, m_maxShowedWave.y);
            setTmpX(currentEnd, m_maxShowedWave.y);

            qDebug() << "[" << __FUNCTION__ << "]"
                     << " currentEnd < m_maxShowedWave.x : new m_currentX = " << m_currentX;

        } else {

            /* currentEnd 大于等于 m_maxShowedWave.x */
            m_currentX = currentStart;
            lastBeamsPointer = DplSource::Source::instance()->beams(m_group, m_maxShowedWave.x, m_maxShowedWave.y);
            setTmpX(m_maxShowedWave.x, m_maxShowedWave.y);

            qDebug() << "[" << __FUNCTION__ << "]"
                     << " currentEnd > m_maxShowedWave.x :  new m_currentX = " << m_currentX
                     << " m_maxShowedWave.x = " << m_maxShowedWave.x
                     << " m_maxShowedWave.y = " << m_maxShowedWave.y;
        }

    } else {

        m_currentX = scanStart;
        lastBeamsPointer = DplSource::Source::instance()->beams(m_group, m_maxShowedWave.x, m_maxShowedWave.y);
        setTmpX(m_maxShowedWave.x, m_maxShowedWave.x);

        qDebug() << "[" << __FUNCTION__ << "]" << " is not scroll window redrawing";
    }

    if(lastBeamsPointer.isNull()) {
        qDebug() << "[" << __FUNCTION__ << "]" << " beamsPointer is NULL.";
        return;
    }

    if(m_redrawFlag) {

    } else {
        m_beamsPointer = lastBeamsPointer;
    }

    m_offsetX   = m_currentX - scanStart;

    qDebug() << "[" << __FUNCTION__ << "]"
             << " beamsPointer encoder x = " << lastBeamsPointer->get(0)->encoder_x() / m_encoderPointer->resolution()
             << " encoder y = " << lastBeamsPointer->get(0)->encoder_y() / m_encoderPointer->resolution()
             << " m_offsetX = " << m_offsetX
             << " m_currentX = " << m_currentX
             << " scanStart = " << scanStart;

    S_CommonProperties commonProperties;
    calculate_common_properties(commonProperties);

    set_vertical_image_data(commonProperties);

    if(m_redrawFlag) {

        m_moveX = currentEnd;
    }
}


void BscanEncoderScene::set_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties)
{
    DEBUG_INIT("BscanScene", __FUNCTION__);

    double x = ((int)((get_dealing_x(m_beamsPointer) + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    /* 设置当前beam数据 */
    set_vertical_beam_data(x, commonProperties, (quint8 *) m_beamsPointer->raw_data());

#if 1
    double retain = 10.0;   /* 10.0 ： 保留小数点一位； 1.0 ： 保留整数位 */
    int intervalX = (m_currentX - x + 0.05) * retain;
#else
    double retain = 1.0;   /* 10.0 ： 保留小数点一位； 1.0 ： 保留整数位 */
    int intervalX = (m_currentX - x + 0.5) * retain;
#endif

    int symbol = 1;
    if(intervalX < 0 ) {
        symbol = -1;
    }

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

    if(m_redrawFlag) {
        m_currentX = m_moveX;
    }

    m_currentX = x;

    if(m_currentX > m_maxShowedWave.x) {

        m_maxShowedWave.x = m_currentX;

        if(m_driving == DplSource::Axis::ENCODER_X) {
            m_maxShowedWave.y = ((int)((m_beamsPointer->get(0)->encoder_y()
                                        / m_encoderPointer->resolution() + 0.005) * 100)) / 100.0;
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            m_maxShowedWave.y = ((int)((m_beamsPointer->get(0)->encoder_x()
                                        / m_encoderPointer->resolution() + 0.005) * 100)) / 100.0;
        }
    }
}


void BscanEncoderScene::set_vertical_beam_data(double x, const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
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

    for(int lineNum = 0; lineNum < m_image->height(); ++lineNum) {

        quint8 *line  = (quint8*) m_image->scanLine(lineNum);

        for(int j = 0; j < commonProperties.pixCount; ++j) {

            int pos = (int)(beamIndex * commonProperties.pixCount + j);

            if(pos >= m_image->width() || pos < 0) {
                qDebug() << "[" << __FUNCTION__ << "]" << " error pos = " << pos
                         << " scanStart = " << scanStart
                         << " m_offsetx = " << m_offsetX;
                continue;
            }

            line[pos] = waveData[(int)(lineNum * commonProperties.ratio)];
        }
    }
}


void BscanEncoderScene::set_scroll_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties)
{
    DEBUG_INIT("BscanScene", __FUNCTION__);

    double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
    double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
    double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();

    double x = ((int)((get_dealing_x(m_beamsPointer) + 0.005) * 100)) / 100.0; /* 保留小数点两位 */

    double targetBeamPosition = ((x - scanStart) / scanResolution) * m_pixPerBeamRatio;

    targetBeamPosition -= ((m_offsetX / scanResolution) * m_pixPerBeamRatio);

    double currentStart = scanStart + m_offsetX;
    double currentEnd   = currentStart + m_image->width() / m_pixPerBeamRatio * scanResolution;

    if(is_equal(x, currentStart)
            || (x > currentStart && x < currentEnd)
            || is_equal(x, currentEnd)) {

        /* 当前位置在该显示区域 */
        qDebug() << "[" << __FUNCTION__ << "]" << " show here."
                 << " x = " << x << " m_offsetX = " << m_offsetX;

        set_vertical_image_data(commonProperties);


    } else if((x > currentEnd && x < scanEnd)
              || is_equal(x, scanEnd)) {

        /* 往SCAN_END滚动 */
        /* 重画之前所有的beams */

        m_moveOffsetX = x - currentEnd;
        m_offsetX += m_moveOffsetX;

        if(m_moveOffsetX < (m_image->width() / m_pixPerBeamRatio * scanResolution)) {
            /* 移动数值小于显示数值，偏移拷贝image */
            QImage tmp = m_image->copy((int)((m_moveOffsetX / scanResolution) * m_pixPerBeamRatio + 0.5), 0, m_image->width(), m_image->height());
            m_image->swap(tmp);
        } else {
            /* 移动数值大于显示区域数值，直接填充white */
            m_image->fill(Qt::white);
        }

        set_vertical_image_data(commonProperties);

    } else if((x < currentStart && x > scanStart)
              || is_equal(x, scanStart)) {

        /* 往 scanStart 滚动 */
        /* 重画之前所有的beams */
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

        set_vertical_image_data(commonProperties);

    } else if(x > scanEnd) {

        m_offsetX = scanEnd - scanStart - m_image->width() / m_pixPerBeamRatio * scanResolution;
        qDebug() << "[" << __FUNCTION__ << "]" << " x > SCAN_END not in rang. new m_offsetX = " << m_offsetX;

    } else if(x < scanStart) {

        m_offsetX = 0.0;
        qDebug() << "[" << __FUNCTION__ << "]" << " x < scanStart not in rang. new m_offsetX = " << m_offsetX;

    }

    m_currentX = x;
    if(m_currentX > m_maxShowedWave.x) {
        m_maxShowedWave.x = m_currentX;
        if(m_driving == DplSource::Axis::ENCODER_X) {
                m_maxShowedWave.y = ((int)((m_beamsPointer->get(0)->encoder_y() / m_encoderPointer->resolution() + 0.005) * 100)) / 100.0;
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
                m_maxShowedWave.y = ((int)((m_beamsPointer->get(0)->encoder_x() / m_encoderPointer->resolution() + 0.005) * 100)) / 100.0;
        }
    }
}


bool BscanEncoderScene::is_equal(double value1, double value2)
{
    return (((value1 - value2) < FLOAT_ZERO) && ((value1 - value2) > -FLOAT_ZERO)) ? true : false;
}


double BscanEncoderScene::get_dealing_x(const DplSource::BeamsPointer &beamsPointer)
{
    double x = 0.0;

    if(beamsPointer.isNull()) {
        return 0.0;
    }

    if(m_redrawFlag) {
        double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();
        double currentStart     = DplSource::Scan::instance()->scan_axis()->start() + m_offsetX;
        double currentEnd       = currentStart + m_image->width() / m_pixPerBeamRatio * scanResolution;
        if(m_maxShowedWave.x > currentEnd) {
            x = currentEnd;
        } else {
            x = m_maxShowedWave.x;
        }
    } else {
        if(m_driving == DplSource::Axis::ENCODER_X) {
            x = beamsPointer->get(0)->encoder_x() / m_encoderPointer->resolution();
        } else if(m_driving == DplSource::Axis::ENCODER_Y) {
            x = beamsPointer->get(0)->encoder_y() / m_encoderPointer->resolution();
        }
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " m_driving = " << m_driving
             << " m_offsetX = " << m_offsetX
             << " *****************  dealing x = " << x;


    qDebug() << "[" << __FUNCTION__ << "]"
             << " scanStart = " << DplSource::Scan::instance()->scan_axis()->start()
             << " scanEnd = " << DplSource::Scan::instance()->scan_axis()->end()
             << " resolution =" << DplSource::Scan::instance()->scan_axis()->resolution()
             << " driving = " << DplSource::Scan::instance()->scan_axis()->driving();

    qDebug() << "[" << __FUNCTION__ << "]"
             << " encoder mode = " << m_encoderPointer->mode()
             << " encoder resolution = " << m_encoderPointer->resolution()
             << " encoder enabled = " << m_encoderPointer->is_enabled()
             << " encoder origin = " << m_encoderPointer->origin();

    return x;
}
