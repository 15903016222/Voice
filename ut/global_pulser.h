/**
 * @file global_pulser.h
 * @brief 全局的脉冲发生器类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-09-28
 */

#ifndef __GLOBAL_PULSER_H__
#define __GLOBAL_PULSER_H__

#include <QObject>

namespace DplUt {

class GlobalPulserPrivate;
class GlobalPulser : public QObject
{
    Q_DECLARE_PRIVATE(GlobalPulser)
    Q_OBJECT
public:
    /**
     * @brief instance  获取GlobalPulser单例对象
     * @return          返回对象指针
     */
    static GlobalPulser *instance();

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
    PrfMode prf_mode();

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
     * @brief set_acquisition_rate  设置采集率
     * @param mode                  脉冲重复频率模式
     * @param val                   采集频率(Hz),当重复频率模式设置为USER_DEF时才有效
     */
    void set_acquisition_rate(PrfMode mode, uint val=0);

    /**
     * @brief beam_cycle    每条Beam的周期时间
     * @return              时间(ns)
     */
    float beam_cycle() const;

signals:
    void voltage_changed(bool, DplUt::GlobalPulser::Voltage);
    void acquisition_rate_changed(int);
    void prf_changed();
    void beam_cycle_changed();

protected:
    explicit GlobalPulser();
    ~GlobalPulser();

private:
    GlobalPulserPrivate *d;
};

}

#endif /* end of __GLOBAL_PULSER_H__ */
