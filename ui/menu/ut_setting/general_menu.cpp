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

#include "general/gain_menu_item.h"
#include "general/start_menu_item.h"
#include "general/range_menu_item.h"

#include <qmath.h>

namespace DplUtSettingMenu {

GeneralMenu::GeneralMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gainItem(new GainMenuItem(this)),
    m_startItem(new StartMenuItem(this)),
    m_rangeItem(new RangeMenuItem(this)),
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
    connect(m_utUnitItem, SIGNAL(value_changed(int)),
            this, SLOT(do_utUnitItem_changed(int)));

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
    m_group = group;

    m_velocityItem->set_value(m_group->focallawer()->specimen()->velocity());

    double delay = m_group->focallawer()->wedge()->delay();
    m_wedgeDelayItem->set_value(Dpl::ns_to_us(delay));

    m_utUnitItem->set_current_index(m_group->ut_unit());
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
}

}
