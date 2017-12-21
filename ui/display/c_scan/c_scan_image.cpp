#include "c_scan_image.h"

CscanImage::CscanImage(const QSize &size, const DplDisplay::PaletteColorPointer &palette) :
    QImage(size, QImage::Format_RGB32),
    m_palette(palette),
    m_image((quint32 *)bits())
{
}

CscanImage::~CscanImage()
{

}

void CscanImage::draw(const int *gates, int beamQty, int line)
{
    if (line < 0 || line >= height()){
        return;
    }

    if (width() > beamQty) {
        draw_interpolation(gates, beamQty, line);
    } else if (width() < beamQty) {
        draw_compress(gates, beamQty, line);
    } else {
        int offset = (height()-line-1) * width();
        for (int i = 0; i < width(); ++i) {
            m_image[offset+i] = m_palette->pixmap(gates[i]);
        }
    }
}

void CscanImage::shift(int lines)
{
    if (qAbs(lines) >= max_lines()) {
        clear();
        return;
    }

    quint8 buf[byteCount()];
    quint8 *image = bits();
    int offset = qAbs(lines) * bytesPerLine();
    ::memcpy(buf, image, byteCount());
    if (lines > 0) {
        ::memset(image, 0, offset);
        ::memcpy(image+offset, buf, byteCount()-offset);
    } else if ( lines < 0) {
        ::memcpy(image, buf+offset, byteCount()-offset);
        ::memset(image+byteCount()-offset, 0, offset);
    }
}

int CscanImage::max_value(const int *gates, int startBeam, int stopBeam) const
{
    int ret = gates[startBeam];
    for (int i = startBeam+1; i < stopBeam; ++i) {
        if (gates[i] > ret) {
            ret = gates[i];
        }
    }
    return ret;
}

void CscanImage::draw_compress(const int *gates, int beamQty, int line)
{
    double ratio = (beamQty-1.0) / (width()-1);
    int offset = (height()-line-1) * width();

    for(int i = 0; i < width(); ++i) {
        qDebug("%s[%d]: %d",__func__, __LINE__, max_value(gates, i*ratio, (i+1)*ratio));
        m_image[offset + i] = m_palette->pixmap(max_value(gates, i*ratio, (i+1)*ratio));
    }
}

void CscanImage::draw_interpolation(const int *gates, int beamQty, int line)
{
    double ratio = (beamQty-1.0) / (width() - 1.0);
    int src = 0;
    double u = 0.0;
    int offset = (height()-line-1) * width();

    /* f'(src+u) = (1-u)f(src) + uf(src+1) */
    for (int i = 0; i < width(); ++i) {
        u = ratio * i;
        src = qFloor(u);
        u = u - src;
        if (src + 1 >= beamQty) {
            m_image[offset+i] = m_palette->pixmap(gates[beamQty-1]);
        } else {
            m_image[offset+i] = m_palette->pixmap((1-u)*gates[src] + u*gates[src+1]);
        }
    }
}

