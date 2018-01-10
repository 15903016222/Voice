#ifndef __UT_CURSOR_ITEM_H__
#define __UT_CURSOR_ITEM_H__

#include "cursor_item.h"

#include <device/group.h>

class UtCursorItem : public CursorItem
{
    Q_OBJECT
public:
    UtCursorItem(const DplDevice::GroupPointer &group,
                 Qt::Orientation orientation,
                 QColor color);

public:
    const DplDevice::GroupPointer &group() const;

public slots:
    void set_text(double val);

protected slots:
    void update_background_color(DplDevice::Group::UtUnit unit);

protected:
    double value() const;

private:
    DplDevice::GroupPointer m_group;
};

inline const DplDevice::GroupPointer &UtCursorItem::group() const
{
    return m_group;
}

#endif // __UT_CURSOR_ITEM_H__
