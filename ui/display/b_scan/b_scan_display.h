#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include "../base/scan_display.h"

#include "b_scan_image.h"

#include <device/group.h>
#include <source/source.h>

#include <QMutex>

class UtRuler;
class ScanRuler;

class BscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~BscanDisplay();

public slots:
    void restart();

protected slots:
    void resize_event(const QSize &size);

    void do_data_event(const DplSource::BeamsPointer &beams);

private:
    DplDevice::GroupPointer m_group;
    DplSource::Source *m_source;

    BscanImage *m_image;
    QMutex m_imageMutex;
    int m_preIndex;
    int m_startIndex;
    int m_stopIndex;
};

#endif // __B_SCAN_DISPLAY_H_
