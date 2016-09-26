#ifndef __BEAM_H__
#define __BEAM_H__

#include <QObject>

class Beam
{
public:
    explicit Beam(const int index=0) : m_index(index) {}
    virtual ~Beam() {}

    int index(void) const { return m_index; }
    void set_index(const int index) { m_index = index; }

    virtual quint32 gain_offset(void) const = 0;
    virtual void set_gain_offset(quint32 offset) = 0;

    virtual quint32 group_id(void) const = 0;
    virtual void set_group_id(quint32 id) = 0;

    virtual quint32 info(void) const = 0;
    virtual void set_info(quint32 info) = 0;

    virtual quint32 delay(void) const = 0;
    virtual void set_delay(quint32 delay) = 0;

    virtual quint32 gate_a_start(void) const = 0;
    virtual void set_gate_a_start(quint32 val) = 0;

    virtual quint32 gate_a_end(void) const = 0;
    virtual void set_gate_a_end(quint32 val) = 0;

    virtual quint32 gate_b_start(void) const = 0;
    virtual void set_gate_b_start(quint32 val) = 0;

    virtual quint32 gate_b_end(void) const = 0;
    virtual void set_gate_b_end(quint32 val) = 0;

    virtual quint32 gate_i_start(void) const = 0;
    virtual void set_gate_i_start(quint32 val) = 0;

    virtual quint32 gate_i_end(void) const = 0;
    virtual void set_gate_i_end(quint32 val) = 0;

    virtual quint32 tx(void) const = 0;
    virtual void set_tx(quint32 val) = 0;

    virtual quint32 rx(void) const = 0;
    virtual void set_rx(quint32 val) = 0;

    virtual u_int64_t rx_sel(void) const = 0;
    virtual void set_rx_sel(u_int64_t val) = 0;

    virtual u_int64_t tx_sel(void) const = 0;
    virtual void set_tx_sel(u_int64_t val) = 0;

    virtual quint32 tx_delay(quint32 channel) const = 0;
    virtual void set_tx_delay(quint32 channel, quint32 val) = 0;

    virtual quint32 rx_delay(quint32 channel) const = 0;
    virtual void set_rx_delay(quint32 channel, quint32 val) = 0;

    virtual quint32 tcg_position(quint32 point) const = 0;
    virtual void set_tcg_position(quint32 poing, quint32 val) = 0;

    virtual quint32 tcg_slope(quint32 point) const = 0;
    virtual void set_tcg_slope(quint32 point, quint32 val)  = 0;

    virtual quint32 tcg_flag(quint32 point) const = 0;
    virtual void set_tcg_flag(quint32 point, quint32 val) = 0;

    virtual bool refresh () = 0;

private:
    int m_index;
};

#endif // __BEAM_H__
