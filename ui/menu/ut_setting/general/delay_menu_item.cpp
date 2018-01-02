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
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));

    do_group_changed(DplDevice::Device::instance()->current_group());
}

void DelayMenuItem::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_focallawer) {
        disconnect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
                   SIGNAL(wedge_changed(DplFocallaw::WedgePointer)),
                   this, SLOT(do_wedge_changed(DplFocallaw::WedgePointer)));
    }

    m_focallawer = group->focallawer();
    do_wedge_changed(m_focallawer->wedge());

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(wedge_changed(DplFocallaw::WedgePointer)),
            this, SLOT(do_wedge_changed(DplFocallaw::WedgePointer)));
}

void DelayMenuItem::do_wedge_changed(const DplFocallaw::WedgePointer &wedge)
{
    if (m_wedge) {
        disconnect(static_cast<DplFocallaw::Wedge *>(m_wedge.data()),
                   SIGNAL(delay_changed(int)),
                   this, SLOT(update_value()));
    }

    m_wedge = wedge;
    update_value();

    connect(static_cast<DplFocallaw::Wedge *>(m_wedge.data()),
            SIGNAL(delay_changed(int)),
            this, SLOT(update_value()));
}

void DelayMenuItem::update_value()
{
    set_value(Dpl::ns_to_us(m_wedge->delay()));
}

void DelayMenuItem::do_value_changed(double val)
{
    m_wedge->set_delay(Dpl::us_to_ns(val));
}

void DelayMenuItem::language_changed()
{
    set_title(tr("Wedge Delay"));
}
