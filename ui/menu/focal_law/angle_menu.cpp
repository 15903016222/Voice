#include "angle_menu.h"

namespace DplFocalLawMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin
};

AngleMenu::AngleMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
            /* Min.Angle Menu Item */
            m_menuItem[0]->set(tr("Min.Angle"), "°", 25, 75, 0);

            /* Max.Angle Menu Item */
            m_menuItem[1]->set(tr("Max.Angle"), "°", 25, 75, 0);

            /* Angle Step Menu Item */
            m_menuItem[2]->set(tr("Angle Step"), "°", 1, 10, 0);
}

}
