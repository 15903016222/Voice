#ifndef __ANGLE_MENU_H__
#define __ANGLE_MENU_H__

#include "base_menu.h"

namespace DplFocalLawMenu {

class AngleMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AngleMenu(Ui::BaseMenu *ui, QObject *parent);
    ~AngleMenu();

    void show();
    void hide();

private:
    MenuItem *m_minAngleItem;
    MenuItem *m_maxAngleItem;
    MenuItem *m_angleStepItem;
};

}

#endif // __ANGLE_MENU_H__
