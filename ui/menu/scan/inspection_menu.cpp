#include "inspection_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplScanMenu {

InspectionMenu::InspectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Scan Menu Item */
    m_scanItem = new ComboMenuItem;
    QStringList scanList;
    scanList.append(tr("Time"));
    scanList.append(tr("Encoder 1"));
    scanList.append(tr("Encoder 2"));
    m_scanItem->set(tr("Scan"), scanList);

    /* Type menu item */
    m_typeItem = new ComboMenuItem;
    QStringList typeList;
    typeList.append(tr("One Line"));
    typeList.append(tr("Raster Scan"));
    typeList.append(tr("Helicoidal Scan"));
    m_typeItem->set(tr("Type"), typeList);

    /* Max Scan Speed menu item */
    m_maxScanSpeedItem = new SpinMenuItem;
    m_maxScanSpeedItem->set(tr("Max Scan Speed"), "m/s", 0, 1000, 2);

    /* Max Scan Speed(rpm) Menu Item */
    m_maxScanSpeedRPMItem = new SpinMenuItem;
    m_maxScanSpeedRPMItem->set(tr("Max Scan Speed(rpm)"), "m/s", 0, 1000, 0);
}

InspectionMenu::~InspectionMenu()
{
    delete m_scanItem;
    delete m_typeItem;
    delete m_maxScanSpeedItem;
    delete m_maxScanSpeedRPMItem;
}

void InspectionMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_scanItem);
    ui->menuItem1->layout()->addWidget(m_typeItem);
    ui->menuItem2->layout()->addWidget(m_maxScanSpeedItem);
    ui->menuItem3->layout()->addWidget(m_maxScanSpeedRPMItem);
    m_scanItem->show();
    m_typeItem->show();
    m_maxScanSpeedItem->show();
    m_maxScanSpeedRPMItem->show();
}

void InspectionMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_scanItem);
    ui->menuItem1->layout()->removeWidget(m_typeItem);
    ui->menuItem2->layout()->removeWidget(m_maxScanSpeedItem);
    ui->menuItem3->layout()->removeWidget(m_maxScanSpeedRPMItem);
    m_scanItem->hide();
    m_typeItem->hide();
    m_maxScanSpeedItem->hide();
    m_maxScanSpeedRPMItem->hide();
}

}
