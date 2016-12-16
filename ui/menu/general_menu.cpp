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

    m_gainItem = new MenuItem();
    m_startItem = new MenuItem();
    m_rangeItem = new MenuItem();
    m_velocityItem = new MenuItem();
    m_wedgeItem = new MenuItem();
    m_utUnitItem = new MenuItem();

    m_gainItem->set_spin(tr("Gain"), "dB", 0, 100, 1);
    m_startItem->set_spin(tr("Start"), "mm", 0, 1000, 2);
    m_rangeItem->set_spin(tr("Range"), "mm", 0, 1000, 2);
    m_velocityItem->set_spin(tr("Velocity"), "m/s", 635, 12540, 1);
    m_wedgeItem->set_spin(tr("Wedge Delay"), "μs", 0, 1000, 2);
    m_utUnitItem->set_combo(tr("UT Unit"), m_utUnit);
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
    qDebug()<<__func__<<__LINE__;
    ui->subMenu_1->layout()->addWidget(m_gainItem);
    ui->subMenu_2->layout()->addWidget(m_startItem);
    ui->subMenu_3->layout()->addWidget(m_rangeItem);
    ui->subMenu_4->layout()->addWidget(m_velocityItem);
    ui->subMenu_5->layout()->addWidget(m_wedgeItem);
    ui->subMenu_6->layout()->addWidget(m_utUnitItem);

    m_gainItem->show();
    m_startItem->show();
    m_rangeItem->show();
    m_velocityItem->show();
    m_wedgeItem->show();
    m_utUnitItem->show();

    qDebug()<<__func__<<__LINE__;
}

void GeneralMenu::hide()
{
    qDebug()<<__func__<<__LINE__;
    ui->subMenu_1->layout()->removeWidget(m_gainItem);
    ui->subMenu_2->layout()->removeWidget(m_startItem);
    ui->subMenu_3->layout()->removeWidget(m_rangeItem);
    ui->subMenu_4->layout()->removeWidget(m_velocityItem);
    ui->subMenu_5->layout()->removeWidget(m_wedgeItem);
    ui->subMenu_6->layout()->removeWidget(m_utUnitItem);

    m_gainItem->hide();
    m_startItem->hide();
    m_rangeItem->hide();
    m_velocityItem->hide();
    m_wedgeItem->hide();
    m_utUnitItem->hide();

    qDebug()<<__func__<<__LINE__;
}
