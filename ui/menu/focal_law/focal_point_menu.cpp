#include "focal_point_menu.h"
#include "ui_base_menu.h"

namespace DplFocalLawMenu {

FocalPointMenu::FocalPointMenu(QWidget *parent) :
    BaseMenu(parent),
    m_typeItem(new ComboMenuItem(this, tr("Type"))),
    m_positionStartItem(new SpinMenuItem(this, tr("Position Start"), tr("mm"))),
    m_positionEndItem(new SpinMenuItem(this, tr("Position End"), tr("mm"))),
    m_offsetStartItem(new SpinMenuItem(this, tr("Offset Start"), tr("mm"))),
    m_offsetEndItem(new SpinMenuItem(this, tr("Offset End"), tr("mm")))
{
    ui->layout0->addWidget(m_typeItem);
    ui->layout1->addWidget(m_positionStartItem);
    ui->layout2->addWidget(m_positionEndItem);
    ui->layout3->addWidget(m_offsetStartItem);
    ui->layout4->addWidget(m_offsetEndItem);

    /* Type Menu Item */
    QStringList types;
    types.append(tr("True Depth"));
    types.append(tr("Half Path"));
    types.append(tr("Projection"));
    types.append(tr("Focal Plane"));
    types.append(tr("DDF"));
    m_typeItem->set(types);

    /* Position Start menu item */
    m_positionStartItem->set(0, 1000, 2);

    /* Position End menu item */
    m_positionEndItem->set(1, 1000, 2);

    /* Offset Start Menu Item */
    m_offsetStartItem->set(0, 1000, 2);

    /* Offset End Menu Item */
    m_offsetEndItem->set(1, 1000, 2);
}

FocalPointMenu::~FocalPointMenu()
{
}

}
