#include "law_config_menu.h"

#include "device/device.h"

#include <QEvent>

#include "../ut_setting/pulser/pulser_menu_item.h"
#include "../ut_setting/receiver/receiver_menu_item.h"

namespace DplFocalLawMenu {

LawConfigMenu::LawConfigMenu(QWidget *parent) :
    BaseMenu(parent),
    m_lawTypeItem(new ComboMenuItem(this, tr("Law Type"))),
    m_pulserItem(new PulserMenuItem(this)),
    m_receiverItem(new ReceiverMenuItem(this)),
    m_waveTypeItem(new ComboMenuItem(this, tr("Wave Type")))
{
    m_layout0->addWidget(m_lawTypeItem);
    m_layout1->addWidget(m_pulserItem);
    m_layout2->addWidget(m_receiverItem);
    m_layout3->addWidget(m_waveTypeItem);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));

    do_group_changed(DplDevice::Device::instance()->current_group());
}

void LawConfigMenu::do_group_changed(const DplDevice::GroupPointer &group)
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

void LawConfigMenu::do_probe_changed(const DplFocallaw::ProbePointer &probe)
{
    if (m_probe) {
        disconnect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
                   SIGNAL(scan_configure_changed(DplFocallaw::ScanCnfPointer)),
                   this, SLOT(update_lawTypeItem(DplFocallaw::ScanCnfPointer)));
    }

    if (!probe->is_pa()) {
        m_probe.clear();
        return;
    }

    m_probe = probe.staticCast<DplFocallaw::PaProbe>();
    update_lawTypeItem();
    update_waveTypeItem();

    connect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
            SIGNAL(scan_configure_changed(DplFocallaw::ScanCnfPointer)),
            this, SLOT(update_lawTypeItem()));
}

void LawConfigMenu::update_lawTypeItem()
{
    disconnect(m_lawTypeItem, SIGNAL(value_changed(int)),
               this, SLOT(do_lawTypeItem_changed(int)));

    m_lawTypeItem->clear();
    m_lawTypeItem->add_item(tr("Linear"));
    m_lawTypeItem->add_item(tr("Azimuthal"));
    m_lawTypeItem->set_current_index(m_probe->scan_configure()->mode());

    connect(m_lawTypeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_lawTypeItem_changed(int)));
}

void LawConfigMenu::update_waveTypeItem()
{
    m_waveTypeItem->clear();
    m_waveTypeItem->add_item(tr("LW"));
    m_waveTypeItem->add_item(tr("SW"));
}

void LawConfigMenu::do_lawTypeItem_changed(int index)
{
    if (index == DplFocallaw::ScanCnf::Linear) {
        m_probe->set_scan_configure(DplFocallaw::ScanCnfPointer(new DplFocallaw::LinearScanCnf(m_probe->element_qty())));
    } else if( index == DplFocallaw::ScanCnf::Sectorial) {
        m_probe->set_scan_configure(DplFocallaw::ScanCnfPointer(new DplFocallaw::SectorialScanCnf(m_probe->element_qty())));
    }
}

void LawConfigMenu::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        m_lawTypeItem->set_title(tr("Law Type"));
        update_lawTypeItem();
        return;
    }
    BaseMenu::changeEvent(e);
}

}
