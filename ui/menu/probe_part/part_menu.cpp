#include "part_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplProbeMenu {

PartMenu::PartMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{

    m_geometryItem = new ComboMenuItem;
    m_thicknessItem = new SpinMenuItem;
    m_diameterItem = new SpinMenuItem;
    m_materialItem = new ComboMenuItem;
    m_overlayItem = new ComboMenuItem;

    /* Geometry menu item */
    QStringList geometrys;
    geometrys.append(tr("Plate"));
    geometrys.append(tr("ID"));
    geometrys.append(tr("OD"));
    m_geometryItem->set(tr("Geometry"), geometrys);

    /* Thickness menu item */
    m_thicknessItem->set(tr("Thickness"), "mm", 0.05, 1000, 2);

    /* Diameter menu item */
    m_diameterItem->set(tr("Diameter"), "mm", 0.05, 525, 2);

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
    m_materialItem->set(tr("Material"), materials);

    /* Overlay menu item */
    m_overlayItem->set(tr("Overlay"), s_onOff);
}

PartMenu::~PartMenu()
{
    delete m_geometryItem;
    delete m_thicknessItem;
    delete m_diameterItem;
    delete m_materialItem;
    delete m_overlayItem;
}

void PartMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_geometryItem);
    ui->menuItem1->layout()->addWidget(m_thicknessItem);
    ui->menuItem2->layout()->addWidget(m_diameterItem);
    ui->menuItem3->layout()->addWidget(m_materialItem);
    ui->menuItem4->layout()->addWidget(m_overlayItem);
    m_geometryItem->show();
    m_thicknessItem->show();
    m_diameterItem->show();
    m_materialItem->show();
    m_overlayItem->show();
}

void PartMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_geometryItem);
    ui->menuItem1->layout()->removeWidget(m_thicknessItem);
    ui->menuItem2->layout()->removeWidget(m_diameterItem);
    ui->menuItem3->layout()->removeWidget(m_materialItem);
    ui->menuItem4->layout()->removeWidget(m_overlayItem);
    m_geometryItem->hide();
    m_thicknessItem->hide();
    m_diameterItem->hide();
    m_materialItem->hide();
    m_overlayItem->hide();
}

}
