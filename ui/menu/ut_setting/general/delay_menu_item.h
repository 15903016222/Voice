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
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_wedge_changed(const DplFocallaw::WedgePointer &wedge);

    void update_value();
    void do_value_changed(double val);

protected:
    void translate();

private:
    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::WedgePointer m_wedge;
};

#endif // __DELAY_MENU_ITEM_H__
