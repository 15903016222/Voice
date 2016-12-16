/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"

static const MenuItem::Type s_typs[MAX_ITEMS] = {
    MenuItem::Label,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Label,
    MenuItem::Spin,
    MenuItem::Label
};

UtAdvancedMenu::UtAdvancedMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, s_typs, parent)
{
    QStringList pointQtyList;

    pointQtyList.append(tr("Auto"));
    pointQtyList.append(tr("160"));
    pointQtyList.append(tr("320"));
    pointQtyList.append(tr("640"));
    pointQtyList.append(tr("UserDef"));

    m_menuItem[0]->set(tr("Set 80%"), "");
    m_menuItem[1]->set(tr("dB Ref."), s_onOff);
    m_menuItem[2]->set(tr("Point Qty."), pointQtyList);
    m_menuItem[3]->set(tr("Scale Factor"), "");
    m_menuItem[4]->set(tr("Sum Gain"), "dB", 0, 100, 1);
}
