#include "angle_menu.h"
#include "spin_menu_item.h"

namespace DplFocalLawMenu {

AngleMenu::AngleMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Min.Angle Menu Item */
    m_minAngleItem = new SpinMenuItem;
    m_minAngleItem->set(tr("Min.Angle"), "°", 25, 75, 0);

    /* Max.Angle Menu Item */
    m_maxAngleItem = new SpinMenuItem;
    m_maxAngleItem->set(tr("Max.Angle"), "°", 25, 75, 0);

    /* Angle Step Menu Item */
    m_angleStepItem = new SpinMenuItem;
    m_angleStepItem->set(tr("Angle Step"), "°", 1, 10, 0);
}

AngleMenu::~AngleMenu()
{
    delete m_minAngleItem;
    delete m_maxAngleItem;
    delete m_angleStepItem;
}

void AngleMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_minAngleItem);
    ui->menuItem1->layout()->addWidget(m_maxAngleItem);
    ui->menuItem2->layout()->addWidget(m_angleStepItem);
    m_minAngleItem->show();
    m_maxAngleItem->show();
    m_angleStepItem->show();
}

void AngleMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_minAngleItem);
    ui->menuItem1->layout()->removeWidget(m_maxAngleItem);
    ui->menuItem2->layout()->removeWidget(m_angleStepItem);
    m_minAngleItem->hide();
    m_maxAngleItem->hide();
    m_angleStepItem->hide();
}

}
