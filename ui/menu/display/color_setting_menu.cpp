/**
 * @file color_setting_menu.cpp
 * @brief Color Setting menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "color_setting_menu.h"

namespace DplDisplayMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Label,
};

ColorSettingMenu::ColorSettingMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Amplitude menu item */
    m_menuItem[0]->set(tr("Amplitude"), "");

    /* Depth menu item */
    m_menuItem[1]->set(tr("Depth"), "");

    /* TOFD menu item */
    m_menuItem[2]->set(tr("TOFD"), "");
}

}
