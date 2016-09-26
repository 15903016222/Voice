#ifndef __PHASCAN_BEAM_H__
#define __PHASCAN_BEAM_H__

#include "beam.h"
#include "fpga.h"

struct DelayInfo
{
     quint32 tx_time  :14;
     quint32 res1     :2;
     quint32 rx_time  :12 ;
     quint32 res2     :4;
};

struct PointInfo
{
    /* TCG_SPI (0) */
     quint32 position :20;
     quint32 res1     :1;
     quint32 pregain  :10;
     quint32 res2     :1;
     quint32 slope    :22;
     quint32 res3     :9;
     quint32 flag     :1;
};

struct BeamData
{
    /* reg (-1) 地址 */
    quint32 offset        :16;    /* bit:0-15 地址的偏移 */
    quint32 res           :12;    /* bit:16-27 保留*/
    quint32 addr          :4;     /* bit:28-31 片选 Group取值0010 */

    /* reg (0) 地址 */
    quint32 res1          :2;     /* bit:0-1 保留 */
    quint32 gainOffset    :10;    /* bit:2-11 增益补偿单位0.1dB */
    quint32 res2          :3;     /* bit:12-14 保留 */
    quint32 group         :5;     /* bit:15-19 groupId */
    quint32 info   :12;    /* bit:19-31 beam_qty */

    /* reg (1) 地址 */
    quint32 beamDelay     :16;    /* bit:0-15 16 单位10ns */
    quint32 res3          :16;    /* bit 16-31 保留*/

    /* reg (2) 地址 */
    quint32 gateAStart    :20;    /* bit:0-19  单位10ns */
    quint32 res4          :12;    /* bit 20-31 保留*/

    /* reg (3) 地址 */
    quint32 gateAEnd      :20;    /* bit:0-19  单位10ns */
    quint32 res5          :12;    /* bit 20-31 保留*/

    /* reg (4) 地址 */
    quint32 gateBStart    :20;    /* bit:0-19  单位10ns */
    quint32 res6          :12;    /* bit 20-31 保留*/

    /* reg (5) 地址 */
    quint32 gateBEnd      :20;    /* bit:0-19  单位10ns */
    quint32 res7          :12;    /* bit 20-31 保留*/

    /* reg (6) 地址 */
    quint32 gateIStart    :20;    /* bit:0-19  单位10ns */
    quint32 res8          :12;    /* bit 20-31 保留*/

    /* reg (7) 地址 */
    quint32 gateIEnd      :20;    /* bit:0-19  单位10ns */
    quint32 res9          :12;    /* bit 20-31 保留*/

    /* reg (8-9) 地址 */
    quint32 res10[2];

    quint32 txEnable;
    quint32 rxEnable;

    /* reg (12-13) 地址 接收使能 */
    u_int64_t rxSel;

    /* reg (14-15) 地址 发射使能 */
    u_int64_t txSel;

    /* reg (16-47) 地址 阵元发射信息 */
    DelayInfo delay[32];            /* bit0-13 发射延时 bit:16-27 接收延时*/
    PointInfo pointInfo[16] ;
};

class PhascanBeam : public Beam
{
public:
    explicit PhascanBeam(const int index = 0);

    quint32 gain_offset(void) const { return d.gainOffset; }
    void set_gain_offset(quint32 offset) { d.offset = offset; }

    quint32 group_id(void) const { return d.group; }
    void set_group_id(quint32 id) { d.group = id; }

    quint32 info(void) const { return d.info; }
    void set_info(quint32 info) { d.info = info; }

    quint32 delay(void) const { return d.beamDelay; }
    void set_delay(quint32 delay) { d.beamDelay = delay; }

    quint32 gate_a_start(void) const { return d.gateAStart; }
    void set_gate_a_start(quint32 val)  { d.gateAStart = val; }

    quint32 gate_a_end(void) const { return d.gateAEnd; }
    void set_gate_a_end(quint32 val) { d.gateAEnd = val; }

    quint32 gate_b_start(void) const { return d.gateBStart; }
    void set_gate_b_start(quint32 val) { d.gateBStart = val; }

    quint32 gate_b_end(void) const { return d.gateBStart; }
    void set_gate_b_end(quint32 val) { d.gateBEnd = val; }

    quint32 gate_i_start(void) const { return d.gateIStart; }
    void set_gate_i_start(quint32 val) { d.gateIStart = val; }

    quint32 gate_i_end(void) const { return d.gateIEnd; }
    void set_gate_i_end(quint32 val) { d.gateIEnd = val; }

    quint32 tx(void) const { return d.txEnable; }
    void set_tx(quint32 val) { d.txEnable = val; }

    quint32 rx(void) const { return d.rxEnable; }
    void set_rx(quint32 val) { d.rxEnable = val; }

    u_int64_t rx_sel(void) const { return d.rxSel; }
    void set_rx_sel(u_int64_t val) { d.rxSel = val; }

    u_int64_t tx_sel(void) const { return d.txSel; }
    void set_tx_sel(u_int64_t val) { d.txSel = val; }

    quint32 tx_delay(quint32 channel) const { return d.delay[channel].tx_time; }
    void set_tx_delay(quint32 channel, quint32 val) { d.delay[channel].tx_time = val; }

    quint32 rx_delay(quint32 channel) const { return d.delay[channel].rx_time; }
    void set_rx_delay(quint32 channel, quint32 val) { d.delay[channel].rx_time = val; }

    quint32 tcg_position(quint32 point) const { return d.pointInfo[point].position; }
    void set_tcg_position(quint32 point, quint32 val) { d.pointInfo[point].position = val; }

    quint32 tcg_slope(quint32 point) const { return d.pointInfo[point].slope; }
    void set_tcg_slope(quint32 point, quint32 val) { d.pointInfo[point].slope = val; }

    quint32 tcg_flag(quint32 point) const { return d.pointInfo[point].flag; }
    void set_tcg_flag(quint32 point, quint32 val) { d.pointInfo[point].flag = val; }

    bool refresh(void) { return m_fpga->send((char *)&d, sizeof(BeamData)); }

private:
    BeamData d;
    Fpga *m_fpga;
};

#endif // __PHASCAN_BEAM_H__
