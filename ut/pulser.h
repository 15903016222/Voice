#ifndef __DPLUT_PULSER_H__
#define __DPLUT_PULSER_H__

#include <QSharedPointer>

namespace DplUt {

class Pulser : public QObject
{
    Q_OBJECT
public:
    explicit Pulser(QObject *parent = 0);

    enum TxRxMode {
        PE,
        PC,
        TT,
        TOFD
    };

    /**
     * @brief tx_rx_mode    获取Tx/Rx模式
     * @return              模式
     */
    TxRxMode tx_rx_mode() const;

    /**
     * @brief set_tx_rx_mode    设置Tx/Rx模式
     * @param mode              模式
     * @return                  成功返回true，否则返回false
     */
    void set_tx_rx_mode(TxRxMode mode);

    enum Voltage {
        V50,
        V100,
        V200,
        V400
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

    /**
     * @brief width 获取脉冲宽度
     * @return      宽度(ns)
     */
    float width() const;

    /**
     * @brief set_width 设置脉冲宽度
     * @param w         宽度(ns)
     */
    void set_width(float w);

signals:
    void tx_rx_mode_changed(TxRxMode mode);

public slots:

private:
    static Voltage s_paVoltage;
    static Voltage s_utVoltage;
    TxRxMode m_txrxMode;
};

typedef QSharedPointer<Pulser> PulserPointer;

inline Pulser::TxRxMode Pulser::tx_rx_mode() const
{
    return m_txrxMode;
}

}
#endif // __DPLUT_PULSER_H__
