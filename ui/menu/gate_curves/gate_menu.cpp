/**
 * @file gate_menu.cpp
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "gate_menu.h"

#include <global.h>
#include <device/device.h>
#include <ui/tool/tool.h>
#include "ui_base_menu.h"

namespace DplGateCurvesMenu {

GateMenu::GateMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gateItem(new ComboMenuItem(this, tr("Gate"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_paramsItem(new ComboMenuItem(this, tr("Parameters"))),
    m_startItem(new SpinMenuItem(this, tr("Start"))),
    m_widthItem(new SpinMenuItem(this, tr("Width"), "mm")),
    m_thresholdItem(new SpinMenuItem(this, tr("Threshold"), "%")),
    m_synchroItem(new ComboMenuItem(this, tr("Synchro"))),
    m_measureModeItem(new ComboMenuItem(this, tr("Measure Mode"))),
    m_modeItem(new ComboMenuItem(this, tr("Mode")))
{
    ui->layout0->addWidget(m_gateItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_paramsItem);
    ui->layout3->addWidget(m_startItem);
    ui->layout4->addWidget(m_widthItem);
    ui->layout5->addWidget(m_thresholdItem);
    ui->layout3->addWidget(m_synchroItem);
    ui->layout4->addWidget(m_measureModeItem);
    ui->layout5->addWidget(m_modeItem);

    QStringList synchrosList;

    synchrosList.append(tr("Gate A"));
    synchrosList.append(tr("Gate I"));
    synchrosList.append(tr("Pulse"));

    m_gateItem->add_item(tr("A"));
    m_gateItem->add_item(tr("B"));
    m_gateItem->add_item(tr("I"));
    connect(m_gateItem, SIGNAL(value_changed(int)),
            this, SLOT(do_gateItem_changed(int)));

    m_switchItem->set(s_onOff);
    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));

    m_paramsItem->add_item(tr("Position"));
    m_paramsItem->add_item(tr("Mode"));
    connect(m_paramsItem, SIGNAL(value_changed(int)),
            this, SLOT(do_paramsItem_changed(int)));

    connect(m_startItem, SIGNAL(value_changed(double)),
            this, SLOT(do_startItem_changed(double)));

    connect(m_widthItem, SIGNAL(value_changed(double)),
            this, SLOT(do_widthItem_changed(double)));

    m_thresholdItem->set(0, 100, 0);
    connect(m_thresholdItem, SIGNAL(value_changed(double)),
            this, SLOT(do_thresholdItem_changed(double)));

    m_synchroItem->set(synchrosList);

    m_measureModeItem->add_item(tr("Edge"));
    m_measureModeItem->add_item(tr("Peak"));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));

    QStringList modeList;
    modeList.append(tr("Sound Path"));
    modeList.append(tr("Depth"));
    m_modeItem->set(modeList);

    do_current_group_changed(DplDevice::Device::instance()->current_group());
    do_paramsItem_changed(0);
}

GateMenu::~GateMenu()
{
}

void GateMenu::update_gate(const DplGate::GatePointer &gate)
{
    m_switchItem->set_current_index(!gate->is_visible());
    update_startItem(gate);
    update_widhtItem(gate);
    update_thresholdItem(gate);
}

void GateMenu::update_startItem(const DplGate::GatePointer &gate)
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_startItem->set_unit(US_STR);
    } else {
        m_startItem->set_unit(MM_STR);
    }

    m_startItem->set(Tool::cnf_to_display(m_group, m_group->sample()->start()),
                     Tool::cnf_to_display(m_group, m_group->sample()->start()+m_group->sample()->range()),
                     2, 0.01);
    m_startItem->set_value(Tool::cnf_to_display(m_group, gate->start()));
}

void GateMenu::update_widhtItem(const DplGate::GatePointer &gate)
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_widthItem->set_unit(US_STR);
    } else {
        m_widthItem->set_unit(MM_STR);
    }

    m_widthItem->set(Tool::cnf_to_display(m_group, 0),
                     Tool::cnf_to_display(m_group, m_group->sample()->range()),
                     2, 0.01);

    m_widthItem->set_value(Tool::cnf_to_display(m_group, gate->width()));
}

void GateMenu::update_thresholdItem(const DplGate::GatePointer &gate)
{
    m_thresholdItem->set_value(gate->height());
}

void GateMenu::do_gateItem_changed(int val)
{
    update_gate(m_group->gate(static_cast<DplGate::Gate::Type>(val)));
}

void GateMenu::do_startItem_changed(double val)
{
    DplGate::GatePointer gate = m_group->gate(static_cast<DplGate::Gate::Type>(m_gateItem->current_index()));
    gate->set_start(Tool::display_to_cnf(m_group, val));
}

void GateMenu::do_widthItem_changed(double val)
{
    DplGate::GatePointer gate = m_group->gate(static_cast<DplGate::Gate::Type>(m_gateItem->current_index()));
    gate->set_width(Tool::display_to_cnf(m_group, val));
}

void GateMenu::do_thresholdItem_changed(double val)
{
    DplGate::GatePointer gate = m_group->gate(static_cast<DplGate::Gate::Type>(m_gateItem->current_index()));
    gate->set_height(val+0.5);
}

void GateMenu::do_switchItem_changed(int index)
{
    m_group->gate(static_cast<DplGate::Gate::Type>(m_gateItem->current_index()))->set_visible(!index);
}

void GateMenu::do_paramsItem_changed(int index)
{
    m_startItem->setVisible(!index);
    m_widthItem->setVisible(!index);
    m_thresholdItem->setVisible(!index);
    m_synchroItem->setVisible(!!index);
    m_measureModeItem->setVisible(!!index);
    m_modeItem->setVisible(!!index);
}

void GateMenu::do_sample_changed()
{
    do_gateItem_changed(m_gateItem->current_index());
}

void GateMenu::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    if (!m_group.isNull()) {
        disconnect(m_group->sample().data(), SIGNAL(start_changed(float)),
                   this, SLOT(do_sample_changed()));
        disconnect(m_group->sample().data(), SIGNAL(range_changed(float)),
                   this, SLOT(do_sample_changed()));
    }

    m_group = group;

    connect(m_group->sample().data(), SIGNAL(start_changed(float)),
            this, SLOT(do_sample_changed()));
    connect(m_group->sample().data(), SIGNAL(range_changed(float)),
            this, SLOT(do_sample_changed()));

    update_gate(m_group->gate(DplGate::Gate::A));
}

}
