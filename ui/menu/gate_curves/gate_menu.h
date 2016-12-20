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

class GateMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GateMenu(Ui::BaseMenu *ui, QObject *parent);
    ~GateMenu();

    void show();
    void hide();

private:
    MenuItem *m_gateItem;
    MenuItem *m_startItem;
    MenuItem *m_widthItem;
    MenuItem *m_thresholdItem;
    MenuItem *m_synchroItem;
    MenuItem *m_measureModeItem;
};

#endif // GATEMENU_H
