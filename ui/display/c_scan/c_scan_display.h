#ifndef __C_SCAN_DISPLAY_H__
#define __C_SCAN_DISPLAY_H__

#include "../base/scan_display.h"

#include <device/group.h>

class ScanRuler;
class IndexRuler;
class CscanItem;
class ScanRefCursorItem;
class ScanMeasCursorItem;

class CscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit CscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~CscanDisplay();

public slots:
    void resize_event(const QSize &size);

protected:
    ScanRefCursorItem * scan_reference_cursor_item() const;
    ScanMeasCursorItem * scan_measurement_cursor_item() const;

private:
    DplDevice::GroupPointer m_group;
    CscanItem *m_cscanItem;
    ScanRefCursorItem *m_scanRefCursorItem;
    ScanMeasCursorItem *m_scanMeasCursorItem;
};

inline ScanRefCursorItem *CscanDisplay::scan_reference_cursor_item() const
{
    return m_scanRefCursorItem;
}

inline ScanMeasCursorItem *CscanDisplay::scan_measurement_cursor_item() const
{
    return m_scanMeasCursorItem;
}

#endif // __C_SCAN_DISPLAY_H__
