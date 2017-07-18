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

protected slots:
    void do_startItem_changed(double val);

    void do_current_group_changed(const DplDevice::GroupPointer &group);

private:
    ComboMenuItem *m_gateItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_widthItem;
    SpinMenuItem *m_thresholdItem;
    ComboMenuItem *m_synchroItem;
    ComboMenuItem *m_measureModeItem;

    DplDevice::GroupPointer m_group;
};

}
#endif // GATEMENU_H
