#ifndef __AMP_REF_CURSOR_ITEM_H__
#define __AMP_REF_CURSOR_ITEM_H__

#include "amp_cursor_item.h"

class AmpRefCursorItem : public AmpCursorItem
{
    Q_OBJECT
public:
    AmpRefCursorItem(const DplMeasure::CursorPointer &cursor,
                     Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;
};

#endif // __AMP_REF_CURSOR_ITEM_H__
