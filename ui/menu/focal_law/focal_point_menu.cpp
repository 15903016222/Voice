#include "focal_point_menu.h"

namespace DplFocalLawMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin
};

FocalPointMenu::FocalPointMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Type Menu Item */
    QStringList types;
    types.append(tr("True Depth"));
    types.append(tr("Half Path"));
    types.append(tr("Projection"));
    types.append(tr("Focal Plane"));
    types.append(tr("DDF"));
    m_menuItem[0]->set(tr("Type"), types);

    /* Position Start menu item */
    m_menuItem[1]->set(tr("Position Start"), "mm", 0, 1000, 2);

    /* Position End menu item */
    m_menuItem[2]->set(tr("Position End"), "mm", 1, 1000, 2);

    /* Offset Start Menu Item */
    m_menuItem[3]->set(tr("Offset Start"), "mm", 0, 1000, 2);

    /* Offset End Menu Item */
    m_menuItem[4]->set(tr("Offset End"), "mm", 1, 1000, 2);
}

}
