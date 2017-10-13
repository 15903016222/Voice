#include "b_scan_time_scene.h"
#include <QDebug>
#include <QByteArray>

#include <source/source.h>
#include <device/device.h>
#include <source/beams.h>
#include <source/scan.h>


BscanTimeScene::BscanTimeScene(const DplDisplay::PaletteColorPointer &palette,
                               const DplDevice::GroupPointer &grp,
                               QObject *parent) :
    TimeScene(palette, grp, parent)
{
    m_driving = DplSource::Axis::TIMER;
}

void BscanTimeScene::set_vertical_image_data(int beamsShowedCount,
                                             const BaseScanScene::S_CommonProperties &commonProperties,
                                             BaseScanScene::E_BEAM_TYPE type,
                                             const DplSource::BeamsPointer &beamsPointer)
{
    int pos = 0;
    for(int i = 0; i < m_image->height(); ++i) {

        quint8 *line    = (quint8*) m_image->scanLine(i);

        for(int j = 0; j < commonProperties.pixCount; ++j) {

            if(type == LAST_BEAM) {
                pos = m_image->width() - j - 1;
            } else {
                pos = (int)(beamsShowedCount * commonProperties.pixCount + j);
            }

            if(pos >= m_image->width() || pos < 0) {
                qDebug() << "[" << __FUNCTION__ << "]" << " last beam error pos = " << pos;
                continue;
            }

            line[pos] = beamsPointer->get(0)->wave().at((int)(i * commonProperties.ratio));
        }
    }
}


bool BscanTimeScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(TimeScene::need_refresh(beams)) {
        return true;
    }
}

