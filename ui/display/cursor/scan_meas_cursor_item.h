#ifndef __SCAN_MEAS_CURSOR_ITEM_H__
#define __SCAN_MEAS_CURSOR_ITEM_H__

#include "scan_cursor_item.h"

class ScanMeasCursorItem : public ScanCursorItem
{
    Q_OBJECT
public:
    ScanMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                      Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;
};

#endif // __SCAN_MEAS_CURSOR_ITEM_H__
