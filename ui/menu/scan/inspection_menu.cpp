#include "inspection_menu.h"

namespace DplScanMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin
};

InspectionMenu::InspectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Scan Menu Item */
    QStringList scanList;
    scanList.append(tr("Time"));
    scanList.append(tr("Encoder 1"));
    scanList.append(tr("Encoder 2"));
    m_menuItem[0]->set(tr("Scan"), scanList);

    /* Type menu item */
    QStringList typeList;
    typeList.append(tr("One Line"));
    typeList.append(tr("Raster Scan"));
    typeList.append(tr("Helicoidal Scan"));
    m_menuItem[1]->set(tr("Type"), typeList);

    /* Max Scan Speed menu item */
    m_menuItem[2]->set(tr("Max Scan Speed"), "m/s", 0, 1000, 2);

    /* Max Scan Speed(rpm) Menu Item */
    m_menuItem[3]->set(tr("Max Scan Speed(rpm)"), "m/s", 0, 1000, 0);
}

}
