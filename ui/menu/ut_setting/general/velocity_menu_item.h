#ifndef __VELOCITY_MENU_ITEM_H__
#define __VELOCITY_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class VelocityMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    VelocityMenuItem(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_specimen_changed(const DplFocallaw::SpecimenPointer &specimen);

    void update_value();
    void do_value_changed(double val);

protected:
    void translate();

private:
    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::SpecimenPointer m_specimen;
};

#endif // __VELOCITY_MENU_ITEM_H__
