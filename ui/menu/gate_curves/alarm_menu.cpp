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

    m_alarmItem.set(tr("Alarm"), alarmList);

    m_switchItem.set(tr("Switch"), s_onOff);

    m_groupItem.set(tr("Group"), groupList);

    m_conditionItem.set(tr("Condition"), conditionList);

    m_operatorItem.set(tr("Operator"), operatorList);
}

AlarmMenu::~AlarmMenu()
{
}

void AlarmMenu::show()
{
    ui->layout0->addWidget(&m_alarmItem);
    ui->layout1->addWidget(&m_switchItem);
    ui->layout2->addWidget(&m_groupItem);
    ui->layout3->addWidget(&m_conditionItem);
    ui->layout4->addWidget(&m_operatorItem);
    m_alarmItem.show();
    m_switchItem.show();
    m_groupItem.show();
    m_conditionItem.show();
    m_operatorItem.show();
}

void AlarmMenu::hide()
{
    ui->layout0->removeWidget(&m_alarmItem);
    ui->layout1->removeWidget(&m_switchItem);
    ui->layout2->removeWidget(&m_groupItem);
    ui->layout3->removeWidget(&m_conditionItem);
    ui->layout4->removeWidget(&m_operatorItem);
    m_alarmItem.hide();
    m_switchItem.hide();
    m_groupItem.hide();
    m_conditionItem.hide();
    m_operatorItem.hide();
}

}
