#include "general_menu.h"
#include "ui_sub_menu.h"

GeneralMenu::GeneralMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(parent)
{
    this->ui = ui;

    m_utUnit.append(tr("Time"));
    m_utUnit.append(tr("Sound Path"));
    m_utUnit.append(tr("True Path"));
}

void GeneralMenu::show()
{
    gain_item();
    start_item();
    range_item();
    velocity_item();
    wedge_item();
    ut_unit_item();
}

void GeneralMenu::hide()
{
    ui->subMenu_1->clean();
    ui->subMenu_2->clean();
    ui->subMenu_3->clean();
    ui->subMenu_4->clean();
    ui->subMenu_5->clean();
    ui->subMenu_6->clean();
}

void GeneralMenu::gain_item()
{
    ui->subMenu_1->set_spin(tr("Gain"), "dB", s_steps1, 0, 100, 1);
}

void GeneralMenu::start_item()
{
    ui->subMenu_2->set_spin(tr("Start"), "mm", s_steps2, 0, 1000, 2);
}

void GeneralMenu::range_item()
{
    ui->subMenu_3->set_spin(tr("Range"), "mm", s_steps2, 0, 1000, 2);
}

void GeneralMenu::velocity_item()
{
    ui->subMenu_4->set_spin(tr("Velocity"), "m/s", s_steps2, 635, 12540, 1);
}

void GeneralMenu::wedge_item()
{
    ui->subMenu_5->set_spin(tr("Wedge Delay"), "μs", s_steps2, 0, 1000, 2);
}

void GeneralMenu::ut_unit_item()
{
    ui->subMenu_6->set_combo(tr("UT Unit"), m_utUnit);
}

