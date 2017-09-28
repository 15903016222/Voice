/**
 * @file global_pulser_p.cpp
 * @brief 全局脉冲发生器的私有类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#include "global_pulser_p.h"

#include <source/source.h>

namespace DplUt {

GlobalPulserPrivate::GlobalPulserPrivate() :
    m_paVoltage(GlobalPulser::V50),
    m_utVoltage(GlobalPulser::V50),
    m_prfMode(GlobalPulser::OPTIMUM),
    m_acqRate(60)
{

}

int GlobalPulserPrivate::max_txrx_time() const
{
    int max = 1;
    foreach (DplDevice::GroupPointer grp, DplDevice::Device::instance()->groups()) {
        if (max < grp->txrx_time()) {
            max = grp->txrx_time();
        }
    }
    return max;
}

int GlobalPulserPrivate::max_acquisition_rate() const
{
    DplDevice::Device *dev = DplDevice::Device::instance();

    double prfLimit[3] = {0.0};
    int beamQty = dev->total_beam_qty();
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
            power = grp->pulser()->pw() * qPow(m_paVoltage, 2) / DplFocallaw::PaProbe::RESISTANCE;
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

}
