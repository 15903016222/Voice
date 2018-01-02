#include "velocity_menu_item.h"

#include <device/device.h>

VelocityMenuItem::VelocityMenuItem(QWidget *parent) :
    SpinMenuItem(parent)
{
    set_unit("m/s");
    set(635, 12540, 0);

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));
    do_group_changed(DplDevice::Device::instance()->current_group());
}

void VelocityMenuItem::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_focallawer) {
        disconnect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
                   SIGNAL(specimen_changed(DplFocallaw::SpecimenPointer)),
                   this, SLOT(do_specimen_changed(DplFocallaw::SpecimenPointer)));
    }

    m_focallawer = group->focallawer();
    do_specimen_changed(m_focallawer->specimen());

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(specimen_changed(DplFocallaw::SpecimenPointer)),
            this, SLOT(do_specimen_changed(DplFocallaw::SpecimenPointer)));
}

void VelocityMenuItem::do_specimen_changed(const DplFocallaw::SpecimenPointer &specimen)
{
    if (m_specimen) {
        disconnect(static_cast<DplFocallaw::Specimen *>(m_specimen.data()),
                   SIGNAL(velocity_changed(uint)),
                   this, SLOT(update_value()));
    }

    m_specimen = specimen;
    update_value();

    connect(static_cast<DplFocallaw::Specimen *>(m_specimen.data()),
            SIGNAL(velocity_changed(uint)),
            this, SLOT(update_value()));
}

void VelocityMenuItem::update_value()
{
    set_value(m_specimen->velocity());
}

void VelocityMenuItem::do_value_changed(double val)
{
    if (m_specimen) {
        m_specimen->set_velocity(val);
    }
}

void VelocityMenuItem::language_changed()
{
    set_title(tr("Velocity"));
}
