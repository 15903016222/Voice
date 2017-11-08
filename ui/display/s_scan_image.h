#ifndef __S_SCAN_IMAGE_H__
#define __S_SCAN_IMAGE_H__

#include <QImage>
#include <device/group.h>

class SscanImagePrivate;
class SscanImage : public QImage
{
public:
    explicit SscanImage(const DplDevice::GroupPointer &group, const QSize &size);
    ~SscanImage();

    void draw_beams(const DplSource::BeamsPointer &beams);

    void draw_sector(const DplSource::BeamsPointer &beams);

private:
    SscanImagePrivate *d;
};

#endif // __S_SCAN_IMAGE_H__
