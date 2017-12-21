/**
 * @file global_pulser_p.h
 * @brief 全局脉冲发生器的私有类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#include "global_transceiver.h"
#include <global.h>
#include <device/device.h>

namespace DplUt {

class GlobalTransceiverPrivate : public QObject
{
    Q_OBJECT
public:
    GlobalTransceiverPrivate(GlobalTransceiver *parent);

    /**
     * @brief pa_max_power  PA最大输出功率
     * @return              功率(W)
     */
    float pa_max_power() const;

    /**
     * @brief max_txrx_time 获取最大工作时间
     * @return              时间(ns)
     */
    int max_txrx_time() const;

    /**
     * @brief max_acquisition_rate  获取最大的采集率
     * @return                      采集率(Hz)
     */
    int max_acquisition_rate() const;

    /* attributions */
    GlobalTransceiver::Voltage m_paVoltage;
    GlobalTransceiver::Voltage m_utVoltage;
    GlobalTransceiver::PrfMode m_prfMode;   // 脉冲重复频率模式
    int m_acqRate;                          // 采集率

public slots:
    void update_acquisition_rate();
    void do_prf_changed();

private:
    GlobalTransceiver *q;
};

inline float GlobalTransceiverPrivate::pa_max_power() const
{
    return 1.0;
}

}
