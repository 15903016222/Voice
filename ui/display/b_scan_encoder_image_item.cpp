#include "b_scan_encoder_image_item.h"
#include <QDebug>
#include <math.h>

#include <source/beams.h>
#include <source/source.h>
#include <source/scan.h>
#include <source/driving.h>
#include <fpga/fpga.h>

BscanEncoderImageItem::BscanEncoderImageItem(const DplDisplay::PaletteColorPointer &palette,
                                     const DplDevice::GroupPointer &grp,
                                     QObject *parent) :
    EncoderImageItem(palette, grp, parent)
{
    set_driving(DplSource::Scan::instance()->scan_axis()->driving());
    init_encoder_properties();
    init_scan_properties();
    m_initFinished = true;
}


bool BscanEncoderImageItem::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(EncoderImageItem::need_refresh(beams)) {
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


void BscanEncoderImageItem::set_vertical_image_data(int beamsShowedCount, const BaseImageItem::S_CommonProperties &commonProperties, BaseImageItem::E_BEAM_TYPE type, const DplSource::BeamsPointer &beamsPointer)
{
#if 1

    DplSource::BeamPointer beamPointer = beamsPointer->get(0);
    if(beamPointer.isNull()) {
        return;
    }

    const QByteArray &wave = beamPointer->wave();

    int pos = 0;

    if(type == LAST_BEAM) {
        for(int i = 0; i < m_image->height(); ++i) {

            quint8 *line    = (quint8*) m_image->scanLine(i);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                pos = m_image->width() - j - 1;
                if(pos >= m_image->width() || pos < 0) {
                    continue;
                }

                line[pos] = wave.at((int)(i * commonProperties.ratio));
            }
        }
    } else {
        for(int i = 0; i < m_image->height(); ++i) {

            quint8 *line    = (quint8*) m_image->scanLine(i);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                pos = (int)(beamsShowedCount * commonProperties.pixCount + j);

                if(pos >= m_image->width() || pos < 0) {
                    continue;
                }

                line[pos] = wave.at((int)(i * commonProperties.ratio));
            }
        }
    }

#else

    m_image->fill(0);
   for(int i = 0; i < m_image->height(); ++i) {
       quint8 *line    = (quint8*) m_image->scanLine(i);

       if((i == 0) || (i == (m_image->height() - 1))) {
           for(int k = 0; k < m_image->width(); ++k) {
               line[k] = 155;
           }
       } else {
           line[0] = 155;
           line[m_image->width() - 1] = 155;
       }
   }

#endif
}


