#include "area_menu.h"

namespace DplScanMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin
};

AreaMenu::AreaMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Scan Start Menu Item */
    m_menuItem[0]->set(tr("Scan Start"), "mm", 0, 10000, 2);

    /* Scan End menu item */
    m_menuItem[1]->set(tr("Scan End"), "mm", 0, 10000, 2);

    /* Scan Resolution menu item */
    m_menuItem[2]->set(tr("Scan Resolution"), "mm", 0, 100, 2);

    /* Index Start Menu Item */
    m_menuItem[3]->set( tr("Index Start"), "mm", 0, 10000, 2);

    /* Index End Menu Item */
    m_menuItem[4]->set(tr("Index End"), "mm", 0, 10000, 2);

    /* Index Resolution Menu Item */
    m_menuItem[5]->set(tr("Index Resolution"), "mm", 0, 100, 2);
}

}
