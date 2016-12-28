/**
 * @file preference_menu.h
 * @brief Preference Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#ifndef __PREFERENCE_MENU_H__
#define __PREFERENCE_MENU_H__

#include "base_menu.h"

namespace DplPreferenceMenu {

class PreferenceMenu : public BaseMenu
{
public:
    explicit PreferenceMenu(Ui::BaseMenu *ui, QObject *parent);
    ~PreferenceMenu();

    void show();
    void hide();

private:
    SpinMenuItem *m_brightItem;
    SpinMenuItem *m_opacityItem;
    ComboMenuItem *m_languageItem;
    ComboMenuItem *m_startingPageItem;
    ComboMenuItem *m_gatemodeItem;
};

}
#endif // PREFERENCEMENU_H
