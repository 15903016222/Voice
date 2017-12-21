#ifndef __C_SCAN_IMAGE_H__
#define __C_SCAN_IMAGE_H__

#include <QImage>
#include <device/group.h>
#include <display/palette_color.h>
#include <source/beams.h>

class CscanImage : public QImage
{
public:
    CscanImage(const QSize &size, const DplDisplay::PaletteColorPointer &palette);
    ~CscanImage();

    void draw(const int *gates, int beamQty, int line);

    void shift(int lines);

    int max_lines() const;

    void clear();

protected:
    int max_value(const int *gates, int startBeam, int stopBeam) const;
    void draw_compress(const int *gates, int beamQty, int line);
    void draw_interpolation(const int *gates, int beamQty, int line);

private:
    DplDisplay::PaletteColorPointer m_palette;
    quint32 *m_image;
};

inline int CscanImage::max_lines() const
{
    return height();
}

inline void CscanImage::clear()
{
    fill(Qt::black);
}

#endif // __C_SCAN_IMAGE_H__
