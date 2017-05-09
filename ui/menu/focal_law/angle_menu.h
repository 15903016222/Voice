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
    SpinMenuItem m_minAngleItem;
    SpinMenuItem m_maxAngleItem;
    SpinMenuItem m_angleStepItem;
};

}

#endif // __ANGLE_MENU_H__
