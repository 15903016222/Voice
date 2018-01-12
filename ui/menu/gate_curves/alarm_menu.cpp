/**
 * @file alarm_menu.cpp
 * @brief alarm menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "alarm_menu.h"
#include <global.h>

#include <fpga/fpga.h>
#include <device/device.h>

namespace DplGateCurvesMenu {

AlarmMenu::AlarmMenu(QWidget *parent) :
    BaseMenu(parent),
    m_alarmItem(new ComboMenuItem(this, tr("Alarm"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_modeItem(new ComboMenuItem(this, tr("Mode"))),
    m_groupItem(new MultiComboMenuItem(tr("Group"), this)),
    m_fstConditionItem(new ComboMenuItem(this, tr("Condition1"))),
    m_operatorItem(new ComboMenuItem(this, tr("Operator"))),
    m_sndConditionItem(new ComboMenuItem(this, tr("Condition2"))),
    m_countItem(new SpinMenuItem(this, tr("Count"))),
    m_soundItem(new ComboMenuItem(this, tr("Sound"))),
    m_delayItem(new SpinMenuItem(this, tr("Delay"), "ms")),
    m_holdTimeItem(new SpinMenuItem(this, tr("Hold Time"), "ms")),
    m_alarm(NULL)
{
    m_layout0->addWidget(m_alarmItem);
    m_layout1->addWidget(m_switchItem);
    m_layout2->addWidget(m_modeItem);

    /* setting mode */
    m_layout3->addWidget(m_groupItem);
    m_layout4->addWidget(m_fstConditionItem);
    m_layout5->addWidget(m_operatorItem);
    m_layout6->addWidget(m_sndConditionItem);

    /* output mode */
    m_layout3->addWidget(m_countItem);
    m_layout4->addWidget(m_soundItem);
    m_layout5->addWidget(m_delayItem);
    m_layout6->addWidget(m_holdTimeItem);

    /* alarm item */
    m_alarmItem->add_item(tr("Alarm 1"));
    m_alarmItem->add_item(tr("Alarm 2"));
    m_alarmItem->add_item(tr("Alarm 3"));
    connect(m_alarmItem, SIGNAL(value_changed(int)),
            this, SLOT(update(int)));

    /* switch item */
    m_switchItem->set(s_onOff);

    /* mode item */
    m_modeItem->add_item(tr("Setting"));
    m_modeItem->add_item(tr("Output"));
    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_modeItem_changed(int)));
    do_modeItem_changed(0);

    /* group item */
    connect(DplDevice::Device::instance(),
            SIGNAL(group_qty_changed(int)),
            this,
            SLOT(do_group_qty_changed(int)));
    do_group_qty_changed(DplDevice::Device::instance()->group_qty());

    /* operator item */
    m_operatorItem->add_item(tr("And"));
    m_operatorItem->add_item(tr("Or"));

    /* condition items */
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

    /* count item */
    m_countItem->set(1, 100, 0);

    /* sound item */
    m_soundItem->add_item(tr("Off"));
    m_soundItem->add_item("300Hz", tr("Audio Output at 300Hz"));
    m_soundItem->add_item("600Hz", tr("Audio Output at 600Hz"));
    m_soundItem->add_item("1000Hz", tr("Audio Output at 1000Hz"));
    m_soundItem->add_item("5000Hz", tr("Audio Output at 5000Hz"));

    /* delay item */
    m_delayItem->set(0, 5000, 2);

    /* hold item */
    m_holdTimeItem->set(0, 5000, 2);

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
    disconnect(m_countItem, SIGNAL(value_changed(double)),
               this, SLOT(do_countItem(double)));
    disconnect(m_soundItem, SIGNAL(value_changed(int)),
               this, SLOT(do_soundItem(int)));
    disconnect(m_delayItem, SIGNAL(value_changed(double)),
               this, SLOT(do_delayItem(double)));
    disconnect(m_holdTimeItem, SIGNAL(value_changed(double)),
               this, SLOT(do_holdTimeItem(double)));
    disconnect(m_switchItem, SIGNAL(value_changed(int)),
               this, SLOT(do_switchItem_changed(int)));

    m_alarm = DplFpga::Fpga::instance()->alarm_output(index);

    update_switchItem();

    update_groupItem();
    update_fstConditionItem();
    update_operatorItem();
    update_sndConditionItem();

    update_countItem();
    update_soundItem();
    update_delayItem();
    update_holdTimeItem();

    connect(m_groupItem, SIGNAL(triggered(int,bool)),
               this, SLOT(do_groupItem_triggered(int,bool)));
    connect(m_fstConditionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_fstConditionItem_changed(int)));
    connect(m_operatorItem, SIGNAL(value_changed(int)),
            this, SLOT(do_operationItem_changed(int)));
    connect(m_sndConditionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_sndConditionItem_changed(int)));
    connect(m_countItem, SIGNAL(value_changed(double)),
            this, SLOT(do_countItem(double)));
    connect(m_soundItem, SIGNAL(value_changed(int)),
            this, SLOT(do_soundItem(int)));
    connect(m_delayItem, SIGNAL(value_changed(double)),
            this, SLOT(do_delayItem(double)));
    connect(m_holdTimeItem, SIGNAL(value_changed(double)),
            this, SLOT(do_holdTimeItem(double)));
    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));
}

void AlarmMenu::do_countItem(double val)
{
    m_alarm->set_count(val);
}

void AlarmMenu::do_modeItem_changed(int index)
{
    if (index == 0) {
        /* output hide */
        m_countItem->hide();
        m_soundItem->hide();
        m_delayItem->hide();
        m_holdTimeItem->hide();

        /* setting show */
        m_groupItem->show();
        m_fstConditionItem->show();
        m_operatorItem->show();
        m_sndConditionItem->show();
    } else {
        /* setting hide */
        m_groupItem->hide();
        m_fstConditionItem->hide();
        m_operatorItem->hide();
        m_sndConditionItem->hide();

        /* output show */
        m_countItem->show();
        m_soundItem->show();
        m_delayItem->show();
        m_holdTimeItem->show();
    }
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

void AlarmMenu::do_soundItem(int index)
{
    DplFpga::Fpga::instance()->set_sound(static_cast<DplFpga::Fpga::SoundMode>(index));
}

void AlarmMenu::do_delayItem(double val)
{
    m_alarm->set_delay(Dpl::ms_to_us(val));
}

void AlarmMenu::do_holdTimeItem(double val)
{
    m_alarm->set_hold_time(Dpl::ms_to_us(val));
}

void AlarmMenu::do_switchItem_changed(int index)
{
    m_alarm->set_enable(!index);
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

void AlarmMenu::update_switchItem()
{
    m_switchItem->set_current_index(!m_alarm->enable());
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

void AlarmMenu::update_countItem()
{
    m_countItem->set_value(m_alarm->count());
}

void AlarmMenu::update_soundItem()
{
    m_soundItem->set_current_index(DplFpga::Fpga::instance()->sound());
}

void AlarmMenu::update_delayItem()
{
    m_delayItem->set_value(Dpl::us_to_ms(static_cast<double>(m_alarm->delay())));
}

void AlarmMenu::update_holdTimeItem()
{
    m_holdTimeItem->set_value(Dpl::us_to_ms(static_cast<double>(m_alarm->hold_time())));
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

void AlarmMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_alarmItem->set_title(tr("Alarm"));
        m_switchItem->set_title(tr("Switch"));
        m_modeItem->set_title(tr("Mode"));
        m_fstConditionItem->set_title(tr("Condition1"));
        m_operatorItem->set_title(tr("Operator"));
        m_sndConditionItem->set_title(tr("Condition2"));
        m_countItem->set_title(tr("Count"));
        m_soundItem->set_title(tr("Sound"));
        m_delayItem->set_title(tr("Delay"));
        m_holdTimeItem->set_title(tr("Hold Time"));
        return;
    }
    BaseMenu::changeEvent(e);
}


}
