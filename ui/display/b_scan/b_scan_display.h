#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include "../base/scan_display.h"

#include "b_scan_item.h"

#include <device/group.h>

class UtRuler;
class ScanRuler;

class BscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~BscanDisplay();

protected slots:
    void resize_event(const QSize &size);

protected:
    BscanItem *m_bscanItem;

private:
    DplDevice::GroupPointer m_group;
};

#endif // __B_SCAN_DISPLAY_H_
