/**
 * @file position_menu.cpp
 * @brief Postion Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "position_menu.h"

namespace DplProbeMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo
};

PositionMenu::PositionMenu(Ui::SubMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{

            /* Scan Offset menu item */
            m_menuItem[0]->set(tr("Scan Offset"), "mm", -10000, 10000, 1);

            /* Index Offset menu item */
            m_menuItem[1]->set(tr("Index Offset"), "mm", -10000, 10000, 1);

            /* Skew menu item */
            QStringList skews;
            skews.append("0°");
            skews.append("90°");
            skews.append("180°");
            skews.append("270°");
            m_menuItem[2]->set(tr("Skew"), skews);
}

}
