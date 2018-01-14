#include "ut_menu_item.h"

#include <global.h>
#include <device/device.h>

UtMenuItem::UtMenuItem(QWidget *parent, const QString &title) :
    SpinMenuItem(parent, title)
{
    set_decimals(2);
    set_step(0.01);
    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update_group()));
}

void UtMenuItem::update_group()
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                   this, SLOT(update_unit(DplDevice::Group::UtUnit)));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(start_changed(float)),
                   this, SLOT(update_range()));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(range_changed(float)),
                   this, SLOT(update_range()));
    }

    m_group = DplDevice::Device::instance()->current_group();

    cursor_change_event(m_group->cursor());

    update_unit(m_group->ut_unit());

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_unit(DplDevice::Group::UtUnit)));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_range()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_range()));
}

void UtMenuItem::update_unit(DplDevice::Group::UtUnit type)
{
    if (type == DplDevice::Group::Time) {
        set_unit(US_STR);
    } else {
        set_unit(MM_STR);
    }
    update_range();
}

void UtMenuItem::update_range()
{
    set_range(m_group->sample()->start(),
              m_group->sample()->start() + m_group->sample()->range());
    update_value();
}

void UtMenuItem::cursor_change_event(const DplMeasure::CursorPointer &cursor)
{
    Q_UNUSED(cursor);
}
