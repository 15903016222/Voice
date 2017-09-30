#include "pulser.h"

namespace DplUt {

class PulserPrivate
{
public:
    PulserPrivate(const SamplePointer &sample, const DplFocallaw::Focallawer &focallawer) :
        m_txrxMode(Pulser::PE),
        m_pw(100),
        m_sample(sample),
        m_focallawer(focallawer)
    {}
    /* Attribution */
    Pulser::TxRxMode m_txrxMode;
    float m_pw;
    SamplePointer m_sample;
    DplFocallaw::FocallawerPointer m_focallawer;
};

Pulser::Pulser(const SamplePointer &sample, const DplFocallaw::FocallawerPointer &focallawer) : QObject(),
    d(new PulserPrivate)
{
    connect(static_cast<Sample *>(sample.data()),
            SIGNAL(start_changed(float)),
            this,
            SIGNAL(txrx_time_changed()));
    connect(static_cast<Sample *>(sample.data()),
            SIGNAL(range_changed(float)),
            this,
            SIGNAL(txrx_time_changed()));
    connect(static_cast<DplFocallaw::Wedge *>(focallawer->wedge().data()),
            SIGNAL(delay_changed(int)),
            this,
            SIGNAL(txrx_time_changed()));
    connect(static_cast<DplFocallaw::Focallawer *>(focallawer.data()),
            SIGNAL(focallawed()),
            this,
            SIGNAL(txrx_time_changed()));
}

Pulser::TxRxMode Pulser::tx_rx_mode() const
{
    return d->m_txrxMode;
}

void Pulser::set_tx_rx_mode(Pulser::TxRxMode mode)
{
    if (m_txrxMode != mode) {
        m_txrxMode = mode;
        emit txrx_mode_changed(m_txrxMode);
    }
}

float Pulser::pw() const
{
    return d->m_pw;
}

void Pulser::set_pw(float w)
{
    if (!qFuzzyIsNull(w) && qFuzzyCompare(d->m_pw, w)) {
        d->m_pw = w;
        emit pw_changed(w);
    }
}

int Pulser::txrx_time() const
{
    return d->m_focallawer->max_beam_delay()
            + d->m_focallawer->wedge()->delay()
            + d->m_sample->start()
            + d->m_sample->range();
}

}
