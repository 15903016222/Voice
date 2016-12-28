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
    ComboMenuItem *m_lawTypeItem;
    SpinMenuItem *m_pulseConnectionItem;
    SpinMenuItem *m_receiverConnectionItem;
    ComboMenuItem *m_waveTypeItem;
};

}

#endif // __LAW_MENU_H__
