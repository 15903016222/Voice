#ifndef __B_SCAN_IMAGE_H__
#define __B_SCAN_IMAGE_H__

#include <QImage>
#include <device/group.h>
#include <display/palette_color.h>

class BscanImage : public QImage
{
public:
    BscanImage(const QSize &size, const DplDisplay::PaletteColorPointer &palette);
    ~BscanImage();

    void draw_wave(const QByteArray &wave, int line, bool rf=false);

    void shift(int lines);

    int max_lines() const;

    void clear();

protected:
    int max_amplitude(const QByteArray &beam, int startPoint, int stopPoint, bool rf);
    void draw_compress(const QByteArray &wave, int line, bool rf);
    void draw_interpolation(const QByteArray &wave, int line, bool rf);

private:
    DplDisplay::PaletteColorPointer m_palette;
    quint32 *m_image;
};

inline int BscanImage::max_lines() const
{
    return height();
}

inline void BscanImage::clear()
{
    fill(Qt::black);
}

#endif // __B_SCAN_IMAGE_H__
