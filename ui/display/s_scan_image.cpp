#include "s_scan_image.h"
#include "s_scan_image_p.h"
#include <QColor>
#include <qmath.h>

SscanImage::SscanImage(const DplDevice::GroupPointer &group, const QSize &size) :
    QImage(size, QImage::Format_Indexed8),
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
    quint8 *imageBits = bits();
    const quint8 *rawData = (quint8 *)beams->raw_data();
    int beamSize = beams->size() / beams->beam_qty();

#if 0
    QVector<QRgb> v = colorTable();
    int bytes = bytesPerLine();

    for (int i = 0; i < beams->beam_qty(); ++i) {
        for (int j = 0; j < beams->point_qty(); ++j) {
            QRgb rgb = v.at(rawData[beamSize*i+j]);
            imageBits[bytes*j + i*3] = qRed(rgb);
            imageBits[bytes*j + i*3+1] = qGreen(rgb);
            imageBits[bytes*j + i*3+2] = qBlue(rgb);
        }
    }
#endif

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

    for (int i = 0; i < d->m_drawPointQty; ++i) {
        imageBits[d->m_pointSet[i].pos] = d->m_pointSet[i].rate1*rawData[d->m_pointSet[i].index1]
                + d->m_pointSet[i].rate2 * rawData[d->m_pointSet[i].index2]
                + d->m_pointSet[i].rate3 * rawData[d->m_pointSet[i].index3]
                + d->m_pointSet[i].rate4 * rawData[d->m_pointSet[i].index4];
    }
}

void SscanImage::draw_sector(const DplSource::BeamsPointer &beams)
{
//    DplFocallaw::PaProbePointer probe = d->m_focallawer->probe().staticCast<DplFocallaw::PaProbe>();
//    DplFocallaw::SectorialScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
//    DplUt::SamplePointer sample = d->m_group->sample();

//    float angleStart = Dpl::degree2pi(scanCnf->first_angle());
//    float angleEnd = Dpl::degree2pi(scanCnf->last_angle());
//    float angleStep = Dpl::degree2pi(scanCnf->angle_step());

//    quint8 *imageBits = bits();
//    const quint8 *rawData = (quint8 *)beams->raw_data();

//    int beamQty = beams->beam_qty();
//    int pointQty = beams->point_qty();

//    int w1 = sample->range() * qFabs(qSin(angleStart));

//    for (int i = 0; i <beamQty ; ++i) {
//        w1 = sample->range() * qFabs(qSin(angleStart));
//        for (int j = 0; j < pointQty; ++j) {
//            w1 - j*
//        }
//    }

}
