/**
 * @file gate_menu.cpp
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "gate_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

#include <global.h>
#include <device/device.h>
#include <ui/tool/tool.h>

namespace DplGateCurvesMenu {

GateMenu::GateMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent),
    m_gateItem(new ComboMenuItem),
    m_switchItem(new ComboMenuItem),
    m_paramsItem(new ComboMenuItem),
    m_startItem(new SpinMenuItem),
    m_widthItem(new SpinMenuItem),
    m_thresholdItem(new SpinMenuItem),
    m_synchroItem(new ComboMenuItem),
    m_measureModeItem(new ComboMenuItem)
{
    ui->layout0->addWidget(m_gateItem);
    ui->layout1->addWidget(m_switchItem);
    ui->layout2->addWidget(m_paramsItem);
    ui->layout3->addWidget(m_startItem);
    ui->layout4->addWidget(m_widthItem);
    ui->layout5->addWidget(m_thresholdItem);
    ui->layout3->addWidget(m_synchroItem);
    ui->layout4->addWidget(m_measureModeItem);

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

    m_gateItem->set(tr("Gate"), gatesList);
    connect(m_gateItem, SIGNAL(value_changed(int)),
            this, SLOT(do_gateItem_changed(int)));

    m_switchItem->set(tr("Switch"), s_onOff);
    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));

    QStringList modeList;
    modeList.append(tr("Position"));
    modeList.append(tr("Mode"));
    m_paramsItem->set(tr("Parameters"), modeList);
    connect(m_paramsItem, SIGNAL(value_changed(int)),
            this, SLOT(do_paramsItem_changed(int)));

    m_startItem->set(tr("Start"), "mm", 0, 16000, 2);
    connect(m_startItem, SIGNAL(value_changed(double)),
            this, SLOT(do_startItem_changed(double)));

    m_widthItem->set(tr("Width"), "mm", 0.05, 525, 2);
    m_thresholdItem->set(tr("Threshold"), "%", 0, 100, 0);
    m_synchroItem->set(tr("Synchro"), synchrosList);
    m_measureModeItem->set(tr("Measure Mode"), measureModesList);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

GateMenu::~GateMenu()
{
    delete m_gateItem;
    delete m_switchItem;
    delete m_paramsItem;
    delete m_startItem;
    delete m_widthItem;
    delete m_thresholdItem;
    delete m_synchroItem;
    delete m_measureModeItem;
}

void GateMenu::show()
{
    m_gateItem->show();
    m_switchItem->show();
    m_paramsItem->show();
    if (m_paramsItem->current_index() == 0) {
        m_startItem->show();
        m_widthItem->show();
        m_thresholdItem->show();
    } else {
        m_synchroItem->show();
        m_measureModeItem->show();
    }
}

void GateMenu::hide()
{
    m_gateItem->hide();
    m_switchItem->hide();
    m_paramsItem->hide();
    m_startItem->hide();
    m_widthItem->hide();
    m_thresholdItem->hide();
    m_synchroItem->hide();
    m_measureModeItem->hide();
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
    Q_UNUSED(index);
    hide();
    show();
}

void GateMenu::update(const DplDevice::GroupPointer &group)
{
    m_group = group;
    update_gate(group->gate(DplDevice::Gate::A));
}

}
