/**
 * @file general_menu.h
 * @brief Ut Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __GENERAL_MENU_H__
#define __GENERAL_MENU_H__

#include "base_menu.h"

class GeneralMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GeneralMenu(Ui::SubMenu *ui, QObject *parent = 0);
};

#endif // GENERALMENU_H
