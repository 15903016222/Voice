#ifndef __UT_MEAS_CURSOR_ITEM_H__
#define __UT_MEAS_CURSOR_ITEM_H__

#include "ut_cursor_item.h"

#include <device/group.h>

class UtMeasCursorItem : public UtCursorItem
{
    Q_OBJECT
public:
    UtMeasCursorItem(const DplDevice::GroupPointer &group,
                     Qt::Orientation orientation);

protected slots:
    void position_event();

protected:
    double ratio() const;

private:
    DplDevice::GroupPointer m_group;
};

#endif // __UT_MEAS_CURSOR_ITEM_H__
