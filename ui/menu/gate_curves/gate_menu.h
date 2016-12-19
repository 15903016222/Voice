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
    GateMenu(Ui::BaseMenu *ui, QObject *parent);
};

#endif // GATEMENU_H
