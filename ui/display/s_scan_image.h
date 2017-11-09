#ifndef __S_SCAN_IMAGE_H__
#define __S_SCAN_IMAGE_H__

#include <QImage>
#include <device/group.h>
#include <display/palette_color.h>

class SscanImagePrivate;
class SscanImage : public QImage
{
public:
    explicit SscanImage(const DplDevice::GroupPointer &group, const QSize &size, const DplDisplay::PaletteColorPointer palette);
    ~SscanImage();

    void draw_beams(const DplSource::BeamsPointer &beams);

private:
    SscanImagePrivate *d;
};

#endif // __S_SCAN_IMAGE_H__
