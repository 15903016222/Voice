#ifndef __DPLUT_SAMPLE_H__
#define __DPLUT_SAMPLE_H__

#include <fpga/group.h>

namespace DplUt {

class SamplePrivate;
class Sample : public QObject
{
    Q_OBJECT
public:
    explicit Sample(const DplFpga::GroupPointer &fpgaGrp);

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
     * @brief is_auto_set_point_qty 获取设置采样点方式
     * @return                      如果是自动设置采样点，则返回true，否则为false
     */
    bool is_auto_set_point_qty() const;

    /**
     * @brief max_point_qty 采取最大采样点数
     * @return              采样点数
     */
    int max_point_qty() const;

    /**
     * @brief set_point_qty 设置采样点数, 如果设置了自动设置采样点状态，那么该函数会一直返回false
     * @param qty           采样点数
     * @param autoset       自动设置采样点，如果设置为自动，那么qty则没用
     * @return              设置成功返回true， 失败返回false
     */
    bool set_point_qty(int qty, bool autoset=false);

signals:
    void gain_changed(float gain);
    void start_changed(float start);
    void range_changed(float range);
    void scale_factor_changed(int ratio);
    void point_qty_changed(int qty);

private:
    float m_start;              // 采样起点(ns)
    float m_range;              // 采样范围(ns)
    SamplePrivate *d;
};

typedef QSharedPointer<Sample> SamplePointer;

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

inline int Sample::scale_factor() const
{
    return range()/precision()/point_qty();
}

}
#endif // __DPLUT_SAMPLE_H__
