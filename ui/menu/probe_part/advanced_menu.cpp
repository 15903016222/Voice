#include "advanced_menu.h"
#include "label_menu_item.h"

namespace DplProbeMenu {

AdvancedMenu::AdvancedMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    m_loadPartItem.set(tr("Load Part"), "");

    /* Clear Part menu item */
    m_clearPartItem.set(tr("Clear Part"), "");
}

AdvancedMenu::~AdvancedMenu()
{
}

void AdvancedMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_loadPartItem);
    ui->menuItem1->layout()->addWidget(&m_clearPartItem);
    m_loadPartItem.show();
    m_clearPartItem.show();
}

void AdvancedMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_loadPartItem);
    ui->menuItem1->layout()->removeWidget(&m_clearPartItem);
    m_loadPartItem.hide();
    m_clearPartItem.hide();
}

}
