#include "gain_menu_item.h"

#include <device/device.h>

GainMenuItem::GainMenuItem(QWidget *parent) :
    SpinMenuItem(parent, tr("Gain"), "dB")
{
    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void GainMenuItem::update(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                SIGNAL(mode_changed(DplDevice::Group::Mode)),
                this, SLOT(update_range(DplDevice::Group::Mode)));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(gain_changed(float)),
                   this, SLOT(update_value(float)));
    }

    m_group = group;

    update_range(m_group->mode());

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(mode_changed(DplDevice::Group::Mode)),
            this, SLOT(update_range(DplDevice::Group::Mode)));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(gain_changed(float)),
            this, SLOT(update_value(float)));
}

void GainMenuItem::update_range(DplDevice::Group::Mode mode)
{
    if (DplDevice::Group::UT1 == mode
            || DplDevice::Group::UT2 == mode) {
        set(0, 110, 1, 0.1);
    } else {
        set(0, 80, 1, 0.1);
    }
    update_value(m_group->sample()->gain());
}

void GainMenuItem::update_value(float val)
{
    set_value(val);
}

void GainMenuItem::do_value_changed(double val)
{
    m_group->sample()->set_gain(val);
}

void GainMenuItem::translate()
{
    set_title(tr("Gain"));
}
