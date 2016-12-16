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

class DisplaySelectionMenu : public BaseMenu
{
public:
    DisplaySelectionMenu(Ui::SubMenu *ui, QObject *parent);
};

#endif // __DISPLAY_SELECTION_MENU_H__
