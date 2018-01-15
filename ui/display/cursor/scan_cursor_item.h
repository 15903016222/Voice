#ifndef __SCAN_CURSOR_ITEM_H__
#define __SCAN_CURSOR_ITEM_H__

#include "axis_cursor_item.h"

class ScanCursorItem : public AxisCursorItem
{
    Q_OBJECT
public:
    ScanCursorItem(const DplMeasure::CursorPointer &cursor,
                   Qt::Orientation orientation,
                   QColor color);
};


#endif // __SCAN_CURSOR_ITEM_H__
