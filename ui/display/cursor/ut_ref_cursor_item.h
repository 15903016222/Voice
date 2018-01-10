#ifndef __UT_REF_CURSOR_ITEM_H__
#define __UT_REF_CURSOR_ITEM_H__

#include "ut_cursor_item.h"

class UtRefCursorItem : public UtCursorItem
{
    Q_OBJECT
public:
    UtRefCursorItem(const DplDevice::GroupPointer &group,
                     Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;
};

#endif // __UT_REF_CURSOR_ITEM_H__
