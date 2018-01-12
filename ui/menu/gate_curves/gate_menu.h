/**
 * @file gate_menu.h
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __GATE_MENU_H__
#define __GATE_MENU_H__

#include "../base_menu.h"

#include <device/group.h>

namespace DplGateCurvesMenu {

class GateMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GateMenu(QWidget *parent);

protected:
    void update_items();
    void update_switchItem();
    void update_synchroItem();
    void update_measureModeItem();

    void changeEvent(QEvent *e);

protected slots:
    void do_gateItem_changed(int val);

    void do_startItem_changed(double val);

    void do_widthItem_changed(double val);

    void do_thresholdItem_changed(double val);

    void do_switchItem_changed(int index);

    void do_paramsItem_changed(int index);

    void do_sample_changed(void);

    void do_synchroItem_changed(int index);

    void do_measureModeItem_changed(int index);

    void update(const DplDevice::GroupPointer &group);

    void update_startItem();

    void update_thresholdItem();

    void update_widhtItem();

private:
    ComboMenuItem *m_gateItem;
    ComboMenuItem *m_switchItem;
    ComboMenuItem *m_paramsItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_widthItem;
    SpinMenuItem *m_thresholdItem;
    ComboMenuItem *m_synchroItem;
    ComboMenuItem *m_measureModeItem;
    ComboMenuItem *m_modeItem;

    DplDevice::GroupPointer m_group;
    DplGate::GatePointer m_gate;
};

}
#endif // GATEMENU_H
