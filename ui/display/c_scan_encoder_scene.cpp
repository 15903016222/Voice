#include "c_scan_encoder_scene.h"

#include <source/scan.h>

#define FLOAT_ZERO  0.0000001

CscanEncoderScene::CscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent)
    : CscanScene(palette, grp, parent)
{
    set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    init_encoder_properties();
    init_scan_properties();
}

bool CscanEncoderScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(CscanScene::need_refresh(beams)) {
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

void CscanEncoderScene::draw_vertical_beam()
{

}

bool CscanEncoderScene::redraw_vertical_beam()
{
    return false;
}

bool CscanEncoderScene::is_equal(double value1, double value2)
{
     return (((value1 - value2) < FLOAT_ZERO) && ((value1 - value2) > -FLOAT_ZERO)) ? true : false;

}

void CscanEncoderScene::init_encoder_properties()
{
    m_encoder.set_enabled(m_encoderPointer->is_enabled());
    m_encoder.set_mode(m_encoderPointer->mode());
    m_encoder.set_origin(m_encoderPointer->origin());
    m_encoder.set_polarity(m_encoderPointer->polarity());
    m_encoder.set_resolution(m_encoderPointer->resolution());
}

void CscanEncoderScene::init_scan_properties()
{
    m_axis.set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    m_axis.set_end(DplSource::Scan::instance()->scan_axis()->end());
    m_axis.set_start(DplSource::Scan::instance()->scan_axis()->start());
    m_axis.set_resolution(DplSource::Scan::instance()->scan_axis()->resolution());
}


void CscanEncoderScene::set_driving(DplSource::Axis::Driving driving)
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

