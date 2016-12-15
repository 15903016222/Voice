#include "output_menu.h"

OutputMenu::OutputMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_outputs.append(tr("Alarm 1"));
    m_outputs.append(tr("Alarm 2"));
    m_outputs.append(tr("Alarm 3"));
    m_outputs.append(tr("Analog 1"));
    m_outputs.append(tr("Analog 2"));

    m_sounds.append(tr("Off No Sound"));
    m_sounds.append(tr("300Hz Audio Output at 300Hz"));
    m_sounds.append(tr("600Hz Audio Output at 600Hz"));
    m_sounds.append(tr("1000Hz Audio Output at 1000Hz"));
    m_sounds.append(tr("5000Hz Audio Output at 5000Hz"));

    m_datas.append(tr("A%"));
    m_datas.append(tr("B%"));
    m_datas.append(tr("None"));

}

void OutputMenu::show()
{
    output_item();
    sound_item();
    delay_item();
    hold_time_item();
    group_item();
    data_item();
}

void OutputMenu::hide()
{

}

void OutputMenu::output_item()
{
    ui->subMenu_1->set_combo(tr("Output"), m_outputs);
}

void OutputMenu::sound_item()
{
    ui->subMenu_2->set_combo(tr("Sound"), m_sounds);
}

void OutputMenu::delay_item()
{
    ui->subMenu_3->set_spin(tr("Delay"), "mm", 0, 5000, 2);
}

void OutputMenu::hold_time_item()
{
    ui->subMenu_4->set_spin(tr("Hold Time"), "%", 0, 5000, 2);
}

void OutputMenu::group_item()
{
    ui->subMenu_5->set_label(tr("Group"));
}

void OutputMenu::data_item()
{
    ui->subMenu_6->set_combo(tr("Data"), m_datas);
}
