/**
 * @file general_menu.cpp
 * @brief UT Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "general_menu.h"
#include <global.h>
#include <ui/tool/tool.h>

#include <qmath.h>

namespace DplUtSettingMenu {

GeneralMenu::GeneralMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gainItem(new SpinMenuItem(this, tr("Gain"), "dB")),
    m_startItem(new SpinMenuItem(this, tr("Start"))),
    m_rangeItem(new SpinMenuItem(this, tr("Range"))),
    m_velocityItem(new SpinMenuItem(this, tr("Velocity"), "m/s")),
    m_wedgeDelayItem(new SpinMenuItem(this, tr("Wedge Delay"), US_STR)),
    m_utUnitItem(new ComboMenuItem(this, tr("UT Unit")))
{
    m_layout0->addWidget(m_gainItem);
    m_layout1->addWidget(m_startItem);
    m_layout2->addWidget(m_rangeItem);
    m_layout3->addWidget(m_velocityItem);
    m_layout4->addWidget(m_wedgeDelayItem);
    m_layout5->addWidget(m_utUnitItem);

    /* Gain Item */
    connect(m_gainItem, SIGNAL(value_changed(double)), this, SLOT(do_gainItem_changed(double)));
    connect(m_gainItem, SIGNAL(value_changed(double)), this, SIGNAL(gain_changed(double)));

    /* Start Item */
    connect(m_startItem, SIGNAL(value_changed(double)), this, SLOT(do_startItem_changed(double)));

    /* Range Item */
    connect(m_rangeItem, SIGNAL(value_changed(double)), this, SLOT(do_rangeItem_changed(double)));

    /* Velocity Item */
    m_velocityItem->set(635, 12540, 1);
    connect(m_velocityItem, SIGNAL(value_changed(double)), this, SLOT(do_velocityItem_changed(double)));

    /* Wedge Delay Item */
    m_wedgeDelayItem->set(0, 1000, 2);
    connect(m_wedgeDelayItem, SIGNAL(value_changed(double)), this, SLOT(do_wedgeDelayItem_changed(double)));

    /* Ut Unit Item */
    QStringList utUnitList;
    utUnitList.append(tr("Time"));
    utUnitList.append(tr("Sound Path"));
    utUnitList.append(tr("True Path"));
    m_utUnitItem->set(utUnitList);
    connect(m_utUnitItem, SIGNAL(value_changed(int)), this, SLOT(do_utUnitItem_changed(int)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

GeneralMenu::~GeneralMenu()
{
    delete m_utUnitItem;
}

void GeneralMenu::update(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(group.data()),
                   SIGNAL(mode_changed(DplDevice::Group::Mode)),
                   this,
                   SLOT(update_gain_item()));
    }

    m_group = group;

    connect(static_cast<DplDevice::Group *>(group.data()),
            SIGNAL(mode_changed(DplDevice::Group::Mode)),
            this,
            SLOT(update_gain_item()));

    update_gain_item();
    update_start_item();
    update_range_item();

    m_velocityItem->set_value(m_group->focallawer()->specimen()->velocity());

    double delay = m_group->focallawer()->wedge()->delay();
    m_wedgeDelayItem->set_value(Dpl::ns_to_us(delay));

    m_utUnitItem->set_current_index(m_group->ut_unit());
}

void GeneralMenu::do_gainItem_changed(double gain)
{
    m_group->sample()->set_gain(gain);
}

void GeneralMenu::do_startItem_changed(double value)
{
    m_group->sample()->set_start(Tool::display_to_cnf(m_group, value));
}

void GeneralMenu::do_rangeItem_changed(double value)
{
    m_group->sample()->set_range(Tool::display_to_cnf(m_group, value));
}

void GeneralMenu::do_velocityItem_changed(double value)
{
    m_group->focallawer()->specimen()->set_velocity(value);
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

void GeneralMenu::update_gain_item()
{
    if (m_group->mode() == DplDevice::Group::UT1
            || m_group->mode() == DplDevice::Group::UT2) {
        m_gainItem->set(0, 110, 1, 0.1);
    } else {
        m_gainItem->set(0, 80, 1, 0.1);
    }
    m_gainItem->set_value(m_group->sample()->gain());
}

void GeneralMenu::update_start_item()
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_startItem->set_unit(US_STR);
    } else {
        m_startItem->set_unit(MM_STR);
    }

    m_startItem->set(0,
                     Tool::cnf_to_display(m_group, m_group->max_start()),
                     2,
                     Tool::cnf_to_display(m_group, m_group->sample()->precision()));

    m_startItem->set_value(Tool::cnf_to_display(m_group, m_group->sample()->start()));
}

void GeneralMenu::update_range_item()
{
    double max = m_group->sample()->point_qty() * m_group->sample()->precision() * DplUt::Sample::MAX_SCALE_FACTOR;
    if (max > m_group->max_range()) {
        max = m_group->max_range();
    }

    double min = 0.0;
    double step = 0.0;
    if (m_group->sample()->is_auto_set_point_qty()) {
        min = 32 * m_group->sample()->precision() * 1;
        step = m_group->sample()->precision();
    } else {
        min = m_group->sample()->point_qty() * m_group->sample()->precision() * 1;
        step = m_group->sample()->point_qty() * m_group->sample()->precision();
    }

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_rangeItem->set_unit(US_STR);
    } else {
        m_rangeItem->set_unit(MM_STR);
    }

    m_rangeItem->set(Tool::cnf_to_display(m_group, min),
                     Tool::cnf_to_display(m_group, max),
                     2,
                     Tool::cnf_to_display(m_group, step));
    m_rangeItem->set_value(Tool::cnf_to_display(m_group, m_group->sample()->range()));
}

}
