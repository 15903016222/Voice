/**
 * @file pulser_menu.h
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __PULSER_MENU_H__
#define __PULSER_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

namespace DplUtSettingMenu {

class PulserMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PulserMenu(QWidget *parent);
    ~PulserMenu();

protected:
    void update_voltage_item();

protected slots:
    void do_txrxModeItem_changed(int index);
    void do_pulserItem_changed(double val);
    void do_voltageItem_changed(int index);
    void do_pwItem_changed(double val);
    void do_prfItem_changed(int index);
    void do_userDevItem_changed(double val);

    void update(const DplDevice::GroupPointer &group);
    void update_user_def_item();

private:
    ComboMenuItem *m_txrxModeItem;
    SpinMenuItem *m_pulserItem;
    ComboMenuItem *m_voltageItem;
    SpinMenuItem *m_pwItem;
    ComboMenuItem *m_prfItem;
    SpinMenuItem *m_userDefItem;

    DplDevice::GroupPointer m_group;
};

}
#endif // __PULSER_MENU_H__
