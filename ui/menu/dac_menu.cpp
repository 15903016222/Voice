#include "dac_menu.h"

#include <QDebug>

DacMenu::DacMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_modes.append(tr("Settings"));
    m_modes.append(tr("Edit"));

    m_curveXs.append("1");
    m_curveXs.append("2");
    m_curveXs.append("3");
    m_curveXs.append("4");
    m_curveXs.append("5");

    m_points.append("1");

    m_settingFlag = true;
}

void DacMenu::show()
{
    mode_item();

    if (m_settingFlag) {
        show_setting();
    } else {
        show_edit();
    }
}

void DacMenu::hide()
{
    disconnect(ui->subMenu_1, SIGNAL(combo_event(int)), this, SLOT(do_mode_event(int)));
}

void DacMenu::mode_item()
{
    ui->subMenu_1->set_combo(tr("Mode"), m_modes);
    connect(ui->subMenu_1, SIGNAL(combo_event(int)), this, SLOT(do_mode_event(int)));
}

void DacMenu::show_setting()
{
    curve_no_item();
    curve_x_item();
    db_offset_item();
    ref_gain_item();
    switch_item();
}

void DacMenu::show_edit()
{
    point_item();
    position_item();
    add_point_item();
    delete_point_item();
    ui->subMenu_6->set_type(MenuItem::None);
}

void DacMenu::curve_no_item()
{
    ui->subMenu_2->set_spin(tr("Curve No."), "", 1, 5, 0);
}

void DacMenu::curve_x_item()
{
    ui->subMenu_3->set_combo(tr("Curve X"), m_curveXs);
}

void DacMenu::db_offset_item()
{
    ui->subMenu_4->set_spin(tr("dB Offset"), "dB", -40, 40, 1);
}

void DacMenu::ref_gain_item()
{
    ui->subMenu_5->set_spin(tr("Ref.Gain"), "dB", -40, 40, 1);
}

void DacMenu::switch_item()
{
    ui->subMenu_6->set_combo(tr("Switch"), s_onOff);
}

void DacMenu::point_item()
{
    ui->subMenu_2->set_combo(tr("Point"), m_points);
}

void DacMenu::position_item()
{
    ui->subMenu_3->set_spin(tr("Position"), "",  0, 10000, 2);
}

void DacMenu::add_point_item()
{
    ui->subMenu_4->set_label(tr("Add Point"));
}

void DacMenu::delete_point_item()
{
    ui->subMenu_5->set_label(tr("Delete Point"));
}

void DacMenu::do_mode_event(int pos)
{
    if (pos == 0) {
        m_settingFlag = true;
    } else {
        m_settingFlag = false;
    }
}
