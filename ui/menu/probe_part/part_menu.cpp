#include "part_menu.h"
#include "ui_base_menu.h"

namespace DplProbeMenu {

PartMenu::PartMenu(QWidget *parent) :
    BaseMenu(parent),
    m_geometryItem(new ComboMenuItem(this, tr("Geometry"))),
    m_thicknessItem(new SpinMenuItem(this, tr("Thickness"), "mm")),
    m_diameterItem(new SpinMenuItem(this, tr("Diameter"), tr("mm"))),
    m_materialItem(new ComboMenuItem(this, tr("Material"))),
    m_overlayItem(new ComboMenuItem(this, tr("Overlay")))
{
    ui->layout0->addWidget(m_geometryItem);
    ui->layout1->addWidget(m_thicknessItem);
    ui->layout2->addWidget(m_diameterItem);
    ui->layout3->addWidget(m_materialItem);
    ui->layout4->addWidget(m_overlayItem);

    /* Geometry menu item */
    QStringList geometrys;
    geometrys.append(tr("Plate"));
    geometrys.append(tr("ID"));
    geometrys.append(tr("OD"));
    m_geometryItem->set(geometrys);

    /* Thickness menu item */
    m_thicknessItem->set(0.05, 1000, 2);

    /* Diameter menu item */
    m_diameterItem->set(0.05, 525, 2);

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
    m_materialItem->set(materials);

    /* Overlay menu item */
    m_overlayItem->set(s_onOff);
}

PartMenu::~PartMenu()
{
}

}
