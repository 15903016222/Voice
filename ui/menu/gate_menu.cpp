#include "gate_menu.h"

GateMenu::GateMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    m_gates.append(tr("A"));
    m_gates.append(tr("B"));
    m_gates.append(tr("I"));
    m_gates.append(tr("Off"));

    m_synchros.append(tr("Gate A"));
    m_synchros.append(tr("Gate I"));
    m_synchros.append(tr("Pulse"));

    m_measureModes.append(tr("Edge"));
    m_measureModes.append(tr("Peak"));
}

void GateMenu::show()
{
    gate_item();
    start_item();
    width_item();
    threshold_item();
    synchro_item();
    measure_mode_item();
}

void GateMenu::hide()
{

}

void GateMenu::gate_item()
{
    ui->subMenu_1->set_combo(tr("Gate"), m_gates);
}

void GateMenu::start_item()
{
    ui->subMenu_2->set_spin(tr("Start"), "mm", 0, 16000, 2);
}

void GateMenu::width_item()
{
    ui->subMenu_3->set_spin(tr("Width"), "mm", 0.05, 525, 2);
}

void GateMenu::threshold_item()
{
    ui->subMenu_4->set_spin(tr("Threshold"), "%", 0, 100, 0);
}

void GateMenu::synchro_item()
{
    ui->subMenu_5->set_combo(tr("Synchro"), m_synchros);
}

void GateMenu::measure_mode_item()
{
    ui->subMenu_6->set_combo(tr("Measure Mode"), m_measureModes);
}
