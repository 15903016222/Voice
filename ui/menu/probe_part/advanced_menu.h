#ifndef __ADVANCED_MENU_H__
#define __ADVANCED_MENU_H__

#include "base_menu.h"

namespace DplProbeMenu {

class AdvancedMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AdvancedMenu(Ui::BaseMenu *ui, QObject *parent);
    ~AdvancedMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_loadPartItem;
    LabelMenuItem *m_clearPartItem;
};

}

#endif // ADVANCEDMENU_H
