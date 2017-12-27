#ifndef __VPA_MENU_ITEM_H__
#define __VPA_MENU_ITEM_H__

#include "../menu_item/spin_menu_item.h"

#include <device/group.h>

class VpaMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    VpaMenuItem(QWidget *parent);

protected slots:
    void do_current_group_changed(const DplDevice::GroupPointer &group);

    void update_all();

    void update_for_ut();

    void update_for_pa();

    void update_value();

    void do_value_changed(double val);

private:
    DplDevice::GroupPointer m_group;
};

#endif // __VPA_MENU_ITEM_H__
