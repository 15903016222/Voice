#include "gain_menu_item.h"

#include <device/device.h>

GainMenuItem::GainMenuItem(QWidget *parent) :
    SpinMenuItem(parent)
{
    set_title(tr("Gain"));
    set_unit("dB");

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void GainMenuItem::update(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(gain_changed(float)),
                   this, SLOT(do_gain_changed(float)));
    }

    m_group = group;

    if (m_group->mode() == DplDevice::Group::UT1
            || m_group->mode() == DplDevice::Group::UT2) {
        set(0, 110, 1, 0.1);
    } else {
        set(0, 80, 1, 0.1);
    }
    do_gain_changed(m_group->sample()->gain());

    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(gain_changed(float)),
            this, SLOT(do_gain_changed(float)));
}

void GainMenuItem::do_gain_changed(float val)
{
    disconnect(this, SIGNAL(value_changed(double)),
               this, SLOT(do_value_changed(double)));

    set_value(val);

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));
}

void GainMenuItem::do_value_changed(double val)
{
    m_group->sample()->set_gain(val);
}
