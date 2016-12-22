/**
 * @file alarm_menu.cpp
 * @brief alarm menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "alarm_menu.h"
#include "combo_menu_item.h"

namespace DplGateCurvesMenu {

AlarmMenu::AlarmMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    QStringList alarmList;
    QStringList groupList;
    QStringList conditionList;
    QStringList operatorList;

    alarmList.append(tr("Alarm 1"));
    alarmList.append(tr("Alarm 2"));
    alarmList.append(tr("Alarm 3"));

    groupList.append(tr("Group1"));
    groupList.append(tr("All"));
    groupList.append(tr("None"));

    conditionList.append(tr("None"));
    conditionList.append(tr("Gate A"));
    conditionList.append(tr("Gate B"));
    conditionList.append(tr("Gate I"));
    conditionList.append(tr("Not Gate A"));
    conditionList.append(tr("Not Gate B"));
    conditionList.append(tr("Not Gate I"));
    conditionList.append(tr(">Max.Thickness"));
    conditionList.append(tr("<Min.Thickness"));

    operatorList.append(tr("And"));
    operatorList.append(tr("Or"));

    m_alarmItem = new ComboMenuItem;
    m_alarmItem->set(tr("Alarm"), alarmList);

    m_switchItem = new ComboMenuItem;
    m_switchItem->set(tr("Switch"), s_onOff);

    m_groupItem = new ComboMenuItem;
    m_groupItem->set(tr("Group"), groupList);

    m_conditionItem = new ComboMenuItem;
    m_conditionItem->set(tr("Condition"), conditionList);

    m_operatorItem = new ComboMenuItem;
    m_operatorItem->set(tr("Operator"), operatorList);
}

AlarmMenu::~AlarmMenu()
{
    delete m_alarmItem;
    delete m_switchItem;
    delete m_groupItem;
    delete m_conditionItem;
    delete m_operatorItem;
}

void AlarmMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_alarmItem);
    ui->menuItem1->layout()->addWidget(m_switchItem);
    ui->menuItem2->layout()->addWidget(m_groupItem);
    ui->menuItem3->layout()->addWidget(m_conditionItem);
    ui->menuItem4->layout()->addWidget(m_operatorItem);
    m_alarmItem->show();
    m_switchItem->show();
    m_groupItem->show();
    m_conditionItem->show();
    m_operatorItem->show();
}

void AlarmMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_alarmItem);
    ui->menuItem1->layout()->removeWidget(m_switchItem);
    ui->menuItem2->layout()->removeWidget(m_groupItem);
    ui->menuItem3->layout()->removeWidget(m_conditionItem);
    ui->menuItem4->layout()->removeWidget(m_operatorItem);
    m_alarmItem->hide();
    m_switchItem->hide();
    m_groupItem->hide();
    m_conditionItem->hide();
    m_operatorItem->hide();
}

}
