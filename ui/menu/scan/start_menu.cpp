#include "start_menu.h"

namespace DplScanMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Combo
};

StartMenu::StartMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Start Menu Item */
    m_menuItem[0]->set(tr("Scan"), "mm", 0, 10000, 2);

    /* Pause menu item */
    m_menuItem[1]->set(tr("Pause"), s_onOff);
}

}
