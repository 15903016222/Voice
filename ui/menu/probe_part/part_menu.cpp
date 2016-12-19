#include "part_menu.h"

namespace DplProbeMenu {

static const MenuItem::Type s_type[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Combo
};

PartMenu::PartMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_type, parent)
{

    /* Geometry menu item */
    QStringList geometrys;
    geometrys.append(tr("Plate"));
    geometrys.append(tr("ID"));
    geometrys.append(tr("OD"));
    m_menuItem[0]->set(tr("Geometry"), geometrys);

    /* Thickness menu item */
    m_menuItem[1]->set(tr("Thickness"), "mm", 0.05, 1000, 2);

    /* Diameter menu item */
    m_menuItem[2]->set(tr("Diameter"), "mm", 0.05, 525, 2);

    /* Material menu item */
    QStringList materials;
    materials.append(tr("Aluminum"));
    materials.append(tr("Steel Common"));
    materials.append(tr("Steel Stainless"));
    materials.append(tr("Brass"));
    materials.append(tr("Copper"));
    materials.append(tr("Iron"));
    materials.append(tr("Lead"));
    materials.append(tr("Nylon"));
    materials.append(tr("Silver"));
    materials.append(tr("Gold"));
    materials.append(tr("Zinc"));
    materials.append(tr("Titanium"));
    materials.append(tr("Tin"));
    materials.append(tr("Epoxy Resin"));
    materials.append(tr("Ice"));
    materials.append(tr("Nickel"));
    materials.append(tr("Plexiglass"));
    materials.append(tr("Polystyrene"));
    materials.append(tr("Orcelain"));
    materials.append(tr("PVC"));
    materials.append(tr("Quartz Glass"));
    materials.append(tr("Rubber Vulcanized"));
    materials.append(tr("Teflon"));
    materials.append(tr("Water"));
    m_menuItem[3]->set(tr("Material"), materials);

    /* Overlay menu item */
    m_menuItem[4]->set(tr("Overlay"), s_onOff);
}

}
