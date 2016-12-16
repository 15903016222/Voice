#ifndef __ALARM_MENU_H__
#define __ALARM_MENU_H__

#include "base_menu.h"

class AlarmMenu : public BaseMenu
{
    Q_OBJECT
public:
    AlarmMenu(Ui::SubMenu *ui, QObject *parent);
};

#endif // ALARMMENU_H
