#ifndef __RECEIVER_MENU_H__
#define __RECEIVER_MENU_H__

#include "base_menu.h"

class ReceiverMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReceiverMenu(Ui::SubMenu *ui, QObject *parent = 0);
};

#endif // __RECEIVER_MENU_H__
