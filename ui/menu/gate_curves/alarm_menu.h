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
#include "../menu_item/multi_combo_menu_item.h"
#include <fpga/alarm_output.h>

namespace DplGateCurvesMenu {

class AlarmMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AlarmMenu(QWidget *parent);

protected slots:
    void update(int index);

    void do_switchItem_changed(int index);
    void do_modeItem_changed(int index);

    void do_groupItem_triggered(int index, bool checked);
    void do_fstConditionItem_changed(int index);
    void do_operationItem_changed(int index);
    void do_sndConditionItem_changed(int index);

    void do_countItem(double val);
    void do_soundItem(int index);
    void do_delayItem(double val);
    void do_holdTimeItem(double val);

    void do_group_qty_changed(int qty);


protected:
    void update_switchItem();

    void update_groupItem();
    void update_fstConditionItem();
    void update_operatorItem();
    void update_sndConditionItem();

    void update_countItem();
    void update_soundItem();
    void update_delayItem();
    void update_holdTimeItem();

    void set_all_group();
    void set_none_group();
    void set_any_group();

    int get_group_qty(int groupflags);

private:
    ComboMenuItem *m_alarmItem;
    ComboMenuItem *m_switchItem;
    ComboMenuItem *m_modeItem;

    /* setting */
    MultiComboMenuItem *m_groupItem;
    ComboMenuItem *m_fstConditionItem;
    ComboMenuItem *m_operatorItem;
    ComboMenuItem *m_sndConditionItem;

    /* output */
    SpinMenuItem *m_countItem;
    ComboMenuItem *m_soundItem;
    SpinMenuItem *m_delayItem;
    SpinMenuItem *m_holdTimeItem;

    DplFpga::AlarmOutput *m_alarm;
};

}

#endif // ALARMMENU_H
