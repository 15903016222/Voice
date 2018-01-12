#ifndef __UNIT_MENU_ITEM_H__
#define __UNIT_MENU_ITEM_H__

#include "../../menu_item/combo_menu_item.h"

#include <device/group.h>

class UnitMenuItem : public ComboMenuItem
{
    Q_OBJECT
public:
    UnitMenuItem(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);

    void update_value();

    void do_value_changed(int index);

protected:
    void translate();

private:
    DplDevice::GroupPointer m_group;

};

#endif // __UNIT_MENU_ITEM_H__
