/**
 * @file group.h
 * @brief Group
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#ifndef __GROUP_H__
#define __GROUP_H__

#include "fpga_global.h"
#include <QSharedPointer>

namespace DplFpga {

class GroupPrivate;

class FPGASHARED_EXPORT Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(const int index, QObject *parent = 0);
    ~Group();

    /**
     * @brief index 获取组序号
     * @return      返回组序号
     */
    int index(void) const;

    /****************************************************************
     *                            滤波器档位说明
     *                  PA                            UT
     * 档位  探头频率  对应带宽   采样频率      探头频率  对应带宽   采样频率
     * 0     none    0.5-20    100M         none
     * 1      1      0.5-2.5   25M          1-2M
     * 2     1.5-2.5  1-5      25M          2-3M
     * 3     3-5     2-10      50M          3-6M
     * 4     7.5     4-16      100M         6-10M
     * 5     >=10    5-20      100M         >=10M
     *****************************************************************/
    /**
     * @brief filter    获取滤波器档位
     * @return          档位
     */
    int filter(void) const;

    /**
     * @brief set_filter    设置滤波器档位
     * @param val           档位
     * @return              成功返回true, 失败返回false
     */
    bool set_filter(int val);

    /**
     * @brief video_filter  获取视频滤波状态
     * @return              开启则返回true, 否则为false
     */
    bool video_filter(void) const;

    /**
     * @brief enable_video_filter   设置视频滤波
     * @param flag                  true为开启,false为关闭
     * @return                      设置成功返回true, 失败返回false
     */
    bool enable_video_filter(bool flag);

    /**
     * @brief The Rectifier enum    整流器类型
     */
    enum Rectifier {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE
    };

    /**
     * @brief rectifier 获取整流器类型
     * @return          类型
     */
    Group::Rectifier rectifier(void) const;

    /**
     * @brief set_rectifier 设置整流器类型
     * @param type          类型
     * @return              成功返回true，否则为false
     */
    bool set_rectifier(Group::Rectifier type);

    /**
     * @brief scale_factor  获取采样点压缩系数
     * @return              压缩系数
     */
    int scale_factor(void) const;

    /**
     * @brief gain  获取增益
     * @return      返回增益值， 单位(dB)
     */
    float gain(void) const;

    int thickness_factor(void) const;
    bool set_thickness_factor(int factor, bool reflesh = false);

    /**
     * @brief The Mode enum 组工作模式
     */
    enum Mode {
        UT1 = 0b001,
        UT2 = 0b010,
        PA  = 0b100
    };

    /**
     * @brief mode  获取组工作模式
     * @return      组工作模式
     */
    Mode mode() const;

    /**
     * @brief set_mode  设置组工作模式
     * @param m         组工作模式
     * @return          成功返回true，否则false
     */
    bool set_mode(Mode m);

    int sum_gain(void) const;
    bool set_sum_gain(int gain, bool reflesh = false);

    int sample_range(void) const;
    bool set_sample_range(int range);

    /**
     * @brief point_qty 获取压缩后的采样点数
     * @return          采样点数
     */
    int point_qty(void) const;


    int tcg_point_qty(void) const;
    bool set_tcg_point_qty(int qty, bool reflesh = false);

    bool tcg(void) const;
    bool enable_tcg(bool flag, bool reflesh = false);

    /**
     * @brief rx_time   获取接收工作时间
     * @return          接收工作时间，单位(采样精度)
     */
    int rx_time(void) const;

    /**
     * @brief set_rx_time   设置接收工作时间
     * @param val           时间，单位(采样精度)
     * @return              成功返回true，失败返回false
     */
    bool set_rx_time(int val);

    /**
     * @brief idle_time     获取空闲时间
     * @return              时间(采样精度)
     */
    int idle_time(void) const;

    /**
     * @brief set_idle_time 设置空闲时间
     * @param val           时间（采样精度）
     * @return
     */
    bool set_idle_time(int val);

    /**
     * @brief The GateType enum 闸门类型
     */
    enum GateType {
        GATE_A,
        GATE_B,
        GATE_I
    };

    /**
     * @brief gate_height   获取指定闸门高度
     * @param type          闸门类型
     * @return              高度(%)
     */
    int gate_height(GateType type) const;

    /**
     * @brief set_gate_height   设置指定闸门高度
     * @param type              闸门类型
     * @param height            高度(%)
     * @return                  设置成功返回true，失败为false
     */
    bool set_gate_height(GateType type, int height);

    /**
     * @brief The SynchroMode enum  闸门同步模式
     */
    enum SynchroMode {
        SYNCHRO_PULSER,
        SYNCHRO_I,
        SYNCHRO_A,
        SYNCHRO_B,
    };

    /**
     * @brief gate_synchro_mode 获取指定闸门的同步模式
     * @param type              闸门类型
     * @return                  同步模式
     */
    SynchroMode gate_synchro_mode(GateType type) const;

    /**
     * @brief set_gate_synchro_mode 设置指定闸门的同步模式
     * @param type                  闸门类型
     * @param mode                  同步模式
     * @return                      设置成功返回true，失败返回false
     */
    bool set_gate_synchro_mode(GateType type, SynchroMode mode);

    /**
     * @brief The MeasureMode enum  闸门测量模式
     */
    enum MeasureMode {
        EDGE,
        PEAK
    };

    /**
     * @brief gate_measure_mode 获取指定闸门的测量模式
     * @param type              闸门类型
     * @return                  测量模式
     */
    MeasureMode gate_measure_mode(GateType type) const;

    /**
     * @brief set_gate_measure_mode 设置指定闸门的测量模式
     * @param type                  闸门类型
     * @param mode                  测量模式
     * @return                      设置成功返回true，失败返回false
     */
    bool set_gate_measure_mode(GateType type, MeasureMode mode);

    int thickness_min(void) const;
    bool set_thickness_min(int val, bool reflesh = false);

    int reject(void) const;
    bool set_reject(int val, bool reflesh = false);

    /**
     * @brief sample_start  获取采样起点
     * @return              返回采样起点值，单位(采样精度)
     */
    int sample_start(void) const;

    /**
     * @brief set_sample_start  设置采样起点
     * @param val               采样起点值，单位(采样精度)
     * @return                  成功返回true，否则返回false
     */
    bool set_sample_start(int val);

    enum Averaging {
        AVERAGING_1,
        AVERAGING_2,
        AVERAGING_4,
        AVERAGING_8,
        AVERAGING_16
    };

    /**
     * @brief averaging 获取平均值类型
     * @return          平均值类型
     */
    Averaging averaging(void) const;

    /**
     * @brief set_averaging 设置平均值类型
     * @param val
     * @return
     */
    bool set_averaging(Averaging val);

    int thickness_max(void) const;
    bool set_thickness_max(int val, bool reflesh = false);

    int thickness_source(void) const;
    bool set_thickness_source(int val, bool reflesh = false);

    int tx_end(void) const;
    bool set_tx_end(int val, bool reflesh = false);

    int tx_start(void) const;
    bool set_tx_start(int val, bool reflesh = false);

    /**
     * @brief init  初始化配置
     */
    void init();

    /**
     * @brief reflesh   更新配置
     * @return
     */
    bool reflesh(void);

    /**
     * @brief show_info 显示信息
     */
    void show_info() const;

public slots:
    /**
     * @brief set_gain  设置增益
     * @param gain      增益值
     */
    void set_gain(float gain);

    /**
     * @brief set_scale_factor      设置采样点压缩系数
     * @param val                   压缩系数
     */
    void set_scale_factor(int val);

    /**
     * @brief set_point_qty 设置压缩后的采样点数
     * @param qty           采样点数
     */
    void set_point_qty(int qty);

private:
    GroupPrivate *d;
};

typedef QSharedPointer<Group> GroupPointer;

}
#endif // __GROUP_H__
