#include "law_config_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

#include "device/device.h"

namespace DplFocalLawMenu {

LawConfigMenu::LawConfigMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent),
    m_updateFlga(false),
    m_pulseConnectionItem(new SpinMenuItem),
    m_receiverConnectionItem(new SpinMenuItem),
    m_waveTypeItem(new ComboMenuItem)
{
    /* Law Type Menu Item */
    QStringList lawTypes;
    lawTypes.append(tr("Linear"));
    lawTypes.append(tr("Azimuthal"));
    m_lawTypeItem.set(tr("Law Type"), lawTypes);
    connect(&m_lawTypeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_lawTypeItem_changed(int)));

    /* Pulse Connection menu item */
    m_pulseConnectionItem->set(tr("Pulse Connection"), "1-113", 1, 113, 0);

    /* Receiver Connection menu item */
    m_receiverConnectionItem->set(tr("Receiver Connection"), "1-113", 1, 113, 0);

    /* Wave Type Menu Item */
    QStringList waveTypes;
    waveTypes.append(tr("LW"));
    waveTypes.append(tr("SW"));
    m_waveTypeItem->set(tr("Wave Type"), waveTypes);

    connect(DplDevice::Device::instance(), SIGNAL(current_group_changed()),
            this, SLOT(do_current_group_changed()));
    do_current_group_changed();
}

LawConfigMenu::~LawConfigMenu()
{
    delete m_pulseConnectionItem;
    delete m_receiverConnectionItem;
    delete m_waveTypeItem;
}

void LawConfigMenu::show()
{
    if (m_updateFlga) {
        update();
    }

    ui->menuItem0->layout()->addWidget(&m_lawTypeItem);
    ui->menuItem1->layout()->addWidget(m_pulseConnectionItem);
    ui->menuItem2->layout()->addWidget(m_receiverConnectionItem);
    ui->menuItem3->layout()->addWidget(m_waveTypeItem);
    m_lawTypeItem.show();
    m_pulseConnectionItem->show();
    m_receiverConnectionItem->show();
    m_waveTypeItem->show();
}

void LawConfigMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_lawTypeItem);
    ui->menuItem1->layout()->removeWidget(m_pulseConnectionItem);
    ui->menuItem2->layout()->removeWidget(m_receiverConnectionItem);
    ui->menuItem3->layout()->removeWidget(m_waveTypeItem);
    m_lawTypeItem.hide();
    m_pulseConnectionItem->hide();
    m_receiverConnectionItem->hide();
    m_waveTypeItem->hide();
}

void LawConfigMenu::update()
{
    m_lawTypeItem.set_current_index(m_scanScnPtr->mode());
    m_pulseConnectionItem->set_value(m_probePtr->pulser_index()+1);
    m_receiverConnectionItem->set_value(m_probePtr->receiver_index()+1);
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

void LawConfigMenu::do_current_group_changed()
{
    m_probePtr = DplDevice::Device::instance()->current_group()->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    m_scanScnPtr = m_probePtr->scan_configure().staticCast<DplFocallaw::ScanCnf>();

    if (m_lawTypeItem.isHidden()) {
        m_updateFlga = true;
    } else {
        update();
    }
}

}
