#ifndef __SYSTEM_MENU_H__
#define __SYSTEM_MENU_H__

#include"base_menu.h"

namespace DplPreferenceMenu {

class SystemMenu : public BaseMenu
{
public:
    explicit SystemMenu(Ui::BaseMenu *ui, QObject *parent);
    ~SystemMenu();

    void show();
    void hide();

private:
    MenuItem *m_dateItem;
    MenuItem *m_timeItem;
    MenuItem *m_certItem;
    MenuItem *m_updateItem;
    MenuItem *m_resetCfgItem;
    MenuItem *m_infoItem;
};

}
#endif // __SYSTEM_MENU_H__
