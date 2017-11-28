#include "law_config_menu.h"
#include "ui_base_menu.h"

#include "device/device.h"

namespace DplFocalLawMenu {

LawConfigMenu::LawConfigMenu(QWidget *parent) :
    BaseMenu(parent),
    m_lawTypeItem(new ComboMenuItem(this, tr("Law Type"))),
    m_pulseItem(new SpinMenuItem(this, tr("Pulse"), "1-113")),
    m_receiverItem(new SpinMenuItem(this, tr("Receiver"), "1-113")),
    m_waveTypeItem(new ComboMenuItem(this, tr("Wave Type")))
{
    ui->layout0->addWidget(m_lawTypeItem);
    ui->layout1->addWidget(m_pulseItem);
    ui->layout2->addWidget(m_receiverItem);
    ui->layout3->addWidget(m_waveTypeItem);

    /* Law Type Menu Item */
    QStringList lawTypes;
    lawTypes.append(tr("Linear"));
    lawTypes.append(tr("Azimuthal"));
    m_lawTypeItem->set(lawTypes);
    connect(m_lawTypeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_lawTypeItem_changed(int)));

    /* Pulse Connection menu item */
    m_pulseItem->set(1, 113, 0);
    connect(m_pulseItem, SIGNAL(value_changed(double)),
            this, SLOT(do_pulseItem_changed(double)));

    /* Receiver Connection menu item */
    m_receiverItem->set(1, 113, 0);
    connect(m_receiverItem, SIGNAL(value_changed(double)),
            this, SLOT(do_receiverItem_changed(double)));

    /* Wave Type Menu Item */
    m_waveTypeItem->add_item(tr("LW"));
    m_waveTypeItem->add_item(tr("SW"));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));

    update(DplDevice::Device::instance()->current_group());
}

LawConfigMenu::~LawConfigMenu()
{
}

void LawConfigMenu::do_lawTypeItem_changed(int index)
{
    if (index == m_scanScnPtr->mode()) {
        return;
    }

    if (index == DplFocallaw::ScanCnf::Linear) {
        DplFocallaw::LinearScanCnfPointer scanCnfPtr(new DplFocallaw::LinearScanCnf(m_probePtr->element_qty()));
        m_probePtr->set_scan_configure(scanCnfPtr.staticCast<DplFocallaw::ScanCnf>());
    } else if( index == DplFocallaw::ScanCnf::Sectorial) {
        DplFocallaw::SectorialScanCnfPointer scanCnfPtr(new DplFocallaw::SectorialScanCnf(m_probePtr->element_qty()));
        m_probePtr->set_scan_configure(scanCnfPtr.staticCast<DplFocallaw::ScanCnf>());
    }
}

void LawConfigMenu::do_pulseItem_changed(double val)
{
    m_probePtr->set_pulser_index(val);
}

void LawConfigMenu::do_receiverItem_changed(double val)
{
    m_probePtr->set_receiver_index(val);
}

void LawConfigMenu::update(const DplDevice::GroupPointer &group)
{
    m_probePtr = group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    m_scanScnPtr = m_probePtr->scan_configure().staticCast<DplFocallaw::ScanCnf>();

    m_lawTypeItem->set_current_index(m_scanScnPtr->mode());
    m_pulseItem->set_value(m_probePtr->pulser_index());
    m_receiverItem->set_value(m_probePtr->receiver_index());
}

}
