#include "delay_menu_item.h"

#include <global.h>
#include <device/device.h>

DelayMenuItem::DelayMenuItem(QWidget *parent) :
    SpinMenuItem(parent)
{
    set_unit(US_STR);
    set(0, 1000, 2, 0.01);

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));

    update(DplDevice::Device::instance()->current_group());
}

void DelayMenuItem::update(const DplDevice::GroupPointer &group)
{
    m_group = group;

    double delay = m_group->focallawer()->wedge()->delay();
    set_value(Dpl::ns_to_us(delay));
}

void DelayMenuItem::do_value_changed(double val)
{
    m_group->focallawer()->wedge()->set_delay(Dpl::us_to_ns(val));
}

void DelayMenuItem::language_changed()
{
    set_title(tr("Wedge Delay"));
}
