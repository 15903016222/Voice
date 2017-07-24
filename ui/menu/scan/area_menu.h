#ifndef __AREA_MENU_H__
#define __AREA_MENU_H__

#include "../base_menu.h"
namespace DplScanMenu {

class AreaMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AreaMenu(QWidget *parent);
    ~AreaMenu();

private:
    SpinMenuItem *m_scanStartItem;
    SpinMenuItem *m_scanEndItem;
    SpinMenuItem *m_scanResolutionItem;
    SpinMenuItem *m_indexStartItem;
    SpinMenuItem *m_indexEndItem;
    SpinMenuItem *m_indexResolutionItem;
};

}
#endif // __AREA_MENU_H__
