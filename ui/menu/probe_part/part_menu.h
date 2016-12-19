#ifndef __PART_MENU_H__
#define __PART_MENU_H__

#include "base_menu.h"

namespace DplProbeMenu {

class PartMenu : public BaseMenu
{
public:
    PartMenu(Ui::SubMenu *ui, QObject *parent);
};

}
#endif // PARTMENU_H
