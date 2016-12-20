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
    MenuItem *m_unitItem;
    MenuItem *m_brightItem;
    MenuItem *m_opacityItem;
    MenuItem *m_languageItem;
    MenuItem *m_startingPageItem;
    MenuItem *m_gatemodeItem;
};

}
#endif // PREFERENCEMENU_H
