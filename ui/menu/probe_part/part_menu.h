#ifndef __PART_MENU_H__
#define __PART_MENU_H__

#include "base_menu.h"

namespace DplProbeMenu {

class PartMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PartMenu(Ui::BaseMenu *ui, QObject *parent);
    ~PartMenu();

    void show();
    void hide();

private:
    MenuItem *m_geometryItem;
    MenuItem *m_thicknessItem;
    MenuItem *m_diameterItem;
    MenuItem *m_materialItem;
    MenuItem *m_overlayItem;
};

}
#endif // PARTMENU_H
