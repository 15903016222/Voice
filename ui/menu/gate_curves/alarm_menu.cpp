/**
 * @file alarm_menu.cpp
 * @brief alarm menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "alarm_menu.h"
#include "ui_base_menu.h"
#include <fpga/fpga.h>

namespace DplGateCurvesMenu {

AlarmMenu::AlarmMenu(QWidget *parent) :
    BaseMenu(parent),
    m_alarmItem(new ComboMenuItem(this, tr("Alarm"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_groupItem(new ComboMenuItem(this, tr("Group"))),
    m_fstConditionItem(new ComboMenuItem(this, tr("Condition1"))),
    m_operatorItem(new ComboMenuItem(this, tr("Operator"))),
    m_sndConditionItem(new ComboMenuItem(this, tr("Condition2"))),
    m_alarmOutput(NULL)
{
    ui->layout0->addWidget(m_alarmItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_groupItem);
    ui->layout3->addWidget(m_fstConditionItem);
    ui->layout4->addWidget(m_operatorItem);
    ui->layout5->addWidget(m_sndConditionItem);

    m_alarmItem->add_item(tr("Alarm 1"));
    m_alarmItem->add_item(tr("Alarm 2"));
    m_alarmItem->add_item(tr("Alarm 3"));
    connect(m_alarmItem, SIGNAL(value_changed(int)),
            this, SLOT(update(int)));

    m_groupItem->add_item(tr("Group1"));
    m_groupItem->add_item(tr("All"));
    m_groupItem->add_item(tr("None"));

    m_operatorItem->add_item(tr("And"));
    m_operatorItem->add_item(tr("Or"));

    m_switchItem->set(s_onOff);

    QStringList conditionList;
    conditionList.append(tr("None"));
    conditionList.append(tr("Gate A"));
    conditionList.append(tr("Gate B"));
    conditionList.append(tr("Gate I"));
    conditionList.append(tr("Not Gate A"));
    conditionList.append(tr("Not Gate B"));
    conditionList.append(tr("Not Gate I"));
    conditionList.append(tr(">Max.Thickness"));
    conditionList.append(tr("<Min.Thickness"));

    m_fstConditionItem->set(conditionList);
    m_sndConditionItem->set(conditionList);

    update(0);
}

void AlarmMenu::update(int index)
{
    disconnect(m_switchItem, SIGNAL(value_changed(int)),
               this, SLOT(do_switchItem_changed(int)));
    //    disconnect(m_groupItem, SIGNAL(value_changed(int)),
    //            this, SLOT(do_))
    disconnect(m_fstConditionItem, SIGNAL(value_changed(int)),
               this, SLOT(do_fstConditionItem_changed(int)));
    disconnect(m_operatorItem, SIGNAL(value_changed(int)),
               this, SLOT(do_operationItem_changed(int)));
    disconnect(m_sndConditionItem, SIGNAL(value_changed(int)),
               this, SLOT(do_sndConditionItem_changed(int)));

    m_alarmOutput = DplFpga::Fpga::instance()->alarm_output(index);

    update_switchItem();
    update_groupItem();
    update_fstConditionItem();
    update_operatorItem();
    update_sndConditionItem();

    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));
    //    connect(m_groupItem, SIGNAL(value_changed(int)),
    //            this, SLOT(do_))
    connect(m_fstConditionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_fstConditionItem_changed(int)));
    connect(m_operatorItem, SIGNAL(value_changed(int)),
            this, SLOT(do_operationItem_changed(int)));
    connect(m_sndConditionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_sndConditionItem_changed(int)));
}

void AlarmMenu::do_switchItem_changed(int index)
{
    m_alarmOutput->set_enable(!index);
}

void AlarmMenu::do_fstConditionItem_changed(int index)
{
    m_alarmOutput->set_condition(static_cast<DplFpga::AlarmOutput::Condition>(index),
                                 static_cast<DplFpga::AlarmOutput::Condition>(m_sndConditionItem->current_index()));
}

void AlarmMenu::do_operationItem_changed(int index)
{
    m_alarmOutput->set_op(static_cast<DplFpga::AlarmOutput::Operator>(index));
}

void AlarmMenu::do_sndConditionItem_changed(int index)
{
    m_alarmOutput->set_condition(static_cast<DplFpga::AlarmOutput::Condition>(m_fstConditionItem->current_index()),
                                 static_cast<DplFpga::AlarmOutput::Condition>(index));
}

void AlarmMenu::update_switchItem()
{
    m_switchItem->set_current_index(!m_alarmOutput->enable());
}

void AlarmMenu::update_groupItem()
{
    m_groupItem->set_current_index(m_alarmOutput->logic_group());
}

void AlarmMenu::update_fstConditionItem()
{
    m_fstConditionItem->set_current_index(m_alarmOutput->first_condition());
}

void AlarmMenu::update_operatorItem()
{
    m_operatorItem->set_current_index(m_alarmOutput->op());
}

void AlarmMenu::update_sndConditionItem()
{
    m_sndConditionItem->set_current_index(m_alarmOutput->second_condition());
}


}
