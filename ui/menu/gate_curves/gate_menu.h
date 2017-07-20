/**
 * @file gate_menu.h
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __GATE_MENU_H__
#define __GATE_MENU_H__

#include "base_menu.h"

#include <device/group.h>

namespace DplGateCurvesMenu {

class GateMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GateMenu(Ui::BaseMenu *ui, QObject *parent);
    ~GateMenu();

    void show();
    void hide();

protected:
    void update_gate(const DplDevice::GatePointer &gate);
    void update_startItem(const DplDevice::GatePointer &gate);

protected slots:
    void do_gateItem_changed(int val);

    void do_startItem_changed(double val);

    void do_switchItem_changed(int index);

    void do_paramsItem_changed(int index);

    void update(const DplDevice::GroupPointer &group);


private:
    ComboMenuItem *m_gateItem;
    ComboMenuItem *m_switchItem;
    ComboMenuItem *m_paramsItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_widthItem;
    SpinMenuItem *m_thresholdItem;
    ComboMenuItem *m_synchroItem;
    ComboMenuItem *m_measureModeItem;

    DplDevice::GroupPointer m_group;
};

}
#endif // GATEMENU_H
