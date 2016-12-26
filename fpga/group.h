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
#include <QReadWriteLock>

namespace DplFpga {

class GroupPrivate;

class FPGASHARED_EXPORT Group
{
public:
    explicit Group(const int index);
    ~Group();

    /**
     * @brief index 获取组序号
     * @return      返回组序号
     */
    int index(void);

    /* 频带选择 */
    enum FreqBand {             /* 探头频率  对应带宽   采样频率 */
        FREQ_BAND_05_20,        /*  none    0.5-20    100M */
        FREQ_BAND_05_25,        /*  1       0.5-2.5   25M */
        FREQ_BAND_10_25,        /*  1.5-2.5 1-5       25M */
        FREQ_BAND_20_100,       /*  3-5     2-10      50M */
        FREQ_BAND_40_160,       /*  7.5     4-16      100M */
        FREQ_BAND_50_200        /*  >=10    5-20      100M */
    };
    FreqBand freq_band(void);
    bool set_freq_band(FreqBand band, bool reflesh = false);

    bool video_filter(void);         /* 视频滤波 */
    bool enable_video_filter(bool flag, bool reflesh = false);

    enum RectifierType {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE
    };
    Group::RectifierType rectifier(void);
    bool set_rectifier(Group::RectifierType type, bool reflesh = false);

    int compress_rato(void);
    bool set_compress_rato(int val, bool reflesh = false);

    /**
     * @brief gain  获取增益
     * @return      返回增益值， 单位(dB)
     */
    float gain(void);

    /**
     * @brief set_gain  设置增益
     * @param gain      增益值
     * @param reflesh   下发FPGA配置
     * @return          成功返回true， 失败返回false
     */
    bool set_gain(float gain, bool reflesh = false);

    int thickness_factor(void);
    bool set_thickness_factor(int factor, bool reflesh = false);

    bool ut1(void);
    bool enable_ut1(bool flag, bool reflesh = false);

    bool ut2(void);
    bool enable_ut2(bool flag, bool reflesh = false);

    bool pa(void);
    bool enable_pa(bool flag, bool reflesh = false);

    int sum_gain(void);
    bool set_sum_gain(int gain, bool reflesh = false);

    int sample_range(void);
    bool set_sample_range(int range, bool reflesh = false);

    int point_qty(void);
    bool set_point_qty(int qty, bool reflesh = false);

    int tcg_point_qty(void);
    bool set_tcg_point_qty(int qty, bool reflesh = false);

    bool tcg(void);
    bool enable_tcg(bool flag, bool reflesh = false);

    int idel_time(void);
    bool set_idel_time(int val, bool reflesh = false);

    int gate_a_height(void);
    bool set_gate_a_height(int val, bool reflesh = false);

    int gate_a_logic(void);
    bool set_gate_a_logic(int val, bool reflesh = false);

    int gate_b_height(void);
    bool set_gate_b_height(int val, bool reflesh = false);

    int gate_b_logic(void);
    bool set_gate_b_logic(int val, bool reflesh = false);

    int gate_i_height(void);
    bool set_gate_i_height(int val, bool reflesh = false);

    int gate_i_logic(void);
    bool set_gate_i_logic(int val, bool reflesh = false);

    int thickness_min(void);
    bool set_thickness_min(int val, bool reflesh = false);

    int reject(void);
    bool set_reject(int val, bool reflesh = false);


    int average(void);
    bool set_average(int val, bool reflesh = false);

    int thickness_max(void);
    bool set_thickness_max(int val, bool reflesh = false);

    int thickness_source(void);
    bool set_thickness_source(int val, bool reflesh = false);

    int tx_end(void);
    bool set_tx_end(int val, bool reflesh = false);

    int tx_start(void);
    bool set_tx_start(int val, bool reflesh = false);

    void init();
    bool reflesh(void);

protected:
    /**
     * @brief sample_start  获取采样起点
     * @return              返回采样起点值，单位(ns)
     */
    int sample_start(void);

    /**
     * @brief set_sample_start  设置采样起点
     * @param val               采样起点值，单位(ns)
     * @param reflesh           下发配置标志
     * @return                  成功返回true，否则返回false
     */
    bool set_sample_start(int val, bool reflesh = false);

    /**
     * @brief rx_time   获取接收工作时间
     * @return          接收工作时间，单位(ns)
     */
    int rx_time(void);

    /**
     * @brief set_rx_time   设置接收工作时间
     * @param val           时间，单位(ns)
     * @param reflesh       下发配置标志
     * @return              成功返回true，失败返回false
     */
    bool set_rx_time(int val, bool reflesh = false);

private:
    GroupPrivate *d;
    QReadWriteLock m_rwlock;
};

}
#endif // __GROUP_H__
