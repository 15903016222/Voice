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

#include <device/device.h>

namespace DplUtSettingMenu {

class GeneralMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GeneralMenu(Ui::BaseMenu *ui, QObject *parent = 0);
    ~GeneralMenu();

    void show();
    void hide();

public slots:
    void set_gain(double gain) { m_gainItem->set_value(gain); }

    /**
     * @brief update    更新菜单数据
     */
    void update();

signals:
    void gain_changed(double gain);
    void ut_unit_changed();

private:
    bool m_updateFlag;

    SpinMenuItem *m_gainItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_rangeItem;
    SpinMenuItem *m_velocityItem;
    SpinMenuItem *m_wedgeDelayItem;
    ComboMenuItem *m_utUnitItem;
    DplDevice::GroupPointer m_group;

private slots:
    void do_gainItem_changed(double gain);
    void do_startItem_changed(double value);
    void do_rangeItem_changed(double value);
    void do_velocityItem_changed(double value);
    void do_wedgeDelayItem_changed(double value);
    void do_utUnitItem_changed(int index);

    void do_current_group_changed();

    void update_gain_item();
    void update_start_item();
    void update_range_item();

};

}
#endif // GENERALMENU_H
