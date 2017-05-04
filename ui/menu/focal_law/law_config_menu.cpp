#include "law_config_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

namespace DplFocalLawMenu {

LawConfigMenu::LawConfigMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Law Type Menu Item */
    m_lawTypeItem = new ComboMenuItem;
    QStringList lawTypes;
    lawTypes.append(tr("Azimuthal"));
    lawTypes.append(tr("Linear"));
    m_lawTypeItem->set(tr("Law Type"), lawTypes);

    /* Pulse Connection menu item */
    m_pulseConnectionItem = new SpinMenuItem;
    m_pulseConnectionItem->set(tr("Pulse Connection"), "1-113", 1, 113, 0);
    m_pulseConnectionItem->set_value(1);

    /* Receiver Connection menu item */
    m_receiverConnectionItem = new SpinMenuItem;
    m_receiverConnectionItem->set(tr("Receiver Connection"), "1-113", 1, 113, 0);
    m_receiverConnectionItem->set_value(1);

    /* Wave Type Menu Item */
    m_waveTypeItem = new ComboMenuItem;
    QStringList waveTypes;
    waveTypes.append(tr("LW"));
    waveTypes.append(tr("SW"));
    m_waveTypeItem->set(tr("Wave Type"), waveTypes);
}

LawConfigMenu::~LawConfigMenu()
{
    delete m_lawTypeItem;
    delete m_pulseConnectionItem;
    delete m_receiverConnectionItem;
    delete m_waveTypeItem;
}

void LawConfigMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_lawTypeItem);
    ui->menuItem1->layout()->addWidget(m_pulseConnectionItem);
    ui->menuItem2->layout()->addWidget(m_receiverConnectionItem);
    ui->menuItem3->layout()->addWidget(m_waveTypeItem);
    m_lawTypeItem->show();
    m_pulseConnectionItem->show();
    m_receiverConnectionItem->show();
    m_waveTypeItem->show();
}

void LawConfigMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_lawTypeItem);
    ui->menuItem1->layout()->removeWidget(m_pulseConnectionItem);
    ui->menuItem2->layout()->removeWidget(m_receiverConnectionItem);
    ui->menuItem3->layout()->removeWidget(m_waveTypeItem);
    m_lawTypeItem->hide();
    m_pulseConnectionItem->hide();
    m_receiverConnectionItem->hide();
    m_waveTypeItem->hide();
}

}
