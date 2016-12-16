/**
 * @file general_menu.cpp
 * @brief UT Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "general_menu.h"

static const MenuItem::Type types[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo
};

GeneralMenu::GeneralMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, types, parent)
{
    QStringList utUnitList;
    utUnitList.append(tr("Time"));
    utUnitList.append(tr("Sound Path"));
    utUnitList.append(tr("True Path"));

    m_menuItem[0]->set(tr("Gain"), "dB", 0, 90, 1);
    m_menuItem[1]->set(tr("Start"), "mm", 0, 1000, 2);
    m_menuItem[2]->set(tr("Range"), "mm", 0, 1000, 2);
    m_menuItem[3]->set(tr("Velocity"), "m/s", 635, 12540, 1);
    m_menuItem[4]->set(tr("Wedge Delay"), "μs", 0, 1000, 2);
    m_menuItem[5]->set(tr("UT Unit"), utUnitList);
}
