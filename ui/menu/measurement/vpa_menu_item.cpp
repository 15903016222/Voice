#include "vpa_menu_item.h"

#include <global.h>
#include <device/device.h>

VpaMenuItem::VpaMenuItem(QWidget *parent) :
    SpinMenuItem(parent)
{
    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(do_current_group_changed(DplDevice::GroupPointer)));
    do_current_group_changed(DplDevice::Device::instance()->current_group());
}

void VpaMenuItem::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(mode_changed(DplDevice::Group::Mode)),
                   this, SLOT(update_all()));
        disconnect(static_cast<DplFocallaw::Focallawer *>(m_group->focallawer().data()),
                   SIGNAL(focallawed()),
                   this, SLOT(update_all()));
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(current_beam_changed(int)),
                   this, SLOT(update_value(int)));
    }

    m_group = group;

    update_all();

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(mode_changed(DplDevice::Group::Mode)),
            this, SLOT(update_all()));
    connect(static_cast<DplFocallaw::Focallawer *>(m_group->focallawer().data()),
            SIGNAL(focallawed()),
            this, SLOT(update_all()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(current_beam_changed(int)),
            this, SLOT(update_value()));
}

void VpaMenuItem::update_all()
{
    if (m_group->mode() == DplDevice::Group::PA) {
        update_for_pa();
    } else {
        update_for_ut();
    }
}

void VpaMenuItem::update_for_ut()
{
    setDisabled(true);

    set_title(tr("Angle"));
    set_unit(DEGREE_STR);
    set_range(1, 1);
}

void VpaMenuItem::update_for_pa()
{
    setDisabled(false);

    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        set_title("VPA");
        set_unit("");
        set_decimals(0);
        set_step(1);
        set_range(1, m_group->focallawer()->beam_qty());
    } else if(probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Sectorial) {
        DplFocallaw::SectorialScanCnfPointer cnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
        set_title(tr("Angle"));
        set_unit(DEGREE_STR);
        set_decimals(1);
        set_step(cnf->angle_step());
        set_range(cnf->first_angle(), cnf->last_angle());
    }
    update_value();
}

void VpaMenuItem::update_value()
{
    disconnect(this, SIGNAL(value_changed(double)),
               this, SLOT(do_value_changed(double)));

    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        set_value(m_group->current_beam_index()+1);
    } else if(probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Sectorial) {
        set_value(m_group->current_angle());
    }

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));
}

void VpaMenuItem::do_value_changed(double val)
{
    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        m_group->set_current_beam(val-1);
    } else if(probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Sectorial) {
        m_group->set_current_angle(val);
    }
}

void VpaMenuItem::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        if (m_group->mode() == DplDevice::Group::PA) {
            DplFocallaw::PaProbePointer probe =
                    m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
            if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
                set_title("VPA");
            } else if(probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Sectorial) {
                set_title(tr("Angle"));
            }
        } else {
            set_title(tr("Angle"));
        }
        return;
    }
    SpinMenuItem::changeEvent(e);
}
