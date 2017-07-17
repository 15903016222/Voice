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

GeneralMenu::GeneralMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Gain Item */
    connect(&m_gainItem, SIGNAL(value_changed(double)), this, SLOT(do_gainItem_changed(double)));
    connect(&m_gainItem, SIGNAL(value_changed(double)), this, SIGNAL(gain_changed(double)));

    /* Start Item */
    connect(&m_startItem, SIGNAL(value_changed(double)), this, SLOT(do_startItem_changed(double)));

    /* Range Item */
    connect(&m_rangeItem, SIGNAL(value_changed(double)), this, SLOT(do_rangeItem_changed(double)));

    /* Velocity Item */
    m_velocityItem.set(tr("Velocity"), "m/s", 635, 12540, 1, 0.1);
    connect(&m_velocityItem, SIGNAL(value_changed(double)), this, SLOT(do_velocityItem_changed(double)));

    /* Wedge Delay Item */
    m_wedgeDelayItem.set(tr("Wedge Delay"), "&micro;s", 0, 1000, 2);
    connect(&m_wedgeDelayItem, SIGNAL(value_changed(double)), this, SLOT(do_wedgeDelayItem_changed(double)));

    /* Ut Unit Item */
    QStringList utUnitList;
    utUnitList.append(tr("Time"));
    utUnitList.append(tr("Sound Path"));
    utUnitList.append(tr("True Path"));
    m_utUnitItem.set(tr("UT Unit"), utUnitList);
    connect(&m_utUnitItem, SIGNAL(value_changed(int)), this, SLOT(do_utUnitItem_changed(int)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));
    do_current_group_changed(DplDevice::Device::instance()->current_group());
}

GeneralMenu::~GeneralMenu()
{
}

void GeneralMenu::show()
{
    update();
    ui->layout0->addWidget(&m_gainItem);
    ui->layout1->addWidget(&m_startItem);
    ui->layout2->addWidget(&m_rangeItem);
    ui->layout3->addWidget(&m_velocityItem);
    ui->layout4->addWidget(&m_wedgeDelayItem);
    ui->layout5->addWidget(&m_utUnitItem);

    m_gainItem.show();
    m_startItem.show();
    m_rangeItem.show();
    m_velocityItem.show();
    m_wedgeDelayItem.show();
    m_utUnitItem.show();

//    BaseMenu::show();
}

void GeneralMenu::hide()
{
//    ui->layout0->removeWidget(&m_gainItem);
//    ui->layout1->removeWidget(&m_startItem);
//    ui->layout2->removeWidget(&m_rangeItem);
//    ui->layout3->removeWidget(&m_velocityItem);
//    ui->layout4->removeWidget(&m_wedgeDelayItem);
//    ui->layout5->removeWidget(&m_utUnitItem);
    m_gainItem.hide();
    m_startItem.hide();
    m_rangeItem.hide();
    m_velocityItem.hide();
    m_wedgeDelayItem.hide();
    m_utUnitItem.hide();
}

void GeneralMenu::update()
{
    update_gain_item();
    update_start_item();
    update_range_item();

    m_velocityItem.set_value(m_group->sample()->velocity());

    double delay = m_group->focallawer()->wedge()->delay();
    m_wedgeDelayItem.set_value(Dpl::ns_to_us(delay));

    m_utUnitItem.set_current_index(m_group->ut_unit());

    m_updateFlag = false;
}

void GeneralMenu::do_gainItem_changed(double gain)
{
    m_group->sample()->set_gain(gain);
}

void GeneralMenu::do_startItem_changed(double value)
{
    double start;

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        start = Dpl::us_to_ns(value);
    } else {
        value = Dpl::mm_to_m(value);
        start = value * 2 / m_group->sample()->velocity();
        start = Dpl::s_to_ns(start);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            start /= qCos(m_group->current_angle());
        }
    }

    m_group->sample()->set_start(start);
}

void GeneralMenu::do_rangeItem_changed(double value)
{
    double range;
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        range = Dpl::us_to_ns(value);
    } else {
        value = Dpl::mm_to_m(value);
        range = value * 2 / m_group->sample()->velocity();
        range = Dpl::s_to_ns(range);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            range /= qCos(m_group->current_angle());
        }
    }

    m_group->sample()->set_range(range);
}

void GeneralMenu::do_velocityItem_changed(double value)
{
    m_group->sample()->set_velocity(value);
}

void GeneralMenu::do_wedgeDelayItem_changed(double value)
{
    m_group->focallawer()->wedge()->set_delay(Dpl::us_to_ns(value));
}

void GeneralMenu::do_utUnitItem_changed(int index)
{
    m_group->set_ut_unit((DplDevice::Group::UtUnit)index);
    update_start_item();
    update_range_item();
}

void GeneralMenu::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    m_group = group;
    if (m_gainItem.isHidden()) {
        m_updateFlag = true;
    } else {
        update();
    }
}

void GeneralMenu::update_gain_item()
{
    m_gainItem.set(tr("Gain"), "dB", 0, 90, 1);
    m_gainItem.set_value(m_group->sample()->gain());
}

void GeneralMenu::update_start_item()
{
    double max = 0.0;
    double value = 0.0;
    double step = 0.0;
    QString unit = "mm";

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        /* 时间显示全声程 */
        max = Dpl::ns_to_us(m_group->max_start());
        value = Dpl::ns_to_us(m_group->sample()->start());
        unit = "&micro;s";
        step = Dpl::ns_to_us(DplFpga::Fpga::SAMPLE_PRECISION);
    } else {
        /* mm显示半声程 */
        max = Dpl::ns_to_s(m_group->max_start()) * m_group->sample()->velocity() / 2;
        max = Dpl::m_to_mm(max);
        step = Dpl::ns_to_s(DplFpga::Fpga::SAMPLE_PRECISION) * m_group->sample()->velocity() / 2;
        step = Dpl::m_to_mm(step);
        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            max *= qCos(m_group->current_angle());
            value *= qCos(m_group->current_angle());
            step *= qCos(m_group->current_angle());
        }
    }

    m_startItem.set(tr("Start"), unit, 0, max, 2, step);
    m_startItem.set_value(value);
}

void GeneralMenu::update_range_item()
{
    double min = 0.0;
    double max = 0.0;
    double value = 0.0;
    double step = 0.0;
    QString unit = "mm";

    max = m_group->sample()->point_qty() * m_group->sample()->precision() * DplUt::Sample::MAX_SCALE_FACTOR;
    if (max > m_group->max_range()) {
        max = m_group->max_range();
    }

    if (m_group->sample()->is_auto_set_point_qty()) {
        min = 32 * m_group->sample()->precision() * 1;
    } else {
        min = m_group->sample()->point_qty() * m_group->sample()->precision() * 1;
    }

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        /* 时间轴 */
        max = Dpl::ns_to_us(max);
        min = Dpl::ns_to_us(min);
        value = Dpl::ns_to_us(m_group->sample()->range());
        step = Dpl::ns_to_us(m_group->sample()->precision());
        unit = "&micro;s";
    } else {
        min = Dpl::ns_to_s(min) * m_group->sample()->velocity() / 2;
        min = Dpl::m_to_mm(min);
        max = Dpl::ns_to_s(max) * m_group->sample()->velocity() / 2;
        max = Dpl::m_to_mm(max);

        value = Dpl::ns_to_s(m_group->sample()->range()) * m_group->sample()->velocity() / 2;
        value = Dpl::m_to_mm(value);

        step = Dpl::ns_to_s(m_group->sample()->precision()) * m_group->sample()->velocity() / 2;
        step = Dpl::m_to_mm(step);

        if (m_group->ut_unit() == DplDevice::Group::TruePath) {
            min *= qCos(m_group->current_angle());
            max *= qCos(m_group->current_angle());
            value *= qCos(m_group->current_angle());
            step *= qCos(m_group->current_angle());
        }
    }

    m_rangeItem.set(tr("Range"), unit, min, max, 2, step);
    m_rangeItem.set_value(value);
}

}
