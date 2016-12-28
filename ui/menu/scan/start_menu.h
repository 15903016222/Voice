#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "base_menu.h"

namespace DplScanMenu {

class StartMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit StartMenu(Ui::BaseMenu *ui, QObject *parent);
    ~StartMenu();

    void show();
    void hide();

private:
    SpinMenuItem *m_scanItem;
    ComboMenuItem *m_pauseItem;
};

}
#endif // __START_MENU_H__
