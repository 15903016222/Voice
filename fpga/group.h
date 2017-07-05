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
#include <QObject>

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

    /* 频带选择 */
    enum FreqBand {             /* 探头频率  对应带宽   采样频率 */
        FREQ_BAND_05_20,        /*  none    0.5-20    100M */
        FREQ_BAND_05_25,        /*  1       0.5-2.5   25M */
        FREQ_BAND_10_25,        /*  1.5-2.5 1-5       25M */
        FREQ_BAND_20_100,       /*  3-5     2-10      50M */
        FREQ_BAND_40_160,       /*  7.5     4-16      100M */
        FREQ_BAND_50_200        /*  >=10    5-20      100M */
    };
    FreqBand freq_band(void) const;
    bool set_freq_band(FreqBand band, bool reflesh = false);

    bool video_filter(void) const;         /* 视频滤波 */
    bool enable_video_filter(bool flag, bool reflesh = false);

    enum RectifierType {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE
    };
    Group::RectifierType rectifier(void) const;
    bool set_rectifier(Group::RectifierType type, bool reflesh = false);

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
    bool set_sample_range(int range, bool reflesh = false);

    /**
     * @brief point_qty 获取压缩后的采样点数
     * @return          采样点数
     */
    int point_qty(void) const;

    int tcg_point_qty(void) const;
    bool set_tcg_point_qty(int qty, bool reflesh = false);

    bool tcg(void) const;
    bool enable_tcg(bool flag, bool reflesh = false);

    int idel_time(void) const;
    bool set_idel_time(int val, bool reflesh = false);

    /**
     * @brief gate_a_height 闸门A高度
     * @return              高度(%)
     */
    int gate_a_height() const;

    /**
     * @brief gate_b_height 闸门B高度
     * @return              高度(%)
     */
    int gate_b_height() const;

    /**
     * @brief gate_i_height 闸门I高度
     * @return              高度(%)
     */
    int gate_i_height() const;

    int gate_a_logic(void) const;
    bool set_gate_a_logic(int val, bool reflesh = false);


    int gate_b_logic(void) const;
    bool set_gate_b_logic(int val, bool reflesh = false);

    int gate_i_logic(void) const;
    bool set_gate_i_logic(int val, bool reflesh = false);

    int thickness_min(void) const;
    bool set_thickness_min(int val, bool reflesh = false);

    int reject(void) const;
    bool set_reject(int val, bool reflesh = false);


    int average(void) const;
    bool set_average(int val, bool reflesh = false);

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

    /**
     * @brief sample_start  获取采样起点
     * @return              返回采样起点值，单位(采样精度)
     */
    int sample_start(void) const;

public slots:
    /**
     * @brief set_gain  设置增益
     * @param gain      增益值
     */
    void set_gain(float gain);

    /**
     * @brief set_gate_a_height 设置闸门A高度
     * @param height            高度(%)
     */
    void set_gate_a_height(int height);

    /**
     * @brief set_gate_b_height 设置闸门B高度
     * @param height            高度(%)
     */
    void set_gate_b_height(int height);

    /**
     * @brief set_gate_i_height 设置闸门I高度
     * @param height            高度(%)
     */
    void set_gate_i_height(int height);

    /**
     * @brief set_sample_start  设置采样起点
     * @param val               采样起点值，单位(采样精度)
     * @param reflesh           下发配置标志
     * @return                  成功返回true，否则返回false
     */
    bool set_sample_start(int val, bool reflesh = false);

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

    /**
     * @brief rx_time   获取接收工作时间
     * @return          接收工作时间，单位(采样精度)
     */
    int rx_time(void) const;

    /**
     * @brief set_rx_time   设置接收工作时间
     * @param val           时间，单位(采样精度)
     * @param reflesh       下发配置标志
     * @return              成功返回true，失败返回false
     */
    bool set_rx_time(int val, bool reflesh = false);

private:
    GroupPrivate *d;
};

typedef QSharedPointer<Group> GroupPointer;

}
#endif // __GROUP_H__
