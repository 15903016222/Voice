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
        emit voltage_changed(true, v);
    } else if(!pa && d->m_utVoltage != v) {
        d->m_utVoltage = v;
        emit voltage_changed(false, v);
    }
}

GlobalPulser::PrfMode GlobalPulser::prf_mode()
{
    return d->m_prfMode;
}

uint GlobalPulser::prf() const
{
    return DplDevice::Device::instance()->total_beam_qty() * acquisition_rate();
}

int GlobalPulser::acquisition_rate() const
{
    return d->m_acqRate;
}

void GlobalPulser::set_acquisition_rate(GlobalPulser::PrfMode mode, uint val)
{
    int rate = 1;
    if (MAX == mode) {
        rate = d->max_acquisition_rate();
    } else if (MAX_HALF == mode) {
        rate = d->max_acquisition_rate();
        if (rate > 1) {
            rate /= 2;
        }
    } else if (OPTIMUM == mode) {
        rate = d->max_acquisition_rate();
        if (rate > 60) {
            rate = 60;
        }
    } else if (USER_DEF == mode) {
        rate = val;
    }

    d->m_prfMode = mode;

    if (d->m_acqRate != rate) {
        d->m_acqRate = rate;
        emit acquisition_rate_changed(rate);
    }
}

float GlobalPulser::beam_cycle() const
{
    return Dpl::s_to_ns(1.0)/prf() - DplFpga::Fpga::LOADING_TIME * DplFpga::Fpga::SAMPLE_PRECISION;
}

GlobalPulser::GlobalPulser() :
    d(new GlobalPulserPrivate)
{

}

GlobalPulser::~GlobalPulser()
{
    delete d;
}



}
