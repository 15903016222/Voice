#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "base_menu.h"

namespace DplScanMenu {

class StartMenu : public BaseMenu
{
public:
    StartMenu(Ui::BaseMenu *ui, QObject *parent);
};

}
#endif // __START_MENU_H__
