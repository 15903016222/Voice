/**
 * @file s_scan_image.cpp
 * @brief 画S-Scan图像类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-11-09
 */
#include "s_scan_image_p.h"

SscanImage::SscanImage(const DplDevice::GroupPointer &group,
                       const QSize &size,
                       const DplDisplay::PaletteColorPointer palette) :
    QImage(size, QImage::Format_RGB32),
    d(new SscanImagePrivate(this, group, palette))
{
}

SscanImage::~SscanImage()
{
    delete d;
}

void SscanImage::draw_beams(const DplSource::BeamsPointer &beams)
{
    QReadLocker l(&d->m_rwLock);
    quint32 *imageBits = (quint32 *)bits();
    const quint8 *rawData = (quint8 *)beams->raw_data();

    for (int i = 0; i < d->m_drawPointQty; ++i) {
        imageBits[d->m_pointSet[i].pos] = d->m_palette->pixmap(
                  d->m_pointSet[i].rate1 * rawData[d->m_pointSet[i].index1]
                + d->m_pointSet[i].rate2 * rawData[d->m_pointSet[i].index2]
                + d->m_pointSet[i].rate3 * rawData[d->m_pointSet[i].index3]
                + d->m_pointSet[i].rate4 * rawData[d->m_pointSet[i].index4]);
    }
}
