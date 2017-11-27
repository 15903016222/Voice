/**
 * @file output_menu.h
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __OUTPUT_MENU_H__
#define __OUTPUT_MENU_H__

#include "../base_menu.h"
#include <fpga/alarm_output.h>

namespace DplGateCurvesMenu {

class OutputMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit OutputMenu(QWidget *parent);

protected slots:
    void do_countItem(double val);
    void do_soundItem(int index);
    void do_delayItem(double val);
    void do_holdTimeItem(double val);
    void do_switchItem_changed(int index);

    void update(int index);

protected:
    void update_countItem();
    void update_soundItem();
    void update_delayItem();
    void update_holdTimeItem();
    void update_switchItem();

protected:

private:
    ComboMenuItem *m_outputItem;
    SpinMenuItem *m_countItem;
    ComboMenuItem *m_soundItem;
    SpinMenuItem *m_delayItem;
    SpinMenuItem *m_holdTimeItem;
    ComboMenuItem *m_switchItem;

    DplFpga::AlarmOutput *m_output;
};

}
#endif // __OUTPUT_MENU_H__
