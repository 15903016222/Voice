#include "c_scan_encoder_scene.h"

#include <source/scan.h>
#include <source/source.h>
#include <source/beams.h>

#define FLOAT_ZERO  0.0000001

CscanEncoderScene::CscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent)
    : EncoderScene(palette, grp, parent),
      m_cscanDataPointer(new CScanData(grp))
{
    set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    init_encoder_properties();
    init_scan_properties();
}


bool CscanEncoderScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(EncoderScene::need_refresh(beams)) {
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


void CscanEncoderScene::set_vertical_image_data(int beamsShowedCount, const BaseScanScene::S_CommonProperties &commonProperties, BaseScanScene::E_BEAM_TYPE type, const DplSource::BeamsPointer &beamsPointer)
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
        if(!m_cscanDataPointer->get_peak_value(beamsPointer, num, gateValue))
        {
            continue;
        }

        double gateValueTmp;
        m_cscanDataPointer->get_peak_value(m_beamsPointer, num, gateValueTmp);

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

