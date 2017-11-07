#include "s_scan_image.h"
#include "s_scan_image_p.h"
#include <QColor>
#include <qmath.h>

SscanImage::SscanImage(const DplDevice::GroupPointer &group, const QSize &size) :
    QImage(size, QImage::Format_Indexed8),
//    QImage(size, QImage::Format_RGB16),
    d(new SscanImagePrivate(group))
{
    fill(0);
}

SscanImage::~SscanImage()
{
    delete d;
}

void SscanImage::draw_beams(const DplSource::BeamsPointer &beams)
{
    int beamSize = beams->size() / beams->beam_qty();

    if (d->m_pointQty != beams->point_qty()
            || d->m_beamQty != beams->beam_qty()) {
        d->m_pointQty = beams->point_qty();
        d->m_beamQty = beams->beam_qty();

        DplFocallaw::PaProbePointer probe = d->m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
        if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
            d->init_linear_matrix(d->m_beamQty, d->m_pointQty, beamSize, width(), height(), bytesPerLine());
        } else {
            d->init_sector_pointSet(width(), height(), bytesPerLine());
        }
    }

    quint8 *imageBits = bits();
    const quint8 *rawData = (quint8 *)beams->raw_data();

    for (int i = 0; i < d->m_drawPointQty; ++i) {
        imageBits[d->m_pointSet[i].pos] = d->m_pointSet[i].rate1*rawData[d->m_pointSet[i].index1]
                + d->m_pointSet[i].rate2 * rawData[d->m_pointSet[i].index2]
                + d->m_pointSet[i].rate3 * rawData[d->m_pointSet[i].index3]
                + d->m_pointSet[i].rate4 * rawData[d->m_pointSet[i].index4];
    }
}

void SscanImage::draw_linear(const DplSource::BeamsPointer &beams)
{

}

quint8 SscanImage::get_gray(const quint8 *raw, int beamSize, int x, int y)
{
    if (x >= d->m_beamQty) {
        x = d->m_beamQty - 1;
    }

    if (y >= d->m_pointQty) {
        y = d->m_pointQty - 1;
    }

    return raw[x*beamSize + y];
}
