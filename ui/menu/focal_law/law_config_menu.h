#ifndef __LAW_MENU_H__
#define __LAW_MENU_H__

#include "base_menu.h"

namespace DplFocalLawMenu {

class LawConfigMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit LawConfigMenu(Ui::BaseMenu *ui, QObject *parent);
    ~LawConfigMenu();

    void show();
    void hide();

private:
    MenuItem *m_lawTypeItem;
    MenuItem *m_pulseConnectionItem;
    MenuItem *m_receiverConnectionItem;
    MenuItem *m_waveTypeItem;
};

}

#endif // __LAW_MENU_H__
