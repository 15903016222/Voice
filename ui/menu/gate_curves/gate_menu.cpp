/**
 * @file gate_menu.cpp
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "gate_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

GateMenu::GateMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    QStringList gatesList;
    QStringList synchrosList;
    QStringList measureModesList;

    gatesList.append(tr("A"));
    gatesList.append(tr("B"));
    gatesList.append(tr("I"));
    gatesList.append(tr("Off"));

    synchrosList.append(tr("Gate A"));
    synchrosList.append(tr("Gate I"));
    synchrosList.append(tr("Pulse"));

    measureModesList.append(tr("Edge"));
    measureModesList.append(tr("Peak"));

    m_gateItem      = new ComboMenuItem;
    m_startItem     = new SpinMenuItem;
    m_widthItem     = new SpinMenuItem;
    m_thresholdItem = new SpinMenuItem;
    m_synchroItem   = new ComboMenuItem;
    m_measureModeItem   = new ComboMenuItem;

    m_gateItem->set(tr("Gate"), gatesList);
    m_startItem->set(tr("Start"), "mm", 0, 16000, 2);
    m_widthItem->set(tr("Width"), "mm", 0.05, 525, 2);
    m_thresholdItem->set(tr("Threshold"), "%", 0, 100, 0);
    m_synchroItem->set(tr("Synchro"), synchrosList);
    m_measureModeItem->set(tr("Measure Mode"), measureModesList);
}

GateMenu::~GateMenu()
{
    delete m_gateItem;
    delete m_startItem;
    delete m_widthItem;
    delete m_thresholdItem;
    delete m_synchroItem;
    delete m_measureModeItem;
}

void GateMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_gateItem);
    ui->menuItem1->layout()->addWidget(m_startItem);
    ui->menuItem2->layout()->addWidget(m_widthItem);
    ui->menuItem3->layout()->addWidget(m_thresholdItem);
    ui->menuItem4->layout()->addWidget(m_synchroItem);
    ui->menuItem5->layout()->addWidget(m_measureModeItem);
    m_gateItem->show();
    m_startItem->show();
    m_widthItem->show();
    m_thresholdItem->show();
    m_synchroItem->show();
    m_measureModeItem->show();
}

void GateMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_gateItem);
    ui->menuItem1->layout()->removeWidget(m_startItem);
    ui->menuItem2->layout()->removeWidget(m_widthItem);
    ui->menuItem3->layout()->removeWidget(m_thresholdItem);
    ui->menuItem4->layout()->removeWidget(m_synchroItem);
    ui->menuItem5->layout()->removeWidget(m_measureModeItem);
    m_gateItem->hide();
    m_startItem->hide();
    m_widthItem->hide();
    m_thresholdItem->hide();
    m_synchroItem->hide();
    m_measureModeItem->hide();
}
