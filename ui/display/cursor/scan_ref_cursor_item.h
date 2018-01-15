#ifndef __SCAN_REF_CURSOR_ITEM_H__
#define __SCAN_REF_CURSOR_ITEM_H__

#include "scan_cursor_item.h"

class ScanRefCursorItem : public ScanCursorItem
{
    Q_OBJECT
public:
    ScanRefCursorItem(const DplMeasure::CursorPointer &cursor,
                      Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;
};

#endif // __SCAN_REF_CURSOR_ITEM_H__
