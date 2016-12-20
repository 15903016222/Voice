#ifndef __AREA_MENU_H__
#define __AREA_MENU_H__

#include "base_menu.h"
namespace DplScanMenu {

class AreaMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AreaMenu(Ui::BaseMenu *ui, QObject *parent);
    ~AreaMenu();

    void show();
    void hide();

private:
    MenuItem *m_scanStartItem;
    MenuItem *m_scanEndItem;
    MenuItem *m_scanResolutionItem;
    MenuItem *m_indexStartItem;
    MenuItem *m_indexEndItem;
    MenuItem *m_indexResolutionItem;
};

}
#endif // __AREA_MENU_H__
