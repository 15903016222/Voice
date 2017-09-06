#include "pulser.h"

namespace DplUt {

Pulser::Voltage Pulser::s_paVoltage = Pulser::V50;
Pulser::Voltage Pulser::s_utVoltage = Pulser::V50;

Pulser::Pulser(QObject *parent) : QObject(parent),
    m_txrxMode(PE)
{

}

void Pulser::set_tx_rx_mode(Pulser::TxRxMode mode)
{
    if (m_txrxMode != mode) {
        m_txrxMode = mode;
        emit tx_rx_mode_changed(m_txrxMode);
    }
}

Pulser::Voltage Pulser::voltage(bool pa) const
{
    if (pa) {
        return s_paVoltage;
    } else {
        return s_utVoltage;
    }
}

void Pulser::set_voltage(bool pa, Pulser::Voltage v)
{
    if (pa && s_paVoltage != v) {
        s_paVoltage = v;
    } else if (s_utVoltage != v) {
        s_utVoltage = v;
    }
}

}
