/**
 * @file group_config.h
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include <QObject>
#include "fpga/group.h"

namespace DplDevice {

class GroupPrivate;

class Group : public DplFpga::Group
{
public:
    explicit Group(int index);
    ~Group();

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
    int start();

    /**
     * @brief set_start 设置声程轴的起始值
     * @param value     起始值，单位(ns)
     */
    void set_start(int value);

    /**
     * @brief range 获取声程轴的范围值
     * @return      返回范围值，单位(ns)
     */
    int range();

    /**
     * @brief set_range 设置声程轴的范围值
     * @param value     范围值，单位(ns)
     */
    void set_range(int value);

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
     * @brief wedge_delay   楔块延迟时间
     * @return              返回楔块延迟时间，单位(ns)
     */
    int wedge_delay();

    /**
     * @brief set_wedge_delay   设置楔块延迟时间
     * @param value             延迟时间，单位(ns)
     */
    void set_wedge_delay(int value);

    /**
     * @brief current_angle 获取当前入射角度
     * @return              角度值，单位(度)
     */
    double current_angle();

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
     * @brief max_rx_time   获取最大接收时间
     * @return              返回最大接收时间，单位(ns)
     */
    int max_rx_time();
private:
    GroupPrivate *d;

    void update_sample();
};

}
