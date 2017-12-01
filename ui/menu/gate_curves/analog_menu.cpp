/**
 * @file analog_menu.cpp
 * @brief Gate/Curves analog menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "analog_menu.h"
#include "ui_base_menu.h"
#include <fpga/fpga.h>

namespace DplGateCurvesMenu {

AnalogMenu::AnalogMenu(QWidget *parent) : BaseMenu(parent),
    m_analogItem(new ComboMenuItem(this, tr("Analog"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_groupItem(new ComboMenuItem(this, tr("Group"))),
    m_dataItem(new ComboMenuItem(this, tr("Data")))
{
    ui->layout0->addWidget(m_analogItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_groupItem);
    ui->layout3->addWidget(m_dataItem);

    m_groupItem->add_item(tr("Group 1"));
    m_groupItem->add_item(tr("All"));

    m_switchItem->add_items(s_onOff);

    m_analogItem->add_item(tr("Analog 1"));
    m_analogItem->add_item(tr("Analog 2"));
    connect(m_analogItem, SIGNAL(value_changed(int)),
            this, SLOT(update(int)));

    m_dataItem->add_item(tr("None"));
    m_dataItem->add_item("A%");
    m_dataItem->add_item("B%");
    m_dataItem->add_item(tr("Thickness"));

    update(0);
}

void AnalogMenu::do_switchItem_changed(int index)
{
    m_analog->set_enable(!index);
}

void AnalogMenu::do_groupItem_changed(int index)
{
    m_analog->set_logic_group(index);
}

void AnalogMenu::do_dataItem_changed(int index)
{
    m_analog->set_type(static_cast<DplFpga::AlarmAnalog::Type>(index));
}

void AnalogMenu::update(int index)
{
    disconnect(m_switchItem, SIGNAL(value_changed(int)),
               this, SLOT(do_switchItem_changed(int)));
    disconnect(m_groupItem, SIGNAL(value_changed(int)),
               this, SLOT(do_dataItem_changed(int)));
    disconnect(m_dataItem, SIGNAL(value_changed(int)),
               this, SLOT(do_dataItem_changed(int)));

    m_analog = DplFpga::Fpga::instance()->alarm_analog(index);

    update_switchItem();
    update_groupItem();
    update_dataItem();

    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));
    connect(m_groupItem, SIGNAL(value_changed(int)),
            this, SLOT(do_dataItem_changed(int)));
    connect(m_dataItem, SIGNAL(value_changed(int)),
            this, SLOT(do_dataItem_changed(int)));
}

void AnalogMenu::update_switchItem()
{
    m_switchItem->set_current_index(!m_analog->enable());
}

void AnalogMenu::update_groupItem()
{
    m_groupItem->set_current_index(m_analog->logic_group());
}

void AnalogMenu::update_dataItem()
{
    m_dataItem->set_current_index(m_analog->type());
}

}
