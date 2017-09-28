#include "pulser.h"

namespace DplUt {

Pulser::Pulser(QObject *parent) : QObject(parent),
    m_txrxMode(PE)
{

}

void Pulser::set_tx_rx_mode(Pulser::TxRxMode mode)
{
    if (m_txrxMode != mode) {
        m_txrxMode = mode;
        emit txrx_mode_changed(m_txrxMode);
    }
}

void Pulser::set_pw(float w)
{
    if (!qFuzzyIsNull(w) && qFuzzyCompare(m_pw, w)) {
        m_pw = w;
        emit pw_changed(m_pw);
    }
}

}
