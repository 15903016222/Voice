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
     * @brief set_prf_mode  设置重复频率模式
     * @param mode          模式
     */
    void set_prf_mode(PrfMode mode);

signals:
    void voltage_changed(bool, DplUt::GlobalPulser::Voltage);
    void prf_mode_changed(DplUt::GlobalPulser::PrfMode);

protected:
    explicit GlobalPulser() {}
    ~GlobalPulser();

private:
    GlobalPulserPrivate *d;
};

}

#endif /* end of __GLOBAL_PULSER_H__ */
