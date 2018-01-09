#ifndef __AMP_REF_CURSOR_ITEM_H__
#define __AMP_REF_CURSOR_ITEM_H__

#include "cursor_item.h"

class AmpRefCursorItem : public CursorItem
{
    Q_OBJECT
public:
    AmpRefCursorItem(const DplMeasure::CursorPointer &cursor,
                     Qt::Orientation orientation);

public slots:
    void update_position();
    void do_position_changed();
};

#endif // __AMP_REF_CURSOR_ITEM_H__
