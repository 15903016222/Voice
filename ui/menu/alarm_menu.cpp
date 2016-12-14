#include "alarm_menu.h"

AlarmMenu::AlarmMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_alarms.append(tr("Alarm 1"));
    m_alarms.append(tr("Alarm 2"));
    m_alarms.append(tr("Alarm 3"));

    m_groups.append(tr("Group1"));
    m_groups.append(tr("All"));
    m_groups.append(tr("None"));

    m_conditions.append(tr("None"));
    m_conditions.append(tr("Gate A"));
    m_conditions.append(tr("Gate B"));
    m_conditions.append(tr("Gate I"));
    m_conditions.append(tr("Not Gate A"));
    m_conditions.append(tr("Not Gate B"));
    m_conditions.append(tr("Not Gate I"));
    m_conditions.append(tr(">Max.Thickness"));
    m_conditions.append(tr("<Min.Thickness"));

    m_operators.append(tr("And"));
    m_operators.append(tr("Or"));

}

void AlarmMenu::show()
{
    alarm_item();
    switch_item();
    group_item();
    condition_factor_item();
    operator_item();

    ui->subMenu_6->set_type(MenuItem::None);
}

void AlarmMenu::hide()
{

}

void AlarmMenu::alarm_item()
{
    ui->subMenu_1->set_combo(tr("Alarm"), m_alarms);
}

void AlarmMenu::switch_item()
{
    ui->subMenu_2->set_combo(tr("Switch"), s_onOff);
}

void AlarmMenu::group_item()
{
    ui->subMenu_3->set_combo(tr("Group"), m_groups);
}

void AlarmMenu::condition_factor_item()
{
    ui->subMenu_4->set_combo(tr("Condition"), m_conditions);
}

void AlarmMenu::operator_item()
{
    ui->subMenu_5->set_combo(tr("Operator"), m_operators);
}
