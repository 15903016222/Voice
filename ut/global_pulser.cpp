/**
 * @file global_pulser.cpp
 * @brief 全局的脉冲发生器类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#include "global_pulser.h"

namespace DplUt {

class GlobalPulserPrivate
{
public:
    GlobalPulserPrivate() :
        m_paVoltage(GlobalPulser::V50),
        m_utVoltage(GlobalPulser::V50),
        m_prfMode(GlobalPulser::OPTIMUM)
    {}

    /* attributions */
    GlobalPulser::Voltage m_paVoltage;
    GlobalPulser::Voltage m_utVoltage;
    GlobalPulser::PrfMode m_prfMode;
};

GlobalPulser *GlobalPulser::instance()
{
    static GlobalPulser *s_globalPulser = new GlobalPulser();
    return s_globalPulser;
}

GlobalPulser::Voltage GlobalPulser::voltage(bool pa) const
{
    if (ps) {
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

void GlobalPulser::set_prf_mode(GlobalPulser::PrfMode mode)
{
    if (d->m_prfMode != mode) {
        d->m_prfMode = mode;
        emit prf_mode_changed(d->m_prfMode);
    }
}



}
