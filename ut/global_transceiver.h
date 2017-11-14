/**
 * @file global_transceiver.h
 * @brief 全局的脉冲发生器类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#ifndef __GLOBAL_TRANSCEIVER_H__
#define __GLOBAL_TRANSCEIVER_H__

#include <fpga/fpga.h>
#include <device/group.h>

namespace DplUt {

class GlobalTransceiverPrivate;
class GlobalTransceiver : public QObject
{
    friend class GlobalTransceiverPrivate;
    Q_OBJECT
public:
    /**
     * @brief instance  获取GlobalPulser单例对象
     * @return          返回对象指针
     */
    static GlobalTransceiver *instance();

    enum Voltage {
        V50     = 50,
        V100    = 100,
        V200    = 200,
        V400    = 400
    };

    /**
     * @brief voltage   获取PA/UT输出电压
     * @param pa        PA标志
     * @return          返回电压类型
     */
    Voltage voltage(bool pa) const;

    /**
     * @brief set_voltage   设置PA/UT输出电压
     * @param pa            PA标志
     * @param v             电压类型
     */
    void set_voltage(bool pa, Voltage v);

    enum UtChannel {
        UT_1 = 1,
        UT_2
    };

    /**
     * @brief tx_damping    获取指定UT发射通道的阻尼
     * @param channel       指定通道
     * @return              阻尼类型
     */
    DplFpga::Fpga::DampingType tx_damping(UtChannel channel) const;

    /**
     * @brief set_tx_damping    设置指定UT发射通道的阻尼
     * @param channel           指定UT通道
     * @param type              阻尼类型
     */
    void set_tx_damping(UtChannel channel, DplFpga::Fpga::DampingType type);

    /**
     * @brief rx_damping    获取指定UT接收通道的阻尼
     * @param channel       指定通道
     * @return              阻尼类型
     */
    DplFpga::Fpga::DampingType rx_damping(UtChannel channel) const;

    /**
     * @brief set_rx_damping    设置指定UT接收通道的阻尼
     * @param channel           指定通道
     * @param type              阻尼类型
     */
    void set_rx_damping(UtChannel channel, DplFpga::Fpga::DampingType type);

    enum PrfMode {
        MAX,
        MAX_HALF,
        OPTIMUM,
        USER_DEF
    };

    /**
     * @brief prf_mode  获取重复频率模式
     * @return          模式
     */
    PrfMode prf_mode() const;

    /**
     * @brief set_prf_mode  设置重复频率模式
     * @param mode          模式
     */
    void set_prf_mode(PrfMode mode);

    /**
     * @brief prf   获取脉冲发射重复频率
     * @return      频率(Hz)
     */
    uint prf() const;

    /**
     * @brief acquisition_rate  获取采集率
     * @return                  频率(Hz)
     */
    int acquisition_rate() const;

    /**
     * @brief max_acquisition_rate  获取最大的采集率
     * @return                      频率(Hz)
     */
    int max_acquisition_rate() const;

    /**
     * @brief set_acquisition_rate  设置采集率
     * @param val                   采集频率(Hz),当重复频率模式设置为USER_DEF时才有效
     * @return                      成功返回true,否则为false
     */
    bool set_acquisition_rate(int val);

    /**
     * @brief beam_cycle    每条Beam的周期时间
     * @return              时间(ns)
     */
    float beam_cycle() const;

    /**
     * @brief connect_group 关联组信息
     * @param grp           组对象
     */
    void connect_group(const DplDevice::Group *grp);

signals:
    void voltage_changed(bool, DplUt::GlobalTransceiver::Voltage);
    void prf_changed();

protected:
    explicit GlobalTransceiver();
    ~GlobalTransceiver();

private:
    GlobalTransceiverPrivate *d;
};

}

#endif /* end of __GLOBAL_TRANSCEIVER_H__ */
