/**
 * @file group_config.h
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#ifndef __DEVICE_GROUP_H__
#define __DEVICE_GROUP_H__

#include <QObject>

#include <fpga/group.h>
#include <probe/probe.h>
#include <probe/wedge.h>

namespace DplDevice {

class GroupPrivate;

class Group : public DplFpga::Group
{
    Q_OBJECT
public:
    explicit Group(int index);
    ~Group();

    enum Mode {
        UT,
        PA,
        UT1,
        UT2
    };
    /**
     * @brief mode  获取组模式
     * @return      组模式
     */
    Mode mode();

    /**
     * @brief set_mode  设置组模式
     * @param mode      组模式
     */
    void set_mode(Mode mode);

    enum UtUnit {
        Time,
        SoundPath,
        TruePath
    };
    UtUnit ut_unit();
    void set_ut_unit(UtUnit type);

    /**
     * @brief start 获取声程轴上的起始值
     * @return      起始值,单位(ns)
     */
    double start();

    /**
     * @brief set_start 设置声程轴的起始值
     * @param value     起始值，单位(ns)
     */
    void set_start(double value);

    /**
     * @brief range 获取声程轴的范围值
     * @return      返回范围值，单位(ns)
     */
    double range();

    /**
     * @brief set_range 设置声程轴的范围值
     * @param value     范围值，单位(ns)
     */
    void set_range(double value);

    /**
     * @brief velocity  获取声速
     * @return          返回声速大小，单位为(m/s)
     */
    double velocity();

    /**
     * @brief set_velocity  设置声速
     * @param value         声速大小，单位为(m/s)
     */
    void set_velocity(double value);

    /**
     * @brief current_angle 获取当前入射角度
     * @return              角度值，单位(MI_P)
     */
    double current_angle();

    /**
     * @brief set_current_angle 设置当前入射角度
     * @param angle             角度，单位(MI_P)
     */
    void set_current_angle(double angle);

    enum PointQtyMode {
        PointQtyAuto,
        PointQty160,
        PointQty320,
        PointQty640,
        PointQtyUserDef
    };
    /**
     * @brief point_qty_mode    获取采样点模式
     * @return                  采样点模式
     */
    PointQtyMode point_qty_mode();

    /**
     * @brief set_point_qty_mode    设置采样点模式
     * @param mode                  采样点模式
     * @return                      成功返回true，否则false
     */
    bool set_point_qty_mode(PointQtyMode mode);

    /**
     * @brief beam_qty  获取组包含的beam数
     * @return          返回beam数
     */
    int beam_qty();

    /**
     * @brief max_sample_time   获取最大Start+Range时间
     * @return              返回最大Start+Range时间，单位(ns)
     */
    double max_sample_time();

    /**
     * @brief max_start 获取最大的start时间
     * @return          时间，单位(ns)
     */
    double max_start();

    /**
     * @brief max_range 获取最大的range时间
     * @return          时间，单位(ns)
     */
    double max_range();

    DplProbe::ProbePointer get_probe() const;
    DplProbe::WedgePointer get_wedge() const;

signals:
    void mode_changed(DplDevice::Group::Mode mode);
    void start_changed(double val);
    void range_changed(double val);
    void velocity_changed(double val);
    void ut_unit_changed(DplDevice::Group::UtUnit type);

private slots:
    void update_sample();

private:
    GroupPrivate *d;

    DplProbe::ProbePointer m_probePtr; /* 探头 */
    DplProbe::WedgePointer m_wedgePtr; /* 楔块 */
};

inline double Group::max_start()
{
    return max_sample_time() - range();
}

inline double Group::max_range()
{
    return max_sample_time() - start();
}

inline DplProbe::ProbePointer Group::get_probe() const
{
    return m_probePtr;
}

inline DplProbe::WedgePointer Group::get_wedge() const
{
    return m_wedgePtr;
}

}
#endif // __DEVICE_GROUP_H__
