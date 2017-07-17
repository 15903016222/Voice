#include "inspection_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplScanMenu {

InspectionMenu::InspectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Scan Menu Item */
    QStringList scanList;
    scanList.append(tr("Time"));
    scanList.append(tr("Encoder 1"));
    scanList.append(tr("Encoder 2"));
    m_scanItem.set(tr("Scan"), scanList);

    /* Type menu item */
    QStringList typeList;
    typeList.append(tr("One Line"));
    typeList.append(tr("Raster Scan"));
    typeList.append(tr("Helicoidal Scan"));
    m_typeItem.set(tr("Type"), typeList);

    /* Max Scan Speed menu item */
    m_maxScanSpeedItem.set(tr("Max Scan Speed"), "m/s", 0, 1000, 2);

    /* Max Scan Speed(rpm) Menu Item */
    m_maxScanSpeedRPMItem.set(tr("Max Scan Speed(rpm)"), "m/s", 0, 1000, 0);
}

InspectionMenu::~InspectionMenu()
{
}

void InspectionMenu::show()
{
    ui->layout0->addWidget(&m_scanItem);
    ui->layout1->addWidget(&m_typeItem);
    ui->layout2->addWidget(&m_maxScanSpeedItem);
    ui->layout3->addWidget(&m_maxScanSpeedRPMItem);
    m_scanItem.show();
    m_typeItem.show();
    m_maxScanSpeedItem.show();
    m_maxScanSpeedRPMItem.show();
}

void InspectionMenu::hide()
{
    ui->layout0->removeWidget(&m_scanItem);
    ui->layout1->removeWidget(&m_typeItem);
    ui->layout2->removeWidget(&m_maxScanSpeedItem);
    ui->layout3->removeWidget(&m_maxScanSpeedRPMItem);
    m_scanItem.hide();
    m_typeItem.hide();
    m_maxScanSpeedItem.hide();
    m_maxScanSpeedRPMItem.hide();
}

}
