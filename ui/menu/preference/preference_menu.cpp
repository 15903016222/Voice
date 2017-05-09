/**
 * @file preference_menu.cpp
 * @brief Preference Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "preference_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplPreferenceMenu {

PreferenceMenu::PreferenceMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    m_mcu = Mcu::get_mcu();

    /* Bright menu item */
    m_brightItem.set(tr("Bright"), "%", 1, 100, 0);
    connect(&m_brightItem, SIGNAL(value_changed(double)), this, SLOT(set_brightness(double)));
    m_brightItem.set_value(100);

    /* Opacity menu item */
    m_opacityItem.set(tr("Opacity"), "%", 20, 100, 0);
    m_opacityItem.set_value(80);
    connect(&m_opacityItem, SIGNAL(value_changed(double)), this, SIGNAL(opacity_changed(double)));

    /* Language menu item */
    QStringList languageList;
    languageList.append("English");
    languageList.append("Chinese");
    m_languageItem.set(tr("Language"), languageList);

    /* Starting Page Menu Item */
    m_startingPageItem.set(tr("Starting Page"), s_onOff);

    /* Gate Mode */
    m_gatemodeItem.set(tr("Gate Mode"), s_onOff);
}

PreferenceMenu::~PreferenceMenu()
{
}

void PreferenceMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_brightItem);
    ui->menuItem1->layout()->addWidget(&m_opacityItem);
    ui->menuItem2->layout()->addWidget(&m_languageItem);
    ui->menuItem3->layout()->addWidget(&m_startingPageItem);
    ui->menuItem4->layout()->addWidget(&m_gatemodeItem);
    m_brightItem.show();
    m_opacityItem.show();
    m_languageItem.show();
    m_startingPageItem.show();
    m_gatemodeItem.show();
}

void PreferenceMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_brightItem);
    ui->menuItem1->layout()->removeWidget(&m_opacityItem);
    ui->menuItem2->layout()->removeWidget(&m_languageItem);
    ui->menuItem3->layout()->removeWidget(&m_startingPageItem);
    ui->menuItem4->layout()->removeWidget(&m_gatemodeItem);
    m_brightItem.hide();
    m_opacityItem.hide();
    m_languageItem.hide();
    m_startingPageItem.hide();
    m_gatemodeItem.hide();
}

void PreferenceMenu::set_brightness(double value)
{
    m_mcu->set_brightness((char)value);
}

}
