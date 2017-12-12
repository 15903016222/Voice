#ifndef __S_SCAN_DISPLAY_H__
#define __S_SCAN_DISPLAY_H__

#include "../scan_display.h"
#include <device/group.h>
#include "vpa_item.h"


class ScanView;
class SscanScene;

class SscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~SscanDisplay();

protected slots:
    void do_data_event(const DplSource::BeamsPointer &beams);

protected:
    DplDevice::GroupPointer m_group;

protected slots:
    void update_rules();
    void do_size_changed(const QSize &size);

private:
    ScanView *m_view;
    SscanScene *m_scene;
    VpaItem *m_vpaItem;
    DplDisplay::SscanPointer m_sScan;
};

#endif // __S_SCAN_DISPLAY_H__
