/**
 * @file analog_menu.h
 * @brief Gate/Curves analog menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __ANALOG_MENU_H__
#define __ANALOG_MENU_H__

#include "../base_menu.h"
#include <fpga/alarm_analog.h>

namespace DplGateCurvesMenu {

class AnalogMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AnalogMenu(QWidget *parent);

protected slots:
    void do_switchItem_changed(int index);
    void do_groupItem_changed(int index);
    void do_dataItem_changed(int index);

    void update(int index);

protected:
    void update_switchItem();
    void update_groupItem();
    void update_dataItem();

    void changeEvent(QEvent *e);

private:
    ComboMenuItem *m_analogItem;
    ComboMenuItem *m_switchItem;
    ComboMenuItem *m_groupItem;
    ComboMenuItem *m_dataItem;

    DplFpga::AlarmAnalog *m_analog;
};

}
#endif // __ANALOG_MENU_H__
