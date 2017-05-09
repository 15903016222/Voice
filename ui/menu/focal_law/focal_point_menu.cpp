#include "focal_point_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

namespace DplFocalLawMenu {

FocalPointMenu::FocalPointMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Type Menu Item */
    QStringList types;
    types.append(tr("True Depth"));
    types.append(tr("Half Path"));
    types.append(tr("Projection"));
    types.append(tr("Focal Plane"));
    types.append(tr("DDF"));
    m_typeItem.set(tr("Type"), types);

    /* Position Start menu item */
    m_positionStartItem.set(tr("Position Start"), "mm", 0, 1000, 2);

    /* Position End menu item */
    m_positionEndItem.set(tr("Position End"), "mm", 1, 1000, 2);

    /* Offset Start Menu Item */
    m_offsetStartItem.set(tr("Offset Start"), "mm", 0, 1000, 2);

    /* Offset End Menu Item */
    m_offsetEndItem.set(tr("Offset End"), "mm", 1, 1000, 2);
}

FocalPointMenu::~FocalPointMenu()
{
}

void FocalPointMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_typeItem);
    ui->menuItem1->layout()->addWidget(&m_positionStartItem);
    ui->menuItem2->layout()->addWidget(&m_positionEndItem);
    ui->menuItem3->layout()->addWidget(&m_offsetStartItem);
    ui->menuItem4->layout()->addWidget(&m_offsetEndItem);
    m_typeItem.show();
    m_positionStartItem.show();
    m_positionEndItem.show();
    m_offsetStartItem.show();
    m_offsetEndItem.show();
}

void FocalPointMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_typeItem);
    ui->menuItem1->layout()->removeWidget(&m_positionStartItem);
    ui->menuItem2->layout()->removeWidget(&m_positionEndItem);
    ui->menuItem3->layout()->removeWidget(&m_offsetStartItem);
    ui->menuItem4->layout()->removeWidget(&m_offsetEndItem);
    m_typeItem.hide();
    m_positionStartItem.hide();
    m_positionEndItem.hide();
    m_offsetStartItem.hide();
    m_offsetEndItem.hide();
}

}
