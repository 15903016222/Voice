/**
 * @file receiver_menu.h
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __RECEIVER_MENU_H__
#define __RECEIVER_MENU_H__

#include "base_menu.h"

class ReceiverMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReceiverMenu(Ui::SubMenu *ui, QObject *parent = 0);
};

#endif // __RECEIVER_MENU_H__
