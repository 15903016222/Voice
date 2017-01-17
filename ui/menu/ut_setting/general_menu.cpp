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

#include <global.h>

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
    connect(m_rangeItem, SIGNAL(value_changed(double)), this, SLOT(do_rangeItem_changed(double)));

    m_velocityItem = new SpinMenuItem();
    m_velocityItem->set(tr("Velocity"), "m/s", 635, 12540, 1, 0.1);
    connect(m_velocityItem, SIGNAL(value_changed(double)), this, SLOT(do_velocityItem_changed(double)));

    m_wedgeDelayItem = new SpinMenuItem();
    m_wedgeDelayItem->set(tr("Wedge Delay"), "&micro;s", 0, 1000, 2);
    connect(m_wedgeDelayItem, SIGNAL(value_changed(double)), this, SLOT(do_wedgeDelayItem_changed(double)));

    m_utUnitItem = new ComboMenuItem();
    m_utUnitItem->set(tr("UT Unit"), utUnitList);
    connect(m_utUnitItem, SIGNAL(value_changed(int)), this, SLOT(do_utUnitItem_changed(int)));

    m_updateFlag = true;
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
    update_range_item();

    m_velocityItem->set_value(m_group->velocity());

    double delay = m_group->get_wedge()->delay();
    m_wedgeDelayItem->set_value(Dpl::ns_to_us(delay));

    m_utUnitItem->set_current_index(m_group->ut_unit());

    m_updateFlag = false;
}

void GeneralMenu::do_gainItem_changed(double gain)
{
    m_group->set_gain(gain);
}

void GeneralMenu::do_startItem_changed(double value)
{
    double start;

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        start = Dpl::us_to_ns(value);
    } else {
        value = Dpl::mm_to_m(value);
        start = value * 2 / m_group->velocity();
        start = Dpl::s_to_ns(start);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            start /= qCos(m_group->current_angle());
        }
    }

    m_group->set_start(start);
}

void GeneralMenu::do_rangeItem_changed(double value)
{
    double range;
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        range = Dpl::us_to_ns(value);
    } else {
        value = Dpl::mm_to_m(value);
        range = value * 2 / m_group->velocity();
        range = Dpl::s_to_ns(range);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            range /= qCos(m_group->current_angle());
        }
    }

    m_group->set_range(range);
}

void GeneralMenu::do_velocityItem_changed(double value)
{
    m_group->set_velocity(value);
}

void GeneralMenu::do_wedgeDelayItem_changed(double value)
{
    DplProbe::WedgePointer wedge = m_group->get_wedge();
    wedge->set_delay(Dpl::us_to_ns(value));
}

void GeneralMenu::do_utUnitItem_changed(int index)
{
    m_group->set_ut_unit((DplDevice::Group::UtUnit)index);
    update_start_item();
    update_range_item();
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
    double max = 0.0;
    double value = 0.0;
    double step = 0.0;
    float precision = DplFpga::Fpga::get_instance()->sample_precision();
    QString unit = "mm";

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        /* 时间显示全声程 */
        max = Dpl::ns_to_us(m_group->max_start());
        value = Dpl::ns_to_us(m_group->start());
        unit = "&micro;s";
        step = Dpl::ns_to_us(precision);
    } else {
        /* mm显示半声程 */
        max = Dpl::ns_to_s(m_group->max_start()) * m_group->velocity() / 2;
        max = Dpl::m_to_mm(max);
        step = Dpl::ns_to_s(precision) * m_group->velocity() / 2;
        step = Dpl::m_to_mm(step);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            max *= qCos(m_group->current_angle());
            value *= qCos(m_group->current_angle());
            step *= qCos(m_group->current_angle());
        }
    }

    m_startItem->set(tr("Start"), unit, 0, max, 2, step);
    m_startItem->set_value(value);
}

void GeneralMenu::update_range_item()
{
    double min = 0.0;
    double max = 0.0;
    double value = 0.0;
    double step = 0.0;
    float precision = DplFpga::Fpga::get_instance()->sample_precision();
    QString unit = "mm";

    max = m_group->point_qty() * 2;
    if (max > Dpl::ns_to_us(m_group->max_range())) {
        max = Dpl::ns_to_us(m_group->max_range());
    }

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        if (m_group->point_qty_mode() == DplDevice::Group::PointQtyAuto) {
            min = 32 * Dpl::ns_to_us(precision);
        } else {
            min = m_group->point_qty() * Dpl::ns_to_us(precision);
        }
        value = Dpl::ns_to_us(m_group->range());
        step = Dpl::ns_to_us(precision);
        unit = "&micro;s";
    } else {
        if (m_group->point_qty_mode() == DplDevice::Group::PointQtyAuto) {
            min = 32 * Dpl::ns_to_s(static_cast<double>(precision))
                    * m_group->velocity()
                    / 2;
            min = Dpl::m_to_mm(min);
        } else {
            min = m_group->point_qty()
                    * Dpl::ns_to_s(static_cast<double>(precision))
                    * m_group->velocity()
                    / 2;
            min = Dpl::m_to_mm(min);
        }
        max = Dpl::us_to_s(max) * m_group->velocity() / 2;
        max = Dpl::m_to_mm(max);

        value = Dpl::ns_to_s(m_group->range()) * m_group->velocity() / 2;
        value = Dpl::m_to_mm(value);

        step = Dpl::ns_to_s(static_cast<double>(precision)) * m_group->velocity() / 2;
        step = Dpl::m_to_mm(step);

        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            min *= qCos(m_group->current_angle());
            max *= qCos(m_group->current_angle());
            value *= qCos(m_group->current_angle());
            step *= qCos(m_group->current_angle());
        }
    }

    m_rangeItem->set(tr("Range"), unit, min, max, 2, step);
    m_rangeItem->set_value(value);
}

}
