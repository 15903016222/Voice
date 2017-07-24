/**
 * @file position_menu.cpp
 * @brief Postion Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "position_menu.h"
#include "ui_base_menu.h"

namespace DplProbeMenu {

PositionMenu::PositionMenu(QWidget *parent) :
    BaseMenu(parent),
    m_scanOffsetItem(new SpinMenuItem(this, tr("Scan Offset"), "mm")),
    m_indexOffsetItem(new SpinMenuItem(this, tr("Index Offset"), "mm")),
    m_skewItem(new ComboMenuItem(this, tr("Skew")))
{
    ui->layout0->addWidget(m_scanOffsetItem);
    ui->layout1->addWidget(m_indexOffsetItem);
    ui->layout2->addWidget(m_skewItem);

    /* Scan Offset menu item */
    m_scanOffsetItem->set(-10000, 10000, 1);

    /* Index Offset menu item */
    m_indexOffsetItem->set(-10000, 10000, 1);

    /* Skew menu item */
    QStringList skews;
    skews.append("0\260");
    skews.append("90\260");
    skews.append("180\260");
    skews.append("270\260");
    m_skewItem->set(skews);
}

PositionMenu::~PositionMenu()
{
}

}
