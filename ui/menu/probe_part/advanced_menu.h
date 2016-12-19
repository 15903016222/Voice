#ifndef __ADVANCED_MENU_H__
#define __ADVANCED_MENU_H__

#include "base_menu.h"

namespace DplProbeMenu {

class AdvancedMenu : public BaseMenu
{
public:
    AdvancedMenu(Ui::SubMenu *ui, QObject *parent);
};

}

#endif // ADVANCEDMENU_H
