/**
 * @file global_pulser_p.cpp
 * @brief 全局脉冲发生器的私有类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#include "global_transceiver_p.h"

#include <source/source.h>

namespace DplUt {

GlobalTransceiverPrivate::GlobalTransceiverPrivate(GlobalTransceiver *parent) : QObject(),
    m_paVoltage(GlobalTransceiver::V50),
    m_utVoltage(GlobalTransceiver::V100),
    m_prfMode(GlobalTransceiver::OPTIMUM),
    m_acqRate(60),
    q(parent)
{
    connect(DplDevice::Device::instance(),
            SIGNAL(beam_qty_changed()),
            this,
            SLOT(update_acquisition_rate()));
    update_acquisition_rate();
}

int GlobalTransceiverPrivate::max_txrx_time() const
{
    int max = 1;
    foreach (DplDevice::GroupPointer grp, DplDevice::Device::instance()->groups()) {
        if (max < grp->transceiver()->work_time()) {
            max = grp->transceiver()->work_time();
        }
    }
    return max;
}

int GlobalTransceiverPrivate::max_acquisition_rate() const
{
    DplDevice::Device *dev = DplDevice::Device::instance();

    double prfLimit[3] = {0.0};
    int beamQty = dev->beam_qty();
    int totalDataSize = DplSource::Source::instance()->beams_size();

    // the rx_time used to calculate PRF is the max rx_time of each group
    // then the idel_time will be 3*max_rx_time minus current group rx_time
    //single_beam_time = 4 * max_rx_time;
    prfLimit[0] = (Dpl::s_to_ns(1.0)/4) / (max_txrx_time() * beamQty );

    double power = 0.0;
    double elementPower = 0.0;
    double totalElementPower = 0.0;

    foreach (DplDevice::GroupPointer grp, dev->groups()) {
        if (grp->focallawer()->probe()->is_pa()) {
            DplFocallaw::PaProbePointer probe = grp->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
            power = grp->transceiver()->pw() * qPow(m_paVoltage, 2) / DplFocallaw::PaProbe::RESISTANCE;
            elementPower += grp->focallawer()->beam_qty() * power;
            totalElementPower += probe->scan_configure()->aperture() * elementPower;
        }
    }

    if(qFuzzyIsNull(elementPower)) {
        prfLimit[1]  =  6000;
    } else {
        prfLimit[1]  =  (pa_max_power() * Dpl::s_to_ns(1.0) / 4) / elementPower;
    }

    if(qFuzzyIsNull(totalElementPower)) {
        prfLimit[2]  =  6000;
     }else {
        prfLimit[2]  =  2*1000*1000*1000 / totalElementPower;
    }

    double result = prfLimit[0];
    for(int i = 1 ; i < 3 ; i ++) {
        if(result > prfLimit[i]) {
            result = prfLimit[i] ;
        }
    }

    // total prf limit
    if(result * beamQty > 20000) {
        result = 20000 / beamQty;
    }

    // total data size limit
    if(result * totalDataSize > 8 *1024 * 1024) {
        result = 8 * 1024 * 1024 / totalDataSize;
    }

    // max interrupt limit
    if(result > 6000) {
        result = 6000 ;
    }

    return  (result)<1 ? 1: result;
}

void GlobalTransceiverPrivate::update_acquisition_rate()
{
    if (GlobalTransceiver::USER_DEF == m_prfMode) {
        return;
    }

    int rate = max_acquisition_rate();
    if (GlobalTransceiver::MAX_HALF == m_prfMode && rate > 1) {
        rate /= 2;
    } else if (GlobalTransceiver::OPTIMUM == m_prfMode && rate > 60) {
        rate = 60;
    }

    if (m_acqRate != rate) {
        m_acqRate = rate;
        emit q->prf_changed();
    }
}

}
