/**
 * @file output_menu.cpp
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "output_menu.h"
#include "ui_base_menu.h"
#include <fpga/fpga.h>
#include <global.h>

namespace DplGateCurvesMenu {

OutputMenu::OutputMenu(QWidget *parent) :
    BaseMenu(parent),
    m_outputItem(new ComboMenuItem(this, tr("Output"))),
    m_countItem(new SpinMenuItem(this, tr("Count"))),
    m_soundItem(new ComboMenuItem(this, tr("Sound"))),
    m_delayItem(new SpinMenuItem(this, tr("Delay"), "ms")),
    m_holdTimeItem(new SpinMenuItem(this, tr("Hold Time"), "ms")),
    m_switchItem(new ComboMenuItem(this, tr("Switch")))
{
    ui->layout0->addWidget(m_outputItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_countItem);
    ui->layout3->addWidget(m_soundItem);
    ui->layout4->addWidget(m_delayItem);
    ui->layout5->addWidget(m_holdTimeItem);

    m_countItem->set(1, 100, 0);

    m_outputItem->add_item(tr("Alarm 1"));
    m_outputItem->add_item(tr("Alarm 2"));
    m_outputItem->add_item(tr("Alarm 3"));

    m_soundItem->add_item(tr("Off No Sound"));
    m_soundItem->add_item(tr("300Hz Audio Output at 300Hz"));
    m_soundItem->add_item(tr("600Hz Audio Output at 600Hz"));
    m_soundItem->add_item(tr("1000Hz Audio Output at 1000Hz"));
    m_soundItem->add_item(tr("5000Hz Audio Output at 5000Hz"));
    m_soundItem->set_dispay_mode(ComboMenuItem::PREFIX);

    m_delayItem->set(0, 5000, 2);
    m_holdTimeItem->set(0, 5000, 2);

    m_switchItem->set(s_onOff);

    update(0);
}

void OutputMenu::do_countItem(double val)
{
    m_output->set_count(val);
}

void OutputMenu::do_soundItem(int index)
{
    DplFpga::Fpga::instance()->set_sound(static_cast<DplFpga::Fpga::SoundMode>(index));
}

void OutputMenu::do_delayItem(double val)
{
    m_output->set_delay(Dpl::ms_to_us(val));
}

void OutputMenu::do_holdTimeItem(double val)
{
    m_output->set_hold_time(Dpl::ms_to_us(val));
}

void OutputMenu::do_switchItem_changed(int index)
{
    m_output->set_enable(!index);
}

void OutputMenu::update(int index)
{
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

    m_output = DplFpga::Fpga::instance()->alarm_output(index);
    update_countItem();
    update_soundItem();
    update_delayItem();
    update_holdTimeItem();
    update_switchItem();

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

void OutputMenu::update_countItem()
{
    m_countItem->set_value(m_output->count());
}

void OutputMenu::update_soundItem()
{
    m_soundItem->set_current_index(DplFpga::Fpga::instance()->sound());
}

void OutputMenu::update_delayItem()
{
    m_delayItem->set_value(Dpl::us_to_ms(static_cast<double>(m_output->delay())));
}

void OutputMenu::update_holdTimeItem()
{
    m_holdTimeItem->set_value(Dpl::us_to_ms(static_cast<double>(m_output->hold_time())));
}

void OutputMenu::update_switchItem()
{
    m_switchItem->set_current_index(!m_output->enable());
}

}
