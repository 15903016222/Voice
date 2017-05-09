/**
 * @file position_menu.cpp
 * @brief Postion Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "position_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplProbeMenu {

PositionMenu::PositionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Scan Offset menu item */
    m_scanOffsetItem.set(tr("Scan Offset"), "mm", -10000, 10000, 1);

    /* Index Offset menu item */
    m_indexOffsetItem.set(tr("Index Offset"), "mm", -10000, 10000, 1);

    /* Skew menu item */
    QStringList skews;
    skews.append("0\260");
    skews.append("90\260");
    skews.append("180\260");
    skews.append("270\260");
    m_skewItem.set(tr("Skew"), skews);
}

PositionMenu::~PositionMenu()
{
}

void PositionMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_scanOffsetItem);
    ui->menuItem1->layout()->addWidget(&m_indexOffsetItem);
    ui->menuItem2->layout()->addWidget(&m_skewItem);
    m_scanOffsetItem.show();
    m_indexOffsetItem.show();
    m_skewItem.show();
}

void PositionMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_scanOffsetItem);
    ui->menuItem1->layout()->removeWidget(&m_indexOffsetItem);
    ui->menuItem2->layout()->removeWidget(&m_skewItem);
    m_scanOffsetItem.hide();
    m_indexOffsetItem.hide();
    m_skewItem.hide();
}

}
