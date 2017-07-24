/**
 * @file alarm_menu.h
 * @brief alarm menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __ALARM_MENU_H__
#define __ALARM_MENU_H__

#include "../base_menu.h"

namespace DplGateCurvesMenu {

class AlarmMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AlarmMenu(QWidget *parent);
    ~AlarmMenu();

    void show();
    void hide();

private:
    ComboMenuItem *m_alarmItem;
    ComboMenuItem *m_switchItem;
    ComboMenuItem *m_groupItem;
    ComboMenuItem *m_conditionItem;
    ComboMenuItem *m_operatorItem;
};

}

#endif // ALARMMENU_H
