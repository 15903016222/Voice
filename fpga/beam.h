/**
 * @file beam.h
 * @brief Beam Class (Focal Law)
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#ifndef __BEAM_H__
#define __BEAM_H__

#include "fpga_global.h"
#include <QObject>

namespace DplFpga {

struct BeamRegs;

class BeamPrivate;
class FPGASHARED_EXPORT Beam
{
    Q_DECLARE_PRIVATE(Beam)
public:
    /**
     * @brief MAX_CHANNELS  通道总数
     */
    static const uint MAX_CHANNELS;

    /**
     * @brief MAX_ELEMENTS  一次激发的最大阵元数
     */
    static const uint MAX_ELEMENTS;

    explicit Beam(int index=0);
    ~Beam();

    /**
     * @brief index 获取序号
     * @return      序号,从0开始
     */
    int index() const;

    /**
     * @brief set_index 设置序号
     * @param index     序号，从0开始
     */
    void set_index(int index);

    /**
     * @brief gain_compensation     获取增益补偿
     * @return                      补偿值(0.1dB)
     */
    quint32 gain_compensation(void) const;

    /**
     * @brief set_gain_compensation 设置增益补偿
     * @param offset                补偿值(0.1dB)
     */
    void set_gain_compensation(quint32 value);

    /**
     * @brief group_id  获取组ID
     * @return          组ID号
     */
    quint32 group_id(void) const;

    /**
     * @brief set_group_id  设置组ID
     * @param id            组ID号
     */
    void set_group_id(quint32 id);

    /**
     * @brief total_beam_qty    获取总共的Beam数
     * @return                  数量
     */
    quint32 total_beam_qty(void) const;

    /**
     * @brief set_total_beam_qty    设置总共的Beam数
     * @param qty                   数量
     */
    void set_total_beam_qty(quint32 qty);

    /**
     * @brief delay 获取声速延迟时间
     * @return      时间(采样精度)
     */
    quint32 delay(void) const;

    /**
     * @brief set_delay 设置声速延迟时间
     * @param delay     时间(采样精度)
     */
    void set_delay(quint32 delay);

    /**
     * @brief gate_a_start  获取闸门A起点
     * @return              位置(采样精度)
     */
    quint32 gate_a_start(void) const;

    /**
     * @brief gate_a_width  获取闸门A宽度
     * @return              宽度(采样精度)
     */
    quint32 gate_a_width(void) const;

    /**
     * @brief set_gate_a    设置闸门A
     * @param start         起点位置(采样精度)
     * @param width         宽度(采样精度)
     */
    void set_gate_a(quint32 start, quint32 width);

    /**
     * @brief gate_b_start  获取闸门B起点
     * @return              位置(采样精度)
     */
    quint32 gate_b_start(void) const;

    /**
     * @brief gate_b_width  获取闸门B宽度
     * @return              宽度(采样精度)
     */
    quint32 gate_b_width(void) const;

    /**
     * @brief set_gate_b    设置闸门B
     * @param start         起点位置(采样精度)
     * @param width         宽度(采样精度)
     */
    void set_gate_b(quint32 start, quint32 width);

    /**
     * @brief gate_i_start  获取闸门I起点
     * @return              位置(采样精度)
     */
    quint32 gate_i_start(void) const;

    /**
     * @brief gate_i_width  获取闸门I宽度
     * @return              宽度(采样精度)
     */
    quint32 gate_i_width(void) const;

    /**
     * @brief set_gate_i    设置闸门I
     * @param start         起点位置(采样精度)
     * @param width         宽度(采样精度)
     */
    void set_gate_i(quint32 start, quint32 width);

    /**
     * @brief rx_channel_select 获取起始接收通道索引号
     * @return                  索引号(0 ~ MAX_CHANNELS-MAX_ELEMENETS)
     */
    uint rx_channel_select(void) const;

    /**
     * @brief set_rx_channel        设置接收通道选择
     * @param start                 起始通道索引号(0 ~ MAX_CHANNELS-MAX_ELEMENETS)
     * @param num                   激活的通道数
     * @return                      设置成功返回true，否则返回false
     */
    bool set_rx_channel(uint start, uint num);

    /**
     * @brief tx_channel_select 获取起始发射通道索引号
     * @return                  索引号(0 ~ MAX_CHANNELS-MAX_ELEMENETS)
     */
    uint tx_channel_select(void) const;

    /**
     * @brief set_tx_channel        设置起始发射通道索引号
     * @param start                 索引号(0 ~ MAX_CHANNELS-MAX_ELEMENETS)
     * @param num                   激活的通道数
     * @return                      设置成功返回true，否则返回false
     */
    bool set_tx_channel(uint start, uint num);

    /**
     * @brief set_tx_delay  设置指定通道的发送延迟
     * @param channel       通道号(0 ~ MAX_CHANNELS)
     * @param val           延迟时间(ns)
     * @return              成功返回true，失败返回false
     */
    bool set_tx_delay(uint channel, quint32 val);

    /**
     * @brief set_rx_delay  设置指定通道的接收延迟时间
     * @param channel       通道号(0 ~ MAX_CHANNELS)
     * @param val           延迟时间(ns)
     * @return              成功返回true，否则为false
     */
    bool set_rx_delay(uint channel, quint32 val);

    /**
     * @brief refresh   下发配置
     * @return          成功返回true，否则false
     */
    bool refresh(void);

    /**
     * @brief show_info 显示信息
     */
    void show_info() const;

private:
    BeamPrivate *d_ptr;
};

}

#endif // __BEAM_H__
