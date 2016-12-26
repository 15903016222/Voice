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

private:
    GroupPrivate *d;
};

}
