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
#include "device.h"

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

signals:
    void gain_changed(double gain);

private:
    SpinMenuItem *m_gainItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_rangeItem;
    SpinMenuItem *m_velocityItem;
    SpinMenuItem *m_wedgeDelayItem;
    ComboMenuItem *m_utUnitItem;
    DplDevice::GroupPointer m_group;

private slots:
    void do_gainItem_changed(double gain);
    void do_startItem_changed(double pos);
    void do_rangeItem_changed(double value);
    void do_velocityItem_changed(double value);

    void do_current_group_changed();
};

}
#endif // GENERALMENU_H
