#ifndef __INDEX_CURSOR_ITEM_H__
#define __INDEX_CURSOR_ITEM_H__

#include "axis_cursor_item.h"


class IndexCursorItem : public AxisCursorItem
{
    Q_OBJECT
public:
    IndexCursorItem(const DplMeasure::CursorPointer &cursor,
                   Qt::Orientation orientation,
                   QColor color);
};


#endif // __INDEX_CURSOR_ITEM_H__
