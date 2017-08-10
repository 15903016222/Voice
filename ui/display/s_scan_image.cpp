#include "s_scan_image.h"
#include <QThread>

SscanImage::SscanImage(const QSize &size) :
    QImage(size, QImage::Format_Indexed8),
    m_beamMark(new int[size.width()*size.height()]),
    m_pointMark(new int[size.width()*size.height()]),
    m_pointQty(0)
{
}

SscanImage::~SscanImage()
{
    delete m_beamMark;
    delete m_pointMark;
}

void SscanImage::draw_beams(const DplSource::BeamsPointer &beams)
{
    const quint8 *rawData = (quint8 *)beams->raw_data();
    int beamSize = beams->size() / beams->beam_qty();

    if (m_pointQty != beams->point_qty()) {
        m_pointQty = beams->point_qty();
        init_mark();
    }

    int w = width();
    int h = height();
    int pos = 0;
    quint8 *buf = NULL;

    for (int i = 0; i < h; ++i) {
        buf = scanLine(i);
        for (int j = 0; j < w; ++j) {
            pos = i*w + j;
            if (m_beamMark[pos] >= 0) {
                buf[j] = rawData[beamSize*m_beamMark[pos] + m_pointMark[pos]];
            }
        }
    }
}

void SscanImage::init_mark()
{
    int w = width();
    int h = height();

    float yRatio = m_pointQty * 1.0 / h;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            m_beamMark[i*w + j] = 0;
            m_pointMark[i*w + j] = yRatio * i + 0.5;
        }
    }
}
