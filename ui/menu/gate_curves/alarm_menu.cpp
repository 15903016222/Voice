/**
 * @file alarm_menu.cpp
 * @brief alarm menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "alarm_menu.h"
#include "ui_base_menu.h"

namespace DplGateCurvesMenu {

AlarmMenu::AlarmMenu(QWidget *parent) :
    BaseMenu(parent),
    m_alarmItem(new ComboMenuItem(this, tr("Alarm"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_groupItem(new ComboMenuItem(this, tr("Group"))),
    m_conditionItem(new ComboMenuItem(this, tr("Condition"))),
    m_operatorItem(new ComboMenuItem(this, tr("Operator")))
{
    ui->layout0->addWidget(m_alarmItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_groupItem);
    ui->layout3->addWidget(m_conditionItem);
    ui->layout4->addWidget(m_operatorItem);

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

    m_alarmItem->set(alarmList);

    m_switchItem->set(s_onOff);

    m_groupItem->set(groupList);

    m_conditionItem->set(conditionList);

    m_operatorItem->set(operatorList);
}

AlarmMenu::~AlarmMenu()
{
}

}
