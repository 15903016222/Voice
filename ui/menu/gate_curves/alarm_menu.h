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
    explicit AlarmMenu(Ui::BaseMenu *ui, QObject *parent);
    ~AlarmMenu();

    void show();
    void hide();

private:
    MenuItem *m_alarmItem;
    MenuItem *m_switchItem;
    MenuItem *m_groupItem;
    MenuItem *m_conditionItem;
    MenuItem *m_operatorItem;
};

#endif // ALARMMENU_H
