#include "inspection_menu.h"
#include "ui_base_menu.h"

namespace DplScanMenu {

InspectionMenu::InspectionMenu(QWidget *parent) :
    BaseMenu(parent),
    m_scanItem(new ComboMenuItem(this, tr("Scan"))),
    m_typeItem(new ComboMenuItem(this, tr("Type"))),
    m_maxScanSpeedItem(new SpinMenuItem(this, tr("Max Scan Speed"), tr("m/s"))),
    m_maxScanSpeedRPMItem(new SpinMenuItem(this, tr("Max Scan Speed(rpm)"), tr("m/s")))
{
    ui->layout0->addWidget(m_scanItem);
    ui->layout1->addWidget(m_typeItem);
    ui->layout2->addWidget(m_maxScanSpeedItem);
    ui->layout3->addWidget(m_maxScanSpeedRPMItem);

    /* Scan Menu Item */
    QStringList scanList;
    scanList.append(tr("Time"));
    scanList.append(tr("Encoder 1"));
    scanList.append(tr("Encoder 2"));
    m_scanItem->set(scanList);

    /* Type menu item */
    QStringList typeList;
    typeList.append(tr("One Line"));
    typeList.append(tr("Raster Scan"));
    typeList.append(tr("Helicoidal Scan"));
    m_typeItem->set(typeList);

    /* Max Scan Speed menu item */
    m_maxScanSpeedItem->set(0, 1000, 2);

    /* Max Scan Speed(rpm) Menu Item */
    m_maxScanSpeedRPMItem->set(0, 1000, 0);
}

InspectionMenu::~InspectionMenu()
{
}

}
