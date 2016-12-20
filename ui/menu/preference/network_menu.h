#ifndef __NETWORK_MENU_H__
#define __NETWORK_MENU_H__

#include "base_menu.h"

namespace DplPreferenceMenu {

class NetworkMenu : public BaseMenu
{
public:
    explicit NetworkMenu(Ui::BaseMenu *ui, QObject *parent);
    ~NetworkMenu();

    void show();
    void hide();

private:
    MenuItem *m_ipItem;
    MenuItem *m_maskItem;
};

}
#endif // __NETWORK_MENU_H__
