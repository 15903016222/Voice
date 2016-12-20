#ifndef __INSPECTION_MENU_H__
#define __INSPECTION_MENU_H__

#include "base_menu.h"

namespace DplScanMenu {

class InspectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit InspectionMenu(Ui::BaseMenu *ui, QObject *parent);
    ~InspectionMenu();

    void show();
    void hide();

private:
    MenuItem *m_scanItem;
    MenuItem *m_typeItem;
    MenuItem *m_maxScanSpeedItem;
    MenuItem *m_maxScanSpeedRPMItem;
};

}
#endif // __INSPECTION_MENU_H__
