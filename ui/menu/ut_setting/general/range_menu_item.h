#ifndef __RANGE_MENU_ITEM_H__
#define __RANGE_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class RangeMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    RangeMenuItem(QWidget *parent);

protected slots:
    void update(const DplDevice::GroupPointer &group);
    void update_unit(DplDevice::Group::UtUnit type);
    void update_range();
    void update_value();
    void do_value_changed(double val);

protected:
    void translate();

private:
    DplDevice::GroupPointer m_group;
};

#endif // __RANGE_MENU_ITEM_H__
