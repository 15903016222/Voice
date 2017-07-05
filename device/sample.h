#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include <QSharedPointer>

namespace DplDevice {

class Sample : public QObject
{
    Q_OBJECT
public:
    explicit Sample(float precision, QObject *parent = 0);

    /**
     * @brief precision 获取采样精度
     * @return
     */
    float precision() const;

    /**
     * @brief gain  获取增益
     * @return
     */
    float gain() const;

    /**
     * @brief set_gain  设置增益
     * @param gain      增益值(dB)
     */
    void set_gain(float gain);

    /**
     * @brief start 获取采样起点
     * @return      起点值(ns)
     */
    float start() const;

    /**
     * @brief set_start 设置采样起点
     * @param value     起点值(ns)
     */
    void set_start(float value);

    /**
     * @brief range 获取采样范围
     * @return      返回范围值(ns)
     */
    float range() const;

    /**
     * @brief set_range 设置采样范围
     * @param range     范围(ns)
     */
    void set_range(float range);

    /**
     * @brief MAX_SCALE_FACTOR  最大压缩系数
     */
    static const int MAX_SCALE_FACTOR = 2000;

    /**
     * @brief scale_factor  获取压缩系数
     * @return              系数
     */
    int scale_factor() const;

    /**
     * @brief point_qty 采样点数
     * @return          点数
     */
    int point_qty() const;

    /**
     * @brief set_point_qty 设置采样点数
     * @param qty           采样点数
     */
    void set_point_qty(int qty);

    /**
     * @brief velocity  获取声速
     * @return          返回声速(m/s)
     */
    float velocity();

    /**
     * @brief set_velocity  设置声速
     * @param value         声速(m/s)
     */
    void set_velocity(float velocity);

signals:
    void gain_changed(float gain);
    void start_changed(float start);
    void range_changed(float range);
    void scale_factor_changed(int ratio);
    void point_qty_changed(int qty);
    void velocity_changed(float velocity);

public slots:

private:
    float m_precision;      // 采样精度(ns)
    float m_gain;           // 增益(dB)
    float m_start;          // 采样起点(ns)
    float m_range;          // 采样范围(ns)
    float m_velocity;       // 声速(m/s)
    int m_pointQty;         // 采样点数
};

typedef QSharedPointer<Sample> SamplePointer;

inline float Sample::precision() const
{
    return m_precision;
}

inline float Sample::gain() const
{
    return m_gain;
}

inline void Sample::set_gain(float gain)
{
    if (!qFuzzyCompare(gain, m_gain)) {
        m_gain = gain;
        emit gain_changed(gain);
    }
}

inline float Sample::start() const
{
    return m_start;
}

inline void Sample::set_start(float start)
{
    if ( !qFuzzyCompare(start, m_start) ) {
        m_start = start;
        emit start_changed(start);
    }
}

inline float Sample::range() const
{
    return m_range;
}

inline void Sample::set_range(float range)
{
    qDebug("%s[%d]: range(%f)",__func__, __LINE__, range);
    if ( !qFuzzyCompare(range, m_range) && (range > point_qty()*precision())) {
        m_range = range;
        emit range_changed(range);
        emit scale_factor_changed(scale_factor());
    }
}

inline int Sample::scale_factor() const
{
    return range()/precision()/point_qty();
}

inline int Sample::point_qty() const
{
    return m_pointQty;
}

inline void Sample::set_point_qty(int qty)
{
    if (m_pointQty != qty) {
        m_pointQty = qty;
        emit point_qty_changed(qty);
        emit scale_factor_changed(scale_factor());
    }
}

inline float Sample::velocity()
{
    return m_velocity;
}

inline void Sample::set_velocity(float velocity)
{
    if ( ! qFuzzyCompare(m_velocity, velocity) ) {
        m_velocity = velocity;
    }
    emit velocity_changed(velocity);
}

}
#endif // __SAMPLE_H__
