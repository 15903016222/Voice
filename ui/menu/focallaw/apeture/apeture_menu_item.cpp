#include "apeture_menu_item.h"

#include <device/device.h>

ApetureMenuItem::ApetureMenuItem(QWidget *parent) :
    SpinMenuItem(parent, tr("Apeture"))
{
    set_decimals(0);
    set_step(1);

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));
    do_group_changed(DplDevice::Device::instance()->current_group());
}

void ApetureMenuItem::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_focallawer) {
        connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
                SIGNAL(probe_changed(DplFocallaw::ProbePointer)),
                this, SLOT(do_probe_changed(DplDevice::GroupPointer)));
    }

    m_focallawer = group->focallawer();
    do_probe_changed(m_focallawer->probe());

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(probe_changed(DplFocallaw::ProbePointer)),
            this, SLOT(do_probe_changed(DplDevice::GroupPointer)));
}

void ApetureMenuItem::do_probe_changed(const DplFocallaw::ProbePointer &probe)
{
    if (m_probe) {
        disconnect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
                   SIGNAL(scan_configure_changed(DplFocallaw::ScanCnfPointer)),
                   this, SLOT(do_scan_changed(DplFocallaw::ScanCnfPointer)));
    }

    if (!probe->is_pa()) {
        setDisabled(true);
        m_probe.clear();
        m_scan.clear();
        return;
    }
    setDisabled(false);

    m_probe = probe.staticCast<DplFocallaw::PaProbe>();
    do_scan_changed(m_probe->scan_configure());

    connect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
            SIGNAL(scan_configure_changed(DplFocallaw::ScanCnfPointer)),
            this, SLOT(do_scan_changed(DplFocallaw::ScanCnfPointer)));
}

void ApetureMenuItem::do_scan_changed(const DplFocallaw::ScanCnfPointer &scan)
{
    if (m_scan) {
        disconnect(static_cast<DplFocallaw::ScanCnf *>(m_scan.data()),
                   SIGNAL(changed()),
                   this, SLOT(update_value()));
    }

    m_scan = scan;
    update_value();

    connect(static_cast<DplFocallaw::ScanCnf *>(m_scan.data()),
            SIGNAL(changed()),
            this, SLOT(update_value()));
}

void ApetureMenuItem::update_value()
{
    set_range(1, m_scan->element_qty());
    set_value(m_scan->aperture());
}

void ApetureMenuItem::do_value_changed(double val)
{
    m_scan->set_aperture(val);
    m_focallawer->focallaw();
}

void ApetureMenuItem::language_changed()
{
    set_title(tr("Apeture"));
}
