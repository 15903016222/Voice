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

protected:
    void draw_linear(const DplSource::BeamsPointer &beams);
    quint8 get_gray(const quint8 *raw, int beamSize, int x, int y);

private:
    SscanImagePrivate *d;
};

#endif // __S_SCAN_IMAGE_H__
