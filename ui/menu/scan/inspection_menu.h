#ifndef __INSPECTION_MENU_H__
#define __INSPECTION_MENU_H__

#include "../base_menu.h"

namespace DplScanMenu {

class InspectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit InspectionMenu(QWidget *parent);
    ~InspectionMenu();

    void show();
    void hide();

private:
    ComboMenuItem *m_scanItem;
    ComboMenuItem *m_typeItem;
    SpinMenuItem *m_maxScanSpeedItem;
    SpinMenuItem *m_maxScanSpeedRPMItem;
};

}
#endif // __INSPECTION_MENU_H__
