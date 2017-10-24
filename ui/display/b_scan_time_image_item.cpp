#include "b_scan_time_image_item.h"
#include <QDebug>
#include <QByteArray>

#include <source/source.h>
#include <device/device.h>
#include <source/beams.h>
#include <source/scan.h>

BscanTimeImageItem::BscanTimeImageItem(const DplDisplay::PaletteColorPointer &palette,
                               const DplDevice::GroupPointer &grp,
                               QObject *parent) :
    TimeImageItem(palette, grp, parent)
{
    m_initFinished = true;
}

void BscanTimeImageItem::set_vertical_image_data(int beamsShowedCount,
                                             const BaseImageItem::S_CommonProperties &commonProperties,
                                             BaseImageItem::E_BEAM_TYPE type,
                                             const DplSource::BeamsPointer &beamsPointer)
{

#if 1
    DplSource::BeamPointer beamPointer = beamsPointer->get(0);
    if(beamPointer.isNull()) {
        return;
    }

    const QByteArray &wave = beamPointer->wave();
    int waveSize = wave.size();

    int pos = 0;
    if(type == LAST_BEAM) {
        for(int i = 0; i < m_image->height(); ++i) {

            quint8 *line    = (quint8*) m_image->scanLine(i);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                pos = m_image->width() - j - 1;

                if(pos >= m_image->width() || pos < 0) {
                    continue;
                }

                if(waveSize <= (int)(i * commonProperties.ratio)) {
                    continue;
                }

                line[pos] = wave.at((int)(i * commonProperties.ratio));
            }
        }
    } else {
        for(int i = 0; i < m_image->height(); ++i) {

            quint8 *line = (quint8*) m_image->scanLine(i);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                pos = (int)(beamsShowedCount * commonProperties.pixCount + j);

                if(pos >= m_image->width() || pos < 0) {
                    continue;
                }

                if(waveSize <= (int)(i * commonProperties.ratio)) {
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


bool BscanTimeImageItem::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(TimeImageItem::need_refresh(beams)) {
        return true;
    }
}

