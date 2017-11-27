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
#include <fpga/alarm_output.h>

namespace DplGateCurvesMenu {

class AlarmMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AlarmMenu(QWidget *parent);

protected slots:
    void update(int index);
    void do_groupItem_changed(int index);
    void do_fstConditionItem_changed(int index);
    void do_operationItem_changed(int index);
    void do_sndConditionItem_changed(int index);

protected:
    void update_groupItem();
    void update_fstConditionItem();
    void update_operatorItem();
    void update_sndConditionItem();

private:
    ComboMenuItem *m_alarmItem;
    ComboMenuItem *m_groupItem;
    ComboMenuItem *m_fstConditionItem;
    ComboMenuItem *m_operatorItem;
    ComboMenuItem *m_sndConditionItem;

    DplFpga::AlarmOutput *m_alarm;
};

}

#endif // ALARMMENU_H
