#ifndef __UT_MENU_ITEM_H__
#define __UT_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"
#include <device/group.h>

class UtMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    UtMenuItem(QWidget *parent, const QString &title);

    const DplDevice::GroupPointer &group() const;

protected slots:
    void update_group();
    void update_unit(DplDevice::Group::UtUnit type);
    void update_range();
    virtual void update_value() = 0;

protected:
    virtual void cursor_change_event(const DplMeasure::CursorPointer &cursor)=0;

private:
    DplDevice::GroupPointer m_group;
};

inline const DplDevice::GroupPointer &UtMenuItem::group() const
{
    return m_group;
}

#endif // __UT_MENU_ITEM_H__
