#include "advanced_menu.h"

namespace DplProbeMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Label,
    MenuItem::Label
};

AdvancedMenu::AdvancedMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    m_menuItem[0]->set(tr("Load Part"), "");

    /* Clear Part menu item */
    m_menuItem[1]->set(tr("Clear Part"), "");
}

}
