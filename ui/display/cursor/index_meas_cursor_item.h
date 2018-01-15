#ifndef __INDEX_MEAS_CURSOR_ITEM_H__
#define __INDEX_MEAS_CURSOR_ITEM_H__

#include "index_cursor_item.h"

class IndexMeasCursorItem : public IndexCursorItem
{
    Q_OBJECT
public:
    IndexMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                      Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;
};

#endif // __INDEX_MEAS_CURSOR_ITEM_H__
