/**
 * @file color_setting_menu.cpp
 * @brief Color Setting menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "color_setting_menu.h"


namespace DplDisplayMenu {

ColorSettingMenu::ColorSettingMenu(QWidget *parent) :
    BaseMenu(parent),
    m_amplitudeItem(new LabelMenuItem(this, tr("Amplitude"))),
    m_depthItem(new LabelMenuItem(this, tr("Depth"))),
    m_tofdItem(new LabelMenuItem(this, tr("TOFD")))
{
    m_layout0->addWidget(m_amplitudeItem);
    m_layout1->addWidget(m_depthItem);
    m_layout2->addWidget(m_tofdItem);
}

ColorSettingMenu::~ColorSettingMenu()
{

}

}
