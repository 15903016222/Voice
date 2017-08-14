#ifndef __S_SCAN_IMAGE_H__
#define __S_SCAN_IMAGE_H__

#include <QImage>
#include <source/beams.h>
#include <source/source.h>
class SscanImage : public QImage
{
public:
    explicit SscanImage(const QSize &size);
    ~SscanImage();

    void draw_beams(const DplSource::BeamsPointer &beams);

protected:
    void init_mark();

private:
    int *m_beamMark;
    int *m_pointMark;

    int m_pointQty;
};

#endif // __S_SCAN_IMAGE_H__
