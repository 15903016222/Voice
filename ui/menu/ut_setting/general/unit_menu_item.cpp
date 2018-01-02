#include "unit_menu_item.h"

#include <device/device.h>

UnitMenuItem::UnitMenuItem(QWidget *parent) :
    ComboMenuItem(parent)
{
    connect(this, SIGNAL(value_changed(int)),
            this, SLOT(do_value_changed(int)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));

    do_group_changed(DplDevice::Device::instance()->current_group());
}

void UnitMenuItem::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                   this, SLOT(update_value()));
    }

    m_group = group;
    update_value();

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_value()));
}

void UnitMenuItem::update_value()
{
    set_current_index(m_group->ut_unit());
}

void UnitMenuItem::do_value_changed(int index)
{
    m_group->set_ut_unit(static_cast<DplDevice::Group::UtUnit>(index));
}

void UnitMenuItem::language_changed()
{
    set_title(tr("Ut Unit"));

    set(QStringList());
    add_item(tr("Time"));
    add_item(tr("Sound Path"));
    add_item(tr("True Path"));

    do_group_changed(m_group);
}
