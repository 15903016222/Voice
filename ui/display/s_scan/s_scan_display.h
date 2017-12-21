#ifndef __S_SCAN_DISPLAY_H__
#define __S_SCAN_DISPLAY_H__

#include "../base/scan_display.h"
#include <device/group.h>
#include <QMutex>

class IndexRuler;
class UtRuler;

class VpaItem;
class SscanImage;

class SscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~SscanDisplay();

protected slots:
    void do_data_event(const DplSource::BeamsPointer &beams);

protected slots:
    void resize_event(const QSize &size);

private:
    DplDevice::GroupPointer m_group;

    IndexRuler *m_indexRuler;
    UtRuler *m_utRuler;

    VpaItem *m_vpaItem;
    DplDisplay::SscanPointer m_sScan;

    SscanImage *m_image;
    QMutex m_imageMutex;
};

#endif // __S_SCAN_DISPLAY_H__
