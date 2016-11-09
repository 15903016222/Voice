/**
 * @file beam.h
 * @brief Beam Class (Focal Law)
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#ifndef __BEAM_H__
#define __BEAM_H__

#include <QObject>

struct BeamData;

class Beam
{
public:
    static const quint32 MAX_CHANNELS;
    static const quint32 MAX_POINTS;

    explicit Beam(const int index=0);
    ~Beam();

    int index(void) const { return m_index; }
    void set_index(const int index) { m_index = index; }

    quint32 gain_offset(void) const;
    void set_gain_offset(quint32 offset);

    quint32 group_id(void) const;
    void set_group_id(quint32 id);

    quint32 info(void) const;
    void set_info(quint32 info);

    quint32 delay(void) const;
    void set_delay(quint32 delay);

    quint32 gate_a_start(void) const;
    void set_gate_a_start(quint32 val);

    quint32 gate_a_end(void) const;
    void set_gate_a_end(quint32 val);

    quint32 gate_b_start(void) const;
    void set_gate_b_start(quint32 val);

    quint32 gate_b_end(void) const;
    void set_gate_b_end(quint32 val);

    quint32 gate_i_start(void) const;
    void set_gate_i_start(quint32 val);

    quint32 gate_i_end(void) const;
    void set_gate_i_end(quint32 val);

    quint32 tx_channel(void) const;
    void set_tx_channel(quint32 val);

    quint32 rx_channel(void) const;
    void set_rx_channel(quint32 val);

    quint8 rx_channel_select(void) const;
    bool set_rx_channel_select(quint8 n);

    quint8 tx_channel_select(void) const;
    bool set_tx_channel_select(quint8 n);

    quint32 tx_delay(quint32 channel) const;
    bool set_tx_delay(quint32 channel, quint32 val);

    quint32 rx_delay(quint32 channel) const;
    bool set_rx_delay(quint32 channel, quint32 val);

    /**
     * @brief tcg_position 返回对应TCG点的位置
     * @param point        指定TCG点,最大点数为 MAX_POINTS-1
     * @return             成功返回指定点的位置,单位为10ns
     */
    quint32 tcg_position(quint32 point) const;
    bool set_tcg_position(quint32 poing, quint32 val);

    quint32 tcg_slope(quint32 point) const;
    bool set_tcg_slope(quint32 point, quint32 val) ;

    bool tcg_flag(quint32 point) const;
    bool set_tcg_flag(quint32 point, bool flag);

    bool refresh(void);

private:
    int m_index;
    BeamData *d;
};

#endif // __BEAM_H__
