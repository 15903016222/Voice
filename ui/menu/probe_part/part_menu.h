#ifndef __PART_MENU_H__
#define __PART_MENU_H__

#include "../base_menu.h"

namespace DplProbeMenu {

class PartMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PartMenu(QWidget *parent);
    ~PartMenu();

    void show();
    void hide();

private:
    ComboMenuItem *m_geometryItem;
    SpinMenuItem *m_thicknessItem;
    SpinMenuItem *m_diameterItem;
    ComboMenuItem *m_materialItem;
    ComboMenuItem *m_overlayItem;
};

}
#endif // PARTMENU_H
