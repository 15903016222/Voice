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
#include "fpga.h"

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
    MenuItem *m_startItem;
    MenuItem *m_rangeItem;
    MenuItem *m_velocityItem;
    MenuItem *m_wedgeDelayItem;
    MenuItem *m_utUnitItem;
    DplFpga::Fpga *m_fpga;

private slots:
    void do_gainItem_changed(double gain);
    void do_startItem_changed(double pos);
    void do_rangeItem_changed(double value);
};

}
#endif // GENERALMENU_H
