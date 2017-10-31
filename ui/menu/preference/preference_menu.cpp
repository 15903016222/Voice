/**
 * @file preference_menu.cpp
 * @brief Preference Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "preference_menu.h"
#include "ui_base_menu.h"
#include <device/device.h>

namespace DplPreferenceMenu {

PreferenceMenu::PreferenceMenu(QWidget *parent) :
    BaseMenu(parent),
    m_brightItem(new SpinMenuItem(this, tr("Bright"), "%")),
    m_opacityItem(new SpinMenuItem(this, tr("Opacity"), "%")),
    m_languageItem(new ComboMenuItem(this, tr("Language"))),
    m_startingPageItem(new ComboMenuItem(this, tr("Starting Page"))),
    m_gatemodeItem(new ComboMenuItem(this, tr("Gate Mode"))),
    m_deployItem(new LabelMenuItem(this, tr("Deploy")))
{
    ui->layout0->addWidget(m_brightItem);
    ui->layout1->addWidget(m_opacityItem);
    ui->layout2->addWidget(m_languageItem);
    ui->layout3->addWidget(m_startingPageItem);
    ui->layout4->addWidget(m_gatemodeItem);
    ui->layout5->addWidget(m_deployItem);

    m_mcu = Mcu::instance();

    /* Bright menu item */
    m_brightItem->set(1, 100, 0);
    connect(m_brightItem, SIGNAL(value_changed(double)),
            this, SLOT(set_brightness(double)));
    m_brightItem->set_value(100);

    /* Opacity menu item */
    m_opacityItem->set(20, 100, 0);
    m_opacityItem->set_value(80);
    connect(m_opacityItem, SIGNAL(value_changed(double)),
            this, SIGNAL(opacity_changed(double)));

    /* Language menu item */
    m_languageItem->add_item(tr("English"));
    m_languageItem->add_item(tr("Chinese"));

    /* Starting Page Menu Item */
    m_startingPageItem->set(s_onOff);

    /* Gate Mode */
    m_gatemodeItem->set(s_onOff);

    /* Deploy */
    connect(m_deployItem,
            SIGNAL(clicked()),
            this, SLOT(do_deployItem_changed()));
}

PreferenceMenu::~PreferenceMenu()
{
}

void PreferenceMenu::set_brightness(double value)
{
    m_mcu->set_brightness((char)value);
}

void PreferenceMenu::do_deployItem_changed()
{
    DplDevice::Device::instance()->deploy();
}

}
