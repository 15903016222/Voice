/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"
#include "label_menu_item.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

namespace DplUtSettingMenu {

UtAdvancedMenu::UtAdvancedMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    QStringList pointQtyList;

    pointQtyList.append(tr("Auto"));
    pointQtyList.append(tr("160"));
    pointQtyList.append(tr("320"));
    pointQtyList.append(tr("640"));
    pointQtyList.append(tr("UserDef"));

    m_eightPercentItem = new LabelMenuItem;
    m_eightPercentItem->set(tr("Set 80%"), "");

    m_dbRefItem = new ComboMenuItem;
    m_dbRefItem->set(tr("dB Ref."), s_onOff);

    m_pointQtyItem = new ComboMenuItem;
    m_pointQtyItem->set(tr("Point Qty."), pointQtyList);

    m_scaleFactorItem = new LabelMenuItem;
    m_scaleFactorItem->set(tr("Scale Factor"), "");

    m_sumGainItem = new SpinMenuItem;
    m_sumGainItem->set(tr("Sum Gain"), "dB", 0, 100, 1);
}

UtAdvancedMenu::~UtAdvancedMenu()
{
    delete m_eightPercentItem;
    delete m_dbRefItem;
    delete m_pointQtyItem;
    delete m_scaleFactorItem;
    delete m_sumGainItem;
}

void UtAdvancedMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_eightPercentItem);
    ui->menuItem1->layout()->addWidget(m_dbRefItem);
    ui->menuItem2->layout()->addWidget(m_pointQtyItem);
    ui->menuItem3->layout()->addWidget(m_scaleFactorItem);
    ui->menuItem4->layout()->addWidget(m_sumGainItem);
    m_eightPercentItem->show();
    m_dbRefItem->show();
    m_pointQtyItem->show();
    m_scaleFactorItem->show();
    m_sumGainItem->show();
}

void UtAdvancedMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_eightPercentItem);
    ui->menuItem1->layout()->removeWidget(m_dbRefItem);
    ui->menuItem2->layout()->removeWidget(m_pointQtyItem);
    ui->menuItem3->layout()->removeWidget(m_scaleFactorItem);
    ui->menuItem4->layout()->removeWidget(m_sumGainItem);
    m_eightPercentItem->hide();
    m_dbRefItem->hide();
    m_pointQtyItem->hide();
    m_scaleFactorItem->hide();
    m_sumGainItem->hide();
}

}
