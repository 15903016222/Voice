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
    ui->layout0->addWidget(&m_typeItem);
    ui->layout1->addWidget(&m_positionStartItem);
    ui->layout2->addWidget(&m_positionEndItem);
    ui->layout3->addWidget(&m_offsetStartItem);
    ui->layout4->addWidget(&m_offsetEndItem);
    m_typeItem.show();
    m_positionStartItem.show();
    m_positionEndItem.show();
    m_offsetStartItem.show();
    m_offsetEndItem.show();
}

void FocalPointMenu::hide()
{
    ui->layout0->removeWidget(&m_typeItem);
    ui->layout1->removeWidget(&m_positionStartItem);
    ui->layout2->removeWidget(&m_positionEndItem);
    ui->layout3->removeWidget(&m_offsetStartItem);
    ui->layout4->removeWidget(&m_offsetEndItem);
    m_typeItem.hide();
    m_positionStartItem.hide();
    m_positionEndItem.hide();
    m_offsetStartItem.hide();
    m_offsetEndItem.hide();
}

}
