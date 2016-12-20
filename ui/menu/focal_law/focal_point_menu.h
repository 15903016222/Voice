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
    MenuItem *m_typeItem;
    MenuItem *m_positionStartItem;
    MenuItem *m_positionEndItem;
    MenuItem *m_offsetStartItem;
    MenuItem *m_offsetEndItem;
};

}
#endif // __FOCAL_POINT_MENU_H__
