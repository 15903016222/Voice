/**
 * @file general_menu.cpp
 * @brief UT Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "general_menu.h"
#include <QDebug>

GeneralMenu::GeneralMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_utUnit.append(tr("Time"));
    m_utUnit.append(tr("Sound Path"));
    m_utUnit.append(tr("True Path"));

    m_gainItem = new SpinMenuItem();
    m_startItem = new SpinMenuItem();
    m_rangeItem = new SpinMenuItem();
    m_velocityItem = new SpinMenuItem();
    m_wedgeItem = new SpinMenuItem();
    m_utUnitItem = new ComboMenuItem();

    m_gainItem->set(tr("Gain"), "dB", 0, 100, 1);
    m_startItem->set(tr("Start"), "mm", 0, 1000, 2);
    m_rangeItem->set(tr("Range"), "mm", 0, 1000, 2);
    m_velocityItem->set(tr("Velocity"), "m/s", 635, 12540, 1);
    m_wedgeItem->set(tr("Wedge Delay"), "μs", 0, 1000, 2);
    m_utUnitItem->set(tr("UT Unit"), m_utUnit);
}

GeneralMenu::~GeneralMenu()
{
    delete m_gainItem;
    delete m_startItem;
    delete m_rangeItem;
    delete m_velocityItem;
    delete m_wedgeItem;
    delete m_utUnitItem;
}

void GeneralMenu::show()
{
    ui->menuItem1->layout()->addWidget(m_gainItem);
    ui->menuItem2->layout()->addWidget(m_startItem);
    ui->menuItem3->layout()->addWidget(m_rangeItem);
    ui->menuItem4->layout()->addWidget(m_velocityItem);
    ui->menuItem5->layout()->addWidget(m_wedgeItem);
    ui->menuItem6->layout()->addWidget(m_utUnitItem);

    m_gainItem->show();
    m_startItem->show();
    m_rangeItem->show();
    m_velocityItem->show();
    m_wedgeItem->show();
    m_utUnitItem->show();
}

void GeneralMenu::hide()
{
    ui->menuItem1->layout()->removeWidget(m_gainItem);
    ui->menuItem2->layout()->removeWidget(m_startItem);
    ui->menuItem3->layout()->removeWidget(m_rangeItem);
    ui->menuItem4->layout()->removeWidget(m_velocityItem);
    ui->menuItem5->layout()->removeWidget(m_wedgeItem);
    ui->menuItem6->layout()->removeWidget(m_utUnitItem);

    m_gainItem->hide();
    m_startItem->hide();
    m_rangeItem->hide();
    m_velocityItem->hide();
    m_wedgeItem->hide();
    m_utUnitItem->hide();
}
