#ifndef __GATE_MENU_H__
#define __GATE_MENU_H__

#include "base_menu.h"

class GateMenu : public BaseMenu
{
    Q_OBJECT
public:
    GateMenu(Ui::SubMenu *ui, QObject *parent);
};

#endif // GATEMENU_H
