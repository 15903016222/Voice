#include "start_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplScanMenu {

StartMenu::StartMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Start Menu Item */
    m_scanItem.set(tr("Scan"), "mm", 0, 10000, 2);

    /* Pause menu item */
    m_pauseItem.set(tr("Pause"), s_onOff);
}

StartMenu::~StartMenu()
{
}

void StartMenu::show()
{
    ui->layout0->addWidget(&m_scanItem);
    ui->layout1->addWidget(&m_pauseItem);
    m_scanItem.show();
    m_pauseItem.show();
}

void StartMenu::hide()
{
    ui->layout0->removeWidget(&m_scanItem);
    ui->layout1->removeWidget(&m_pauseItem);
    m_scanItem.hide();
    m_pauseItem.hide();
}

}
