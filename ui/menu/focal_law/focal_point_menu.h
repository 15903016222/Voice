#ifndef __FOCAL_POINT_MENU_H__
#define __FOCAL_POINT_MENU_H__

#include "base_menu.h"

namespace DplFocalLawMenu {

class FocalPointMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FocalPointMenu(Ui::BaseMenu *ui, QObject *parent);
    ~FocalPointMenu();

    void show();
    void hide();

private:
    ComboMenuItem m_typeItem;
    SpinMenuItem m_positionStartItem;
    SpinMenuItem m_positionEndItem;
    SpinMenuItem m_offsetStartItem;
    SpinMenuItem m_offsetEndItem;
};

}
#endif // __FOCAL_POINT_MENU_H__
