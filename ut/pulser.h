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

    /**
     * @brief pw    获取脉冲宽度
     * @return      宽度(ns)
     */
    float pw() const;

    /**
     * @brief set_pw    设置脉冲宽度
     * @param w         宽度(ns)
     */
    void set_pw(float w);

signals:
    void txrx_mode_changed(TxRxMode);
    void pw_changed(float);

public slots:

private:
    TxRxMode m_txrxMode;
    float m_pw;
};

typedef QSharedPointer<Pulser> PulserPointer;

inline Pulser::TxRxMode Pulser::tx_rx_mode() const
{
    return m_txrxMode;
}

inline float Pulser::pw() const
{
    return m_pw;
}

}
#endif // __DPLUT_PULSER_H__
