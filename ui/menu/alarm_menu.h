#ifndef __ALARM_MENU_H__
#define __ALARM_MENU_H__

#include "base_menu.h"

class AlarmMenu : public BaseMenu
{
    Q_OBJECT
public:
    AlarmMenu(Ui::SubMenu *ui, QObject *parent);
    void show();
    void hide();

private:
    QStringList m_alarms;
    QStringList m_groups;
    QStringList m_conditions;
    QStringList m_operators;

    void alarm_item();
    void switch_item();
    void group_item();
    void condition_factor_item();
    void operator_item();
};

#endif // ALARMMENU_H
