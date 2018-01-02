/**
 * @file general_menu.cpp
 * @brief UT Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "general_menu.h"

#include "general/gain_menu_item.h"
#include "general/start_menu_item.h"
#include "general/range_menu_item.h"
#include "general/velocity_menu_item.h"
#include "general/delay_menu_item.h"
#include "general/unit_menu_item.h"

namespace DplUtSettingMenu {

GeneralMenu::GeneralMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gainItem(new GainMenuItem(this)),
    m_startItem(new StartMenuItem(this)),
    m_rangeItem(new RangeMenuItem(this)),
    m_velocityItem(new VelocityMenuItem(this)),
    m_wedgeDelayItem(new DelayMenuItem(this)),
    m_utUnitItem(new UnitMenuItem(this))
{
    m_layout0->addWidget(m_gainItem);
    m_layout1->addWidget(m_startItem);
    m_layout2->addWidget(m_rangeItem);
    m_layout3->addWidget(m_velocityItem);
    m_layout4->addWidget(m_wedgeDelayItem);
    m_layout5->addWidget(m_utUnitItem);
}

}
