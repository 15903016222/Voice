#ifndef __DELAY_MENU_ITEM_H__
#define __DELAY_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class DelayMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    DelayMenuItem(QWidget *parent);

protected slots:
    void update(const DplDevice::GroupPointer &group);

    void do_value_changed(double val);

protected:
    void language_changed();

private:
    DplDevice::GroupPointer m_group;
};

#endif // __DELAY_MENU_ITEM_H__
