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

    QStringList gatesList;
    QStringList synchrosList;
    QStringList measureModesList;

    gatesList.append(tr("A"));
    gatesList.append(tr("B"));
    gatesList.append(tr("I"));

    synchrosList.append(tr("Gate A"));
    synchrosList.append(tr("Gate I"));
    synchrosList.append(tr("Pulse"));

    measureModesList.append(tr("Edge"));
    measureModesList.append(tr("Peak"));

    m_gateItem->set(gatesList);
    connect(m_gateItem, SIGNAL(value_changed(int)),
            this, SLOT(do_gateItem_changed(int)));

    m_switchItem->set(s_onOff);
    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));

    QStringList paramList;
    paramList.append(tr("Position"));
    paramList.append(tr("Mode"));
    m_paramsItem->set(paramList);
    connect(m_paramsItem, SIGNAL(value_changed(int)),
            this, SLOT(do_paramsItem_changed(int)));

    connect(m_startItem, SIGNAL(value_changed(double)),
            this, SLOT(do_startItem_changed(double)));

    m_widthItem->set(0.05, 525, 2);
    m_thresholdItem->set(0, 100, 0);
    m_synchroItem->set(synchrosList);
    m_measureModeItem->set(measureModesList);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));

    QStringList modeList;
    modeList.append(tr("Sound Path"));
    modeList.append(tr("Depth"));
    m_modeItem->set(modeList);

    do_current_group_changed(DplDevice::Device::instance()->current_group());
}

GateMenu::~GateMenu()
{
}

void GateMenu::update_gate(const DplDevice::GatePointer &gate)
{
    m_switchItem->set_current_index(!gate->is_visible());
    update_startItem(gate);
}

void GateMenu::update_startItem(const DplDevice::GatePointer &gate)
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_startItem->set_unit(US_STR);
    } else {
        m_startItem->set_unit(MM_STR);
    }

    m_startItem->set(Tool::cnf_to_display(m_group, m_group->sample()->start()),
                     Tool::cnf_to_display(m_group, m_group->sample()->start()+m_group->sample()->range()),
                     2);
    m_startItem->set_value(Tool::cnf_to_display(m_group, gate->start()));
}

void GateMenu::do_gateItem_changed(int val)
{
    update_gate(m_group->gate(static_cast<DplDevice::Gate::Type>(val)));
}

void GateMenu::do_startItem_changed(double val)
{
    DplDevice::GatePointer gate = m_group->gate(static_cast<DplDevice::Gate::Type>(m_gateItem->current_index()));
    gate->set_start(Tool::display_to_cnf(m_group, val));
}

void GateMenu::do_switchItem_changed(int index)
{
    m_group->gate(static_cast<DplDevice::Gate::Type>(m_gateItem->current_index()))->set_visible(!index);
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

void GateMenu::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    m_group = group;
    update_gate(group->gate(DplDevice::Gate::A));
    do_paramsItem_changed(m_paramsItem->current_index());
}

}
