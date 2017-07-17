#include "part_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplProbeMenu {

PartMenu::PartMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Geometry menu item */
    QStringList geometrys;
    geometrys.append(tr("Plate"));
    geometrys.append(tr("ID"));
    geometrys.append(tr("OD"));
    m_geometryItem.set(tr("Geometry"), geometrys);

    /* Thickness menu item */
    m_thicknessItem.set(tr("Thickness"), "mm", 0.05, 1000, 2);

    /* Diameter menu item */
    m_diameterItem.set(tr("Diameter"), "mm", 0.05, 525, 2);

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
    m_materialItem.set(tr("Material"), materials);

    /* Overlay menu item */
    m_overlayItem.set(tr("Overlay"), s_onOff);
}

PartMenu::~PartMenu()
{
}

void PartMenu::show()
{
    ui->layout0->addWidget(&m_geometryItem);
    ui->layout1->addWidget(&m_thicknessItem);
    ui->layout2->addWidget(&m_diameterItem);
    ui->layout3->addWidget(&m_materialItem);
    ui->layout4->addWidget(&m_overlayItem);
    m_geometryItem.show();
    m_thicknessItem.show();
    m_diameterItem.show();
    m_materialItem.show();
    m_overlayItem.show();
}

void PartMenu::hide()
{
    ui->layout0->removeWidget(&m_geometryItem);
    ui->layout1->removeWidget(&m_thicknessItem);
    ui->layout2->removeWidget(&m_diameterItem);
    ui->layout3->removeWidget(&m_materialItem);
    ui->layout4->removeWidget(&m_overlayItem);
    m_geometryItem.hide();
    m_thicknessItem.hide();
    m_diameterItem.hide();
    m_materialItem.hide();
    m_overlayItem.hide();
}

}
