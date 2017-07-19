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

namespace DplGateCurvesMenu {

GateMenu::GateMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent),
    m_gateItem(new ComboMenuItem),
    m_startItem(new SpinMenuItem),
    m_widthItem(new SpinMenuItem),
    m_thresholdItem(new SpinMenuItem),
    m_synchroItem(new ComboMenuItem),
    m_measureModeItem(new ComboMenuItem)
{
    ui->layout0->addWidget(m_gateItem);
    ui->layout1->addWidget(m_startItem);
    ui->layout2->addWidget(m_widthItem);
    ui->layout3->addWidget(m_thresholdItem);
    ui->layout4->addWidget(m_synchroItem);
    ui->layout5->addWidget(m_measureModeItem);

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

    m_startItem->set(tr("Start"), "mm", 0, 16000, 2);
    connect(m_startItem, SIGNAL(value_changed(double)),
            this, SLOT(do_startItem_changed(double)));

    m_widthItem->set(tr("Width"), "mm", 0.05, 525, 2);
    m_thresholdItem->set(tr("Threshold"), "%", 0, 100, 0);
    m_synchroItem->set(tr("Synchro"), synchrosList);
    m_measureModeItem->set(tr("Measure Mode"), measureModesList);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));
    do_current_group_changed(DplDevice::Device::instance()->current_group());
}

GateMenu::~GateMenu()
{
    delete m_gateItem;
    delete m_startItem;
    delete m_widthItem;
    delete m_thresholdItem;
    delete m_synchroItem;
    delete m_measureModeItem;
}

void GateMenu::show()
{
    m_gateItem->show();
    m_startItem->show();
    m_widthItem->show();
    m_thresholdItem->show();
    m_synchroItem->show();
    m_measureModeItem->show();
}

void GateMenu::hide()
{
    m_gateItem->hide();
    m_startItem->hide();
    m_widthItem->hide();
    m_thresholdItem->hide();
    m_synchroItem->hide();
    m_measureModeItem->hide();
}

void GateMenu::do_startItem_changed(double val)
{
    if (m_group->ut_unit() != DplDevice::Group::Time) {
        val = Dpl::us_to_ns(val);
    } else {
        val = Dpl::mm_to_m(val);
        val = val * 2 / m_group->sample()->velocity();
        val = Dpl::s_to_ns(val);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            val /= qCos(m_group->current_angle());
        }
    }

    m_group->gate(static_cast<DplDevice::Gate::Type>(m_gateItem->current_index()))->set_start(val);
}

void GateMenu::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    m_group = group;
}

}
