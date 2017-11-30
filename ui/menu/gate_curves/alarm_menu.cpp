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
#include <device/device.h>

namespace DplGateCurvesMenu {

AlarmMenu::AlarmMenu(QWidget *parent) :
    BaseMenu(parent),
    m_alarmItem(new ComboMenuItem(this, tr("Alarm"))),
    m_groupItem(new MultiComboMenuItem(tr("Group"), this)),
    m_fstConditionItem(new ComboMenuItem(this, tr("Condition1"))),
    m_operatorItem(new ComboMenuItem(this, tr("Operator"))),
    m_sndConditionItem(new ComboMenuItem(this, tr("Condition2"))),
    m_alarm(NULL)
{
    ui->layout0->addWidget(m_alarmItem);
    ui->layout1->addWidget(m_groupItem);
    ui->layout2->addWidget(m_fstConditionItem);
    ui->layout3->addWidget(m_operatorItem);
    ui->layout4->addWidget(m_sndConditionItem);

    m_alarmItem->add_item(tr("Alarm 1"));
    m_alarmItem->add_item(tr("Alarm 2"));
    m_alarmItem->add_item(tr("Alarm 3"));
    connect(m_alarmItem, SIGNAL(value_changed(int)),
            this, SLOT(update(int)));

    connect(DplDevice::Device::instance(),
            SIGNAL(group_qty_changed(int)),
            this,
            SLOT(do_group_qty_changed(int)));
    do_group_qty_changed(DplDevice::Device::instance()->group_qty());

    m_operatorItem->add_item(tr("And"));
    m_operatorItem->add_item(tr("Or"));

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
    disconnect(m_groupItem, SIGNAL(triggered(int,bool)),
               this, SLOT(do_groupItem_triggered(int,bool)));
    disconnect(m_fstConditionItem, SIGNAL(value_changed(int)),
               this, SLOT(do_fstConditionItem_changed(int)));
    disconnect(m_operatorItem, SIGNAL(value_changed(int)),
               this, SLOT(do_operationItem_changed(int)));
    disconnect(m_sndConditionItem, SIGNAL(value_changed(int)),
               this, SLOT(do_sndConditionItem_changed(int)));

    m_alarm = DplFpga::Fpga::instance()->alarm_output(index);

    update_groupItem();
    update_fstConditionItem();
    update_operatorItem();
    update_sndConditionItem();

    connect(m_groupItem, SIGNAL(triggered(int,bool)),
               this, SLOT(do_groupItem_triggered(int,bool)));
    connect(m_fstConditionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_fstConditionItem_changed(int)));
    connect(m_operatorItem, SIGNAL(value_changed(int)),
            this, SLOT(do_operationItem_changed(int)));
    connect(m_sndConditionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_sndConditionItem_changed(int)));
}

void AlarmMenu::do_groupItem_triggered(int index, bool checked)
{
    if ((index == 0) || (index==1 && !checked) ) {
        /* none */
        set_none_group();
    } else if(index == 1 && checked) {
        /* all */
        set_all_group();
    } else {
        set_any_group();
    }
}

void AlarmMenu::do_fstConditionItem_changed(int index)
{
    m_alarm->set_condition(static_cast<DplFpga::AlarmOutput::Condition>(index),
                                 static_cast<DplFpga::AlarmOutput::Condition>(m_sndConditionItem->current_index()));
}

void AlarmMenu::do_operationItem_changed(int index)
{
    m_alarm->set_op(static_cast<DplFpga::AlarmOutput::Operator>(index));
}

void AlarmMenu::do_sndConditionItem_changed(int index)
{
    m_alarm->set_condition(static_cast<DplFpga::AlarmOutput::Condition>(m_fstConditionItem->current_index()),
                           static_cast<DplFpga::AlarmOutput::Condition>(index));
}

void AlarmMenu::do_group_qty_changed(int qty)
{
    m_groupItem->clear();
    m_groupItem->add_item(tr("None"));
    m_groupItem->add_item(tr("All"));
    for (int i = 0; i < qty; ++i) {
        m_groupItem->add_item(QString("Group%1").arg(i+1));
    }
    if (m_alarm) {
        update_groupItem();
    }
}

void AlarmMenu::update_groupItem()
{
    if (m_alarm->logic_group() == 0) {
        m_groupItem->set_value(0x1);
    } else if (DplDevice::Device::instance()->group_qty() == get_group_qty(m_alarm->logic_group())) {
        m_groupItem->set_value(0x1ffff<<1);
    } else {
        m_groupItem->set_value(m_alarm->logic_group()<<2);
    }
}

void AlarmMenu::update_fstConditionItem()
{
    m_fstConditionItem->set_current_index(m_alarm->first_condition());
}

void AlarmMenu::update_operatorItem()
{
    m_operatorItem->set_current_index(m_alarm->op());
}

void AlarmMenu::update_sndConditionItem()
{
    m_sndConditionItem->set_current_index(m_alarm->second_condition());
}

void AlarmMenu::set_all_group()
{
    m_groupItem->set_value(0x1ffff<<1);
    m_alarm->set_logic_group(m_groupItem->value()>>2);
}

void AlarmMenu::set_none_group()
{
    m_alarm->set_logic_group(0x0);
    m_groupItem->set_value(0x1);
}

void AlarmMenu::set_any_group()
{
    int cnt = get_group_qty(m_groupItem->value()>>2);
    int value = m_groupItem->value()>>2;

    m_alarm->set_logic_group(value);
    if (cnt == DplDevice::Device::instance()->group_qty()) {
        m_groupItem->set_value(0xffff<<1);
    } else if (cnt == 0) {
        m_groupItem->set_value(0x1);
    } else {
        m_groupItem->set_value(value<<2);
    }
}

int AlarmMenu::get_group_qty(int groupflags)
{
    int ret = 0;
    for (uint i = 0; i < sizeof(int); ++i) {
        ret += (groupflags>>i) & 0x1;
    }
    return ret;
}


}
