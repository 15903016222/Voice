#ifndef __AMP_MEAS_CURSOR_ITEM_H__
#define __AMP_MEAS_CURSOR_ITEM_H__

#include "cursor_item.h"

class AmpMeasCursorItem : public CursorItem
{
    Q_OBJECT
public:
    AmpMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                     Qt::Orientation orientation);

public slots:
    void update_position();
    void do_position_changed();
    void set_text(double val);
};

#endif // __AMP_MEAS_CURSOR_ITEM_H__
