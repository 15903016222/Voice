/**
 * @file alarm_menu.h
 * @brief alarm menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __ALARM_MENU_H__
#define __ALARM_MENU_H__

#include "base_menu.h"

class AlarmMenu : public BaseMenu
{
    Q_OBJECT
public:
    AlarmMenu(Ui::BaseMenu *ui, QObject *parent);
};

#endif // ALARMMENU_H
