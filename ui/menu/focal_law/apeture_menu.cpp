#include "apeture_menu.h"

namespace DplFocalLawMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin
};

ApetureMenu::ApetureMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
            /* Apeture Menu Item */
            m_menuItem[0]->set(tr("Apeture"), "", 0, 64, 0);

            /* First Element menu item */
            m_menuItem[1]->set(tr("First Element"), "", 1, 64, 0);

            /* Last Element menu item */
            m_menuItem[2]->set(tr("Last Element"), "", 1, 64, 0);

            /* Element Step Menu Item */
            m_menuItem[3]->set(tr("Element Step"), "", 1, 32, 0);
}

}
