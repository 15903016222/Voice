#include "receiver_menu_item.h"

#include <device/device.h>

ReceiverMenuItem::ReceiverMenuItem(QWidget *parent) :
    SpinMenuItem(parent, tr("Receiver"), "1-113")
{
    set(1, 113, 0);
    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));

    do_group_changed(DplDevice::Device::instance()->current_group());
}

void ReceiverMenuItem::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_focallawer) {
        disconnect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
                   SIGNAL(probe_changed(DplFocallaw::ProbePointer)),
                   this, SLOT(do_probe_changed(DplFocallaw::ProbePointer)));
    }

    m_focallawer = group->focallawer();
    do_probe_changed(m_focallawer->probe());

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(probe_changed(DplFocallaw::ProbePointer)),
            this, SLOT(do_probe_changed(DplFocallaw::ProbePointer)));
}

void ReceiverMenuItem::do_probe_changed(const DplFocallaw::ProbePointer &probe)
{
    if (m_probe) {
        disconnect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
                   SIGNAL(receiver_index_changed(uint)),
                   this, SLOT(update_value(uint)));

    }

    setDisabled(!probe->is_pa());
    if (!probe->is_pa()) {
        m_probe.clear();
        return;
    }

    m_probe = probe.staticCast<DplFocallaw::PaProbe>();
    update_value(m_probe->receiver_index());

    connect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
            SIGNAL(receiver_index_changed(uint)),
            this, SLOT(update_value(uint)));
}

void ReceiverMenuItem::update_value(uint val)
{
    set_value(val+1);
}

void ReceiverMenuItem::do_value_changed(double val)
{
    m_probe->set_receiver_index(val-1);
}

void ReceiverMenuItem::language_changed()
{
    set_title(tr("Receiver"));
}
