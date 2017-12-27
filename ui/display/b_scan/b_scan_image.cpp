#include "b_scan_image.h"

BscanImage::BscanImage(const QSize &size, const DplDisplay::PaletteColorPointer &palette) :
    QImage(size, QImage::Format_RGB32),
    m_palette(palette),
    m_image((quint32 *)bits())
{
    clear();
}

BscanImage::~BscanImage()
{

}

void BscanImage::draw_wave(const QByteArray &wave, int line, bool rf)
{
    if (line < 0 || line >= height()){
        return;
    }

    if (width() > wave.size()) {
        draw_interpolation(wave, line, rf);
    } else if (width() < wave.size()) {
        draw_compress(wave, line, rf);
    } else {
        int offset = (height()-line-1) * width();
        for (int i = 0; i < width(); ++i) {
            m_image[offset+i] = m_palette->pixmap(wave[i]);
        }
    }
}

void BscanImage::shift(int lines)
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

int BscanImage::max_amplitude(const QByteArray &wave, int startPoint, int stopPoint, bool rf)
{
    int ret = wave[startPoint];
    if (rf) {
        ret = abs(ret - 128);
        for(int i = startPoint + 1; i <= stopPoint; ++i) {
            if (qAbs(wave[i] - 128) > ret) {
                ret = qAbs(wave[i] - 128);
            }
        }
    } else {
        for (int i = startPoint+1; i <= stopPoint; ++i) {
            if (wave[i] > ret) {
                ret = wave[i];
            }
        }
    }
    return ret;
}

void BscanImage::draw_compress(const QByteArray &wave, int line, bool rf)
{
    double ratio = (wave.size()-1.0) / width();
    int offset = (height()-line-1) * width();

    for(int i = 0; i < width(); ++i) {
        m_image[offset + i] = m_palette->pixmap(
                    max_amplitude(wave, i*ratio-0.5, (i+1)*ratio+0.5, rf));
    }
}

void BscanImage::draw_interpolation(const QByteArray &wave, int line, bool rf)
{
    double ratio = (wave.size()-1.0) / (width() - 1.0);
    int src = 0;
    double u = 0.0;
    int offset = (height()-line-1) * width();

    /* f'(src+u) = (1-u)f(src) + uf(src+1) */
    if (rf) {
        for (int i = 0; i < width(); ++i) {
            u = ratio * i;
            src = qFloor(u);
            u = u - src;
            if (src + 1 >= wave.size()) {
                m_image[offset+i] = m_palette->pixmap(qAbs(wave[wave.size()-1]-128));
            } else {
                m_image[offset+i] = m_palette->pixmap((1-u)*qAbs(wave[src]-128) + u*qAbs(wave[src+1]-128));
            }
        }
    } else {
        for (int i = 0; i < width(); ++i) {
            u = ratio * i;
            src = qFloor(u);
            u = u - src;
            if (src + 1 >= wave.size()) {
                m_image[offset+i] = m_palette->pixmap(wave[wave.size()-1]);
            } else {
                m_image[offset+i] = m_palette->pixmap((1-u)*wave[src] + u*wave[src+1]);
            }
        }
    }
}

