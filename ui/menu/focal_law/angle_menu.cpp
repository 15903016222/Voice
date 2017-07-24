#include "angle_menu.h"
#include "ui_base_menu.h"

namespace DplFocalLawMenu {

AngleMenu::AngleMenu(QWidget *parent) :
    BaseMenu(parent),
    m_minAngleItem(new SpinMenuItem(this, tr("Min"), tr("&#176;"))),
    m_maxAngleItem(new SpinMenuItem(this, tr("Max"), tr("&#176;"))),
    m_angleStepItem(new SpinMenuItem(this, tr("Step"),tr("&#176;")))
{
    ui->layout0->addWidget(m_minAngleItem);
    ui->layout1->addWidget(m_maxAngleItem);
    ui->layout2->addWidget(m_angleStepItem);

    /* Min.Angle Menu Item */
    m_minAngleItem->set(25, 75, 0);

    /* Max.Angle Menu Item */
    m_maxAngleItem->set(25, 75, 0);

    /* Angle Step Menu Item */
    m_angleStepItem->set(1, 10, 0);
}

AngleMenu::~AngleMenu()
{
}

}
