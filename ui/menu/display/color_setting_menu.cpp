/**
 * @file color_setting_menu.cpp
 * @brief Color Setting menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "color_setting_menu.h"
#include "ui_base_menu.h"

namespace DplDisplayMenu {

ColorSettingMenu::ColorSettingMenu(QWidget *parent) :
    BaseMenu(parent),
    m_amplitudeItem(new LabelMenuItem(this, tr("Amplitude"))),
    m_depthItem(new LabelMenuItem(this, tr("Depth"))),
    m_tofdItem(new LabelMenuItem(this, tr("TOFD")))
{
    ui->layout0->addWidget(m_amplitudeItem);
    ui->layout1->addWidget(m_depthItem);
    ui->layout2->addWidget(m_tofdItem);
}

ColorSettingMenu::~ColorSettingMenu()
{

}

}
