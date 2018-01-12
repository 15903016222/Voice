#include "start_menu_item.h"

#include <global.h>
#include <device/device.h>
#include <ui/tool/tool.h>

StartMenuItem::StartMenuItem(QWidget *parent) :
    SpinMenuItem(parent, tr("Start"))
{
    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void StartMenuItem::update(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group*>(m_group.data()),
                SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                this, SLOT(update_unit(DplDevice::Group::UtUnit)));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(start_changed(float)),
                   this, SLOT(update_value()));
    }

    m_group = group;

    update_unit(m_group->ut_unit());

    connect(static_cast<DplDevice::Group*>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_unit(DplDevice::Group::UtUnit)));

    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_value()));
}

void StartMenuItem::update_unit(DplDevice::Group::UtUnit type)
{
    if (type == DplDevice::Group::Time) {
        set_unit(US_STR);
    } else {
        set_unit(MM_STR);
    }
    update_range();
}

void StartMenuItem::update_range()
{
    set(0,
        Tool::cnf_to_display(m_group, m_group->max_start()),
        2,
        Tool::cnf_to_display(m_group, m_group->sample()->precision()));
    update_value();
}

void StartMenuItem::update_value()
{
    set_value(Tool::cnf_to_display(m_group, m_group->sample()->start()));
}

void StartMenuItem::do_value_changed(double val)
{
    m_group->sample()->set_start(Tool::display_to_cnf(m_group, val));
}

void StartMenuItem::translate()
{
    set_title(tr("Start"));
}
