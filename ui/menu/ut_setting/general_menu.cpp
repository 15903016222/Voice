/**
 * @file general_menu.cpp
 * @brief UT Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "general_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

#include <qmath.h>
#include <QDebug>

namespace DplUtSettingMenu {

GeneralMenu::GeneralMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_device = DplDevice::Device::get_instance();

    QStringList utUnitList;
    utUnitList.append(tr("Time"));
    utUnitList.append(tr("Sound Path"));
    utUnitList.append(tr("True Path"));

    m_gainItem = new SpinMenuItem();
    m_gainItem->set(tr("Gain"), "dB", 0, 90, 1);
    connect(m_gainItem, SIGNAL(value_changed(double)), this, SLOT(do_gainItem_changed(double)));
    connect(m_gainItem, SIGNAL(value_changed(double)), this, SIGNAL(gain_changed(double)));

    m_startItem = new SpinMenuItem();
    m_startItem->set(tr("Start"), "mm", 0, 1000, 2);
    connect(m_startItem, SIGNAL(value_changed(double)), this, SLOT(do_startItem_changed(double)));

    m_rangeItem = new SpinMenuItem();
    m_rangeItem->set(tr("Range"), "mm", 0, 1000, 2);

    m_velocityItem = new SpinMenuItem();
    m_velocityItem->set(tr("Velocity"), "m/s", 635, 12540, 1);
    connect(m_velocityItem, SIGNAL(value_changed(double)), this, SLOT(do_velocityItem_changed(double)));

    m_wedgeDelayItem = new SpinMenuItem();
    m_wedgeDelayItem->set(tr("Wedge Delay"), "&micro;s", 0, 1000, 2);

    m_utUnitItem = new ComboMenuItem();
    m_utUnitItem->set(tr("UT Unit"), utUnitList);
}

GeneralMenu::~GeneralMenu()
{
    delete m_gainItem;
    delete m_startItem;
    delete m_rangeItem;
    delete m_velocityItem;
    delete m_wedgeDelayItem;
    delete m_utUnitItem;
}

void GeneralMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_gainItem);
    ui->menuItem1->layout()->addWidget(m_startItem);
    ui->menuItem2->layout()->addWidget(m_rangeItem);
    ui->menuItem3->layout()->addWidget(m_velocityItem);
    ui->menuItem4->layout()->addWidget(m_wedgeDelayItem);
    ui->menuItem5->layout()->addWidget(m_utUnitItem);
    m_gainItem->show();
    m_startItem->show();
    m_rangeItem->show();
    m_velocityItem->show();
    m_wedgeDelayItem->show();
    m_utUnitItem->show();
}

void GeneralMenu::hide()
{
    DplDevice::GroupPointer group = m_device->current_group();
    m_gainItem->set_value(group->gain());
//    m_startItem->set_value(group->start());
//    m_rangeItem->set_value(group->range());
    m_velocityItem->set_value(group->velocity());
//    m_wedgeDelayItem->set_value(group->wedgetDelay());

    ui->menuItem0->layout()->removeWidget(m_gainItem);
    ui->menuItem1->layout()->removeWidget(m_startItem);
    ui->menuItem2->layout()->removeWidget(m_rangeItem);
    ui->menuItem3->layout()->removeWidget(m_velocityItem);
    ui->menuItem4->layout()->removeWidget(m_wedgeDelayItem);
    ui->menuItem5->layout()->removeWidget(m_utUnitItem);
    m_gainItem->hide();
    m_startItem->hide();
    m_rangeItem->hide();
    m_velocityItem->hide();
    m_wedgeDelayItem->hide();
    m_utUnitItem->hide();
}

void GeneralMenu::do_gainItem_changed(double gain)
{
    m_device->current_group()->set_gain(gain, true);
}

void GeneralMenu::do_startItem_changed(double pos)
{
    DplDevice::GroupPointer group = m_device->current_group();
    int start;
    if (group->ut_unit() == DplDevice::Group::TruePath) {
        start = (int)(pos * 2000000.0 /
                (qCos(group->current_angle()) * group->velocity()));
    } else if (group->ut_unit() == DplDevice::Group::SoundPath) {
        start = (int)(pos * 2000000.0 / group->velocity());
    } else {
        /* 显示方式为时间 */
        start = (int) (pos * 1000.0);
    }

    group->set_start(start);
}

void GeneralMenu::do_rangeItem_changed(double value)
{
    m_device->current_group()->set_sample_range(value);
    //    m_fpga->current_group()->
}

void GeneralMenu::do_velocityItem_changed(double value)
{
    m_device->current_group()->set_velocity(value);
}

}
