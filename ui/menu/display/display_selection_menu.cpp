/**
 * @file selection_menu.cpp
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "display_selection_menu.h"

namespace DplDisplayMenu {

static const MenuItem::Type s_type[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo
};

SelectionMenu::SelectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_type, parent)
{
    QStringList groupList;
    QStringList displayList;
    QStringList cScanSourceList;

    groupList.append(tr("All"));
    groupList.append(tr("Current"));

    displayList.append(tr("A A-Scan"));
    displayList.append(tr("B B-Scan"));
    displayList.append(tr("C C-Scan"));
    displayList.append(tr("S S-Scan"));
    displayList.append(tr("A-B A-Scan B-Scan"));
    displayList.append(tr("A-S A-Scan S-Scan"));
    displayList.append(tr("A-B-C A-Scan B-Scan C-Scan"));
    displayList.append(tr("A-B-S A-Scan B-Scan S-Scan"));
    displayList.append(tr("A-S-[C] A-Scan S-Scan [C-Scan]"));
    displayList.append(tr("S-A-A-A S-Scan A-Scan A-Scan A-Scan"));
    displayList.append(tr("S-A-C-C S-Scan A-Scan C-Scan C-Scan"));

    cScanSourceList.append(tr("A%"));
    cScanSourceList.append(tr("B%"));
    cScanSourceList.append(tr("Thickness"));
    cScanSourceList.append(tr("I/"));

    /* Group menu item */
    m_menuItem[0]->set(tr("Group"), groupList);

    /* Display menu item */
    m_menuItem[1]->set(tr("Display"), displayList);

    /* C-Scan Source menu item */
    m_menuItem[2]->set(tr("C-Scan<br>Source"), cScanSourceList);

    /* Min.Thickness menu item */
    m_menuItem[3]->set(tr("Min.Thickness"), "mm", 0.05, 20000, 2);

    /* Max.Thickness menu item */
    m_menuItem[4]->set(tr("Max.Thickness"), "mm", 0.06, 20000, 2);

    /* Data compression */
    m_menuItem[5]->set(tr("Data<br>Compression"), s_onOff);
}

}
