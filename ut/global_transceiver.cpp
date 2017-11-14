/**
 * @file global_pulser.cpp
 * @brief 全局的脉冲发生器类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#include "global_transceiver_p.h"

namespace DplUt {

GlobalTransceiver *GlobalTransceiver::instance()
{
    static GlobalTransceiver *s_globalPulser = new GlobalTransceiver();
    return s_globalPulser;
}

GlobalTransceiver::Voltage GlobalTransceiver::pa_voltage() const
{
    return d->m_paVoltage;
}

void GlobalTransceiver::set_pa_voltage(GlobalTransceiver::Voltage v)
{
    if (d->m_paVoltage == v) {
        return;
    }

    d->m_paVoltage = v;
    d->update_acquisition_rate();
    if (v == V50) {
        DplFpga::Fpga::instance()->set_pa_voltage(DplFpga::Fpga::VOLTAGE_LOW);
    } else if (v == V100) {
        DplFpga::Fpga::instance()->set_pa_voltage(DplFpga::Fpga::VOLTAGE_MIDDLE);
    }

    emit pa_voltage_changed(v);
}

GlobalTransceiver::Voltage GlobalTransceiver::ut_voltage() const
{
    return d->m_utVoltage;
}

void GlobalTransceiver::set_ut_voltage(GlobalTransceiver::Voltage v)
{
    if (d->m_utVoltage == v) {
        return;
    }

    d->m_utVoltage = v;
    if (v == V100) {
        DplFpga::Fpga::instance()->set_ut_voltage(DplFpga::Fpga::VOLTAGE_LOW);
    } else if (v == V200) {
        DplFpga::Fpga::instance()->set_ut_voltage(DplFpga::Fpga::VOLTAGE_MIDDLE);
    } else if (v == V400) {
        DplFpga::Fpga::instance()->set_ut_voltage(DplFpga::Fpga::VOLTAGE_HIGHT);
    }
    emit ut_voltage_changed(v);
}

DplFpga::Fpga::DampingType GlobalTransceiver::tx_damping(GlobalTransceiver::UtChannel channel) const
{
    if (channel == UT_1) {
        return DplFpga::Fpga::instance()->ut1_tx_damping();
    } else {
        return DplFpga::Fpga::instance()->ut2_tx_damping();
    }
}

void GlobalTransceiver::set_tx_damping(GlobalTransceiver::UtChannel channel, DplFpga::Fpga::DampingType type)
{
    if (channel == UT_1) {
        DplFpga::Fpga::instance()->set_ut1_tx_damping(type);
    } else {
        DplFpga::Fpga::instance()->set_ut2_tx_damping(type);
    }
}

GlobalTransceiver::PrfMode GlobalTransceiver::prf_mode() const
{
    return d->m_prfMode;
}

void GlobalTransceiver::set_prf_mode(GlobalTransceiver::PrfMode mode)
{
    if (d->m_prfMode != mode) {
        d->m_prfMode = mode;
        d->update_acquisition_rate();
    }
}

uint GlobalTransceiver::prf() const
{
    return DplDevice::Device::instance()->beam_qty() * acquisition_rate();
}

int GlobalTransceiver::acquisition_rate() const
{
    return d->m_acqRate;
}

int GlobalTransceiver::max_acquisition_rate() const
{
    return d->max_acquisition_rate();
}

bool GlobalTransceiver::set_acquisition_rate(int val)
{
    if (USER_DEF == d->m_prfMode && d->m_acqRate != val) {
        d->m_acqRate = val;
        emit prf_changed();
        return true;
    } else {
        return false;
    }
}

float GlobalTransceiver::beam_cycle() const
{
    return Dpl::s_to_ns(1.0)/prf() - DplFpga::Fpga::LOADING_TIME * DplFpga::Fpga::SAMPLE_PRECISION;
}

void GlobalTransceiver::connect_group(const DplDevice::Group *grp)
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

GlobalTransceiver::GlobalTransceiver() : QObject(),
    d(new GlobalTransceiverPrivate(this))
{
    connect(DplDevice::Device::instance(),
            SIGNAL(beam_qty_changed()),
            this,
            SIGNAL(prf_changed()));
}

GlobalTransceiver::~GlobalTransceiver()
{
    delete d;
}



}
