#ifndef __AMP_MEAS_CURSOR_ITEM_H__
#define __AMP_MEAS_CURSOR_ITEM_H__

#include "amp_cursor_item.h"

class AmpMeasCursorItem : public AmpCursorItem
{
    Q_OBJECT
public:
    AmpMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                     Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;
};

#endif // __AMP_MEAS_CURSOR_ITEM_H__
