#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include "../base/scan_display.h"

#include "b_scan_item.h"

#include <device/group.h>

class UtRuler;
class ScanRuler;
class UtRefCursorItem;
class UtMeasCursorItem;
class ScanRefCursorItem;
class ScanMeasCursorItem;

class BscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~BscanDisplay();

protected slots:
    void resize_event(const QSize &size);

protected:
    ScanRefCursorItem * scan_reference_cursor_item() const;
    ScanMeasCursorItem * scan_measurement_cursor_item() const;

private:
    DplDevice::GroupPointer m_group;
    BscanItem *m_bscanItem;
    UtRefCursorItem *m_utRefCursorItem;
    UtMeasCursorItem *m_utMeasCursorItem;
    ScanRefCursorItem *m_scanRefCursorItem;
    ScanMeasCursorItem *m_scanMeasCursorItem;
};

inline ScanRefCursorItem *BscanDisplay::scan_reference_cursor_item() const
{
    return m_scanRefCursorItem;
}

inline ScanMeasCursorItem *BscanDisplay::scan_measurement_cursor_item() const
{
    return m_scanMeasCursorItem;
}

#endif // __B_SCAN_DISPLAY_H_
