/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"

UtAdvancedMenu::UtAdvancedMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_pointQtyList.append(tr("Auto"));
    m_pointQtyList.append(tr("160"));
    m_pointQtyList.append(tr("320"));
    m_pointQtyList.append(tr("640"));
    m_pointQtyList.append(tr("UserDef"));
}

void UtAdvancedMenu::show()
{
    eight_percent_item();
    db_ref_item();
    point_number_item();
    scale_factor_item();
    sum_gain_item();

    ui->subMenu_6->set_type(MenuItem::None);
}

void UtAdvancedMenu::hide()
{

}

void UtAdvancedMenu::eight_percent_item()
{
    ui->subMenu_1->set_label(tr("Set 80%"));
}

void UtAdvancedMenu::db_ref_item()
{
    ui->subMenu_2->set_combo(tr("dB Ref."), s_onOff);
}

void UtAdvancedMenu::point_number_item()
{
    ui->subMenu_3->set_combo(tr("Point Qty."), m_pointQtyList);
}

void UtAdvancedMenu::scale_factor_item()
{
    ui->subMenu_4->set_label(tr("Scale Factor"));
}

void UtAdvancedMenu::sum_gain_item()
{
    ui->subMenu_5->set_spin(tr("Sum Gain"), "dB", 0, 100, 1);
}

