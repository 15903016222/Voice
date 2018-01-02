#include "velocity_menu_item.h"

#include <device/device.h>

VelocityMenuItem::VelocityMenuItem(QWidget *parent) :
    SpinMenuItem(parent)
{
    set_unit("m/s");
    set(635, 12540, 1, 0.1);

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void VelocityMenuItem::update(const DplDevice::GroupPointer &group)
{
    m_group = group;
    set_value(m_group->focallawer()->specimen()->velocity());
}

void VelocityMenuItem::do_value_changed(double val)
{
    if (m_group->focallawer()->specimen()) {
        m_group->focallawer()->specimen()->set_velocity(val);
    }
}

void VelocityMenuItem::language_changed()
{
    set_title(tr("Velocity"));
}
