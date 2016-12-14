#include "pulser_menu.h"

PulserMenu::PulserMenu(Ui::SubMenu *ui, QObject *parent)
    :BaseMenu(ui, parent)
{
    m_txRxMode.append(tr("PC"));
    m_txRxMode.append(tr("PE"));
    m_txRxMode.append(tr("TT"));
    m_txRxMode.append(tr("TOFD"));

    m_voltages.append("50V");
    m_voltages.append("100V");
    m_voltages.append("200V");

    m_prfs.append(tr("Auto Max"));
    m_prfs.append(tr("Max/2"));
    m_prfs.append(tr("Optimum"));
    m_prfs.append(tr("UserDef"));
}

void PulserMenu::show()
{
    txrx_item();
    pulser_item();
    voltage_item();
}

void PulserMenu::hide()
{

}

void PulserMenu::txrx_item()
{
    ui->subMenu_1->set_combo(tr("Tx/Rx Mode"), m_txRxMode);
}

void PulserMenu::pulser_item()
{
    ui->subMenu_2->set_spin(tr("Pulser"), "", s_steps1, 1, 113, 0);
}

void PulserMenu::voltage_item()
{
    ui->subMenu_3->set_combo(tr("Voltage"), m_voltages);
}

void PulserMenu::pw_item()
{
    ui->subMenu_4->set_spin(tr("PW"), "ns", s_steps1, 30, 500, 1);
}

void PulserMenu::prf_item()
{
    ui->subMenu_5->set_combo(tr("PRF"), m_prfs);
}
