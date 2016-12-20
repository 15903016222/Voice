#include "start_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplScanMenu {

StartMenu::StartMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Start Menu Item */
    m_scanItem = new SpinMenuItem;
    m_scanItem->set(tr("Scan"), "mm", 0, 10000, 2);

    /* Pause menu item */
    m_pauseItem = new ComboMenuItem;
    m_pauseItem->set(tr("Pause"), s_onOff);
}

StartMenu::~StartMenu()
{
    delete m_scanItem;
    delete m_pauseItem;
}

void StartMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_scanItem);
    ui->menuItem1->layout()->addWidget(m_pauseItem);
    m_scanItem->show();
    m_pauseItem->show();
}

void StartMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_scanItem);
    ui->menuItem1->layout()->removeWidget(m_pauseItem);
    m_scanItem->hide();
    m_pauseItem->hide();
}

}
