#include "range_menu_item.h"

#include <global.h>
#include <device/device.h>
#include <ui/tool/tool.h>

RangeMenuItem::RangeMenuItem(QWidget *parent) :
    SpinMenuItem(parent, tr("Range"))
{
    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void RangeMenuItem::update(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group*>(m_group.data()),
                SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                this, SLOT(update_unit(DplDevice::Group::UtUnit)));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(range_changed(float)),
                   this, SLOT(update_value()));
    }

    m_group = group;

    update_unit(m_group->ut_unit());

    connect(static_cast<DplDevice::Group*>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_unit(DplDevice::Group::UtUnit)));

    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_value()));
}

void RangeMenuItem::update_unit(DplDevice::Group::UtUnit type)
{
    if (type == DplDevice::Group::Time) {
        set_unit(US_STR);
    } else {
        set_unit(MM_STR);
    }
    update_range();
}

void RangeMenuItem::update_range()
{
    double max = m_group->sample()->point_qty() * m_group->sample()->precision() * DplUt::Sample::MAX_SCALE_FACTOR;
    if (max > m_group->max_range()) {
        max = m_group->max_range();
    }

    double min = 0.0;
    double step = 0.0;
    if (m_group->sample()->is_auto_set_point_qty()) {
        min = 32 * m_group->sample()->precision() * 1;
        step = m_group->sample()->precision();
    } else {
        min = m_group->sample()->point_qty() * m_group->sample()->precision() * 1;
        step = m_group->sample()->point_qty() * m_group->sample()->precision();
    }

    set(Tool::cnf_to_display(m_group, min),
        Tool::cnf_to_display(m_group, max),
        2,
        Tool::cnf_to_display(m_group, step));

    update_value();
}

void RangeMenuItem::update_value()
{
    set_value(Tool::cnf_to_display(m_group, m_group->sample()->range()));
}

void RangeMenuItem::do_value_changed(double val)
{
    m_group->sample()->set_range(Tool::display_to_cnf(m_group, val));
}

void RangeMenuItem::translate()
{
    set_title(tr("Range"));
}
