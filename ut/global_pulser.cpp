/**
 * @file global_pulser.cpp
 * @brief 全局的脉冲发生器类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#include "global_pulser_p.h"

namespace DplUt {

GlobalPulser *GlobalPulser::instance()
{
    static GlobalPulser *s_globalPulser = new GlobalPulser();
    return s_globalPulser;
}

GlobalPulser::Voltage GlobalPulser::voltage(bool pa) const
{
    if (pa) {
        return d->m_paVoltage;
    }
    return d->m_utVoltage;
}

void GlobalPulser::set_voltage(bool pa, GlobalPulser::Voltage v)
{
    if (pa && d->m_paVoltage != v) {
        d->m_paVoltage = v;
        d->update_acquisition_rate();
        emit voltage_changed(true, v);
    } else if(!pa && d->m_utVoltage != v) {
        d->m_utVoltage = v;
        emit voltage_changed(false, v);
    }
}

GlobalPulser::PrfMode GlobalPulser::prf_mode() const
{
    return d->m_prfMode;
}

void GlobalPulser::set_prf_mode(GlobalPulser::PrfMode mode)
{
    if (d->m_prfMode != mode) {
        d->m_prfMode = mode;
        d->update_acquisition_rate();
    }
}

uint GlobalPulser::prf() const
{
    return DplDevice::Device::instance()->beam_qty() * acquisition_rate();
}

int GlobalPulser::acquisition_rate() const
{
    return d->m_acqRate;
}

int GlobalPulser::max_acquisition_rate() const
{
    return d->max_acquisition_rate();
}

bool GlobalPulser::set_acquisition_rate(int val)
{
    if (USER_DEF == d->m_prfMode && d->m_acqRate != val) {
        d->m_acqRate = val;
        emit prf_changed();
        return true;
    } else {
        return false;
    }
}

float GlobalPulser::beam_cycle() const
{
    return Dpl::s_to_ns(1.0)/prf() - DplFpga::Fpga::LOADING_TIME * DplFpga::Fpga::SAMPLE_PRECISION;
}

void GlobalPulser::connect_group(const DplDevice::Group *grp)
{
    connect(static_cast<DplFocallaw::Focallawer *>(grp->focallawer().data()),
            SIGNAL(focallawed()),
            d,
            SLOT(update_acquisition_rate()));
    connect(static_cast<Transceiver *>(grp->transceiver().data()),
            SIGNAL(work_time_changed()),
            d,
            SLOT(update_acquisition_rate()));
    connect(static_cast<Transceiver *>(grp->transceiver().data()),
            SIGNAL(pw_changed(float)),
            d,
            SLOT(update_acquisition_rate()));
    connect(static_cast<Sample *>(grp->sample().data()),
            SIGNAL(point_qty_changed(int)),
            d,
            SLOT(update_acquisition_rate()));
}

GlobalPulser::GlobalPulser() : QObject(),
    d(new GlobalPulserPrivate(this))
{
    connect(DplDevice::Device::instance(),
            SIGNAL(beam_qty_changed()),
            this,
            SIGNAL(prf_changed()));
}

GlobalPulser::~GlobalPulser()
{
    delete d;
}



}
