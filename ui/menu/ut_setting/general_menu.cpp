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
    DplDevice::Device *device = DplDevice::Device::get_instance();
    connect(device, SIGNAL(current_group_changed()), this, SLOT(do_current_group_changed()));
    m_group = device->current_group();

    QStringList utUnitList;
    utUnitList.append(tr("Time"));
    utUnitList.append(tr("Sound Path"));
    utUnitList.append(tr("True Path"));

    m_gainItem = new SpinMenuItem();
    connect(m_gainItem, SIGNAL(value_changed(double)), this, SLOT(do_gainItem_changed(double)));
    connect(m_gainItem, SIGNAL(value_changed(double)), this, SIGNAL(gain_changed(double)));

    m_startItem = new SpinMenuItem();
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
    connect(m_utUnitItem, SIGNAL(value_changed(int)), this, SLOT(do_utUnitItem_changed(int)));
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
    if (m_updateFlag) {
        update();
    }
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

void GeneralMenu::update()
{
    update_gain_item();
    update_start_item();
    m_utUnitItem->set_current_index(m_group->ut_unit());
    m_updateFlag = false;
}

void GeneralMenu::do_gainItem_changed(double gain)
{
    if (m_group->gain() == gain) {
        return;
    }
    m_group->set_gain(gain, true);
}

void GeneralMenu::do_startItem_changed(double pos)
{
    qDebug()<<__func__<<__LINE__<<"pos="<<pos<<m_startItem->get_value();

    double start;
    if (m_group->ut_unit() == DplDevice::Group::TruePath) {
        start = (pos * 2000000.0 /
                (qCos(m_group->current_angle()) * m_group->velocity()));
    } else if (m_group->ut_unit() == DplDevice::Group::SoundPath) {
        start = pos * 2000000.0 / m_group->velocity();
    } else {
        /* 显示方式为时间 */
        start = pos * 1000.0;
    }

    m_group->set_start(start);
}

void GeneralMenu::do_rangeItem_changed(double value)
{
    double range;
    if (m_group->ut_unit() == DplDevice::Group::TruePath) {
        range = (value * 2000000.0 /
                (qCos(m_group->current_angle()) * m_group->velocity()));
    } else if (m_group->ut_unit() == DplDevice::Group::SoundPath) {
        range = (value * 2000000.0 / m_group->velocity());
    } else {
        /* 显示方式为时间 */
        range = (value * 1000.0);
    }
    m_group->set_range(range);
}

void GeneralMenu::do_velocityItem_changed(double value)
{
    m_group->set_velocity(value);
}

void GeneralMenu::do_utUnitItem_changed(int index)
{
    m_group->set_ut_unit((DplDevice::Group::UtUnit)index);
    update_start_item();
    emit ut_unit_changed();
}

void GeneralMenu::do_current_group_changed()
{
    m_group = DplDevice::Device::get_instance()->current_group();
    if (m_gainItem->isHidden()) {
        m_updateFlag = true;
    } else {
        update();
    }
}

void GeneralMenu::update_gain_item()
{
    m_gainItem->set(tr("Gain"), "dB", 0, 90, 1);
    m_gainItem->set_value(m_group->gain());
}

void GeneralMenu::update_start_item()
{
    double upper = 0.0;
    double value = 0.0;
    QString unit = "mm";

    qDebug()<<"start="<<m_group->start()<<"range="<<m_group->range()<<"velocity="<<m_group->velocity();
    if (m_group->ut_unit() == DplDevice::Group::TruePath) {
        upper = (m_group->max_rx_time() - m_group->range()) * m_group->velocity() / (2*1000*1000);
        upper *= qCos(m_group->current_angle());

        value = m_group->start() * m_group->velocity() / (2*1000*1000);
        value *= qCos(m_group->current_angle());
    } else if (m_group->ut_unit() == DplDevice::Group::SoundPath) {
        upper = (m_group->max_rx_time() - m_group->range()) * m_group->velocity() / (2*1000*1000);
        value = m_group->start() * m_group->velocity() / (2*1000*1000);
    } else {
        upper = (m_group->max_rx_time() - m_group->range()) / 1000;
        value = m_group->start()/1000.0;
        unit = "&micro;s";
    }

    qDebug()<<__func__<<"upper="<<upper<<"value="<<value;
    m_startItem->set(tr("Start"), unit, 0, upper, 2);
    m_startItem->set_value(value);
}

}
