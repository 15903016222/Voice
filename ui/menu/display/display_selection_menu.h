/**
 * @file selection_menu.h
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __DISPLAY_SELECTION_MENU_H__
#define __DISPLAY_SELECTION_MENU_H__

#include "base_menu.h"

namespace DplDisplayMenu {

class SelectionMenu : public BaseMenu
{
public:
    SelectionMenu(Ui::SubMenu *ui, QObject *parent);
};

}
#endif // __DISPLAY_SELECTION_MENU_H__
