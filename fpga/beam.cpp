/**
 * @file beam.cpp
 * @brief Beam Class (Focal law)
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#include "beam.h"
#include "fpga_spi.h"

static const int BEAM_REGS_NUM      = 80;
const quint32 Beam::MAX_CHANNELS    = 32;

struct DelayInfo
{
     quint32 txTime :14;        /* bit:0-13     发送延迟*/
     quint32 res1   :2;         /* bit:14-15    保留 */
     quint32 rxTime :12;        /* bit:16-27    接收延迟*/
     quint32 res2   :4;         /* bit:28-31    保留 */
};

#pragma pack(4)
struct BeamData
{
    /* reg (-1) */
    quint32 offset        :16;    /* bit:0-15 地址的偏移 */
    quint32 res           :12;    /* bit:16-27 保留*/
    quint32 chip          :4;     /* bit:28-31 片选 Group取值0010 */

    /* reg (0) */
    quint32 res1          :2;     /* bit:0-1 保留 */
    quint32 gainOffset    :10;    /* bit:2-11 增益补偿单位0.1dB */
    quint32 res2          :3;     /* bit:12-14 保留 */
    quint32 group         :5;     /* bit:15-19 groupId */
    quint32 info          :12;    /* bit:19-31 beam_qty */

    /* reg (1) */
    quint32 beamDelay     :16;    /* bit:0-15 16 单位10ns */
    quint32 res3          :16;    /* bit:16-31 保留*/

    /* reg (2) */
    quint32 gateAStart    :20;    /* bit:0-19  单位10ns */
    quint32 res4          :12;    /* bit:20-31 保留*/

    /* reg (3) */
    quint32 gateAEnd      :20;    /* bit:0-19  单位10ns */
    quint32 res5          :12;    /* bit:20-31 保留*/

    /* reg (4) */
    quint32 gateBStart    :20;    /* bit:0-19  单位10ns */
    quint32 res6          :12;    /* bit:20-31 保留*/

    /* reg (5) */
    quint32 gateBEnd      :20;    /* bit:0-19  单位10ns */
    quint32 res7          :12;    /* bit:20-31 保留*/

    /* reg (6) */
    quint32 gateIStart    :20;    /* bit:0-19  单位10ns */
    quint32 res8          :12;    /* bit:20-31 保留*/

    /* reg (7) */
    quint32 gateIEnd      :20;    /* bit:0-19  单位10ns */
    quint32 res9          :12;    /* bit:20-31 保留*/

    /* reg (8-9) */
    quint32 res10[2];

    /* reg (10) */
    quint32 txEnable;

    /* reg (11) */
    quint32 rxEnable;

    /* reg (12-13) 接收使能 */
    quint64 rxChannelSel;

    /* reg (14-15) 发射使能 */
    quint64 txChannelSel;

    /* reg (16-47) 阵元发射信息 */
    DelayInfo delay[32];
}__attribute__((aligned(4)));
#pragma pack()

Beam::Beam(const int index)
    : m_index(index), d(new BeamData())
{
    ::memset(d, 0, sizeof(BeamData));
    d->chip = 0b0001;
    d->offset = BEAM_REGS_NUM * index;
}

Beam::~Beam()
{
    delete d;
}

quint32 Beam::gain_offset(void) const
{
    return d->gainOffset;
}

void Beam::set_gain_offset(quint32 offset)
{
    d->gainOffset = offset;
}

quint32 Beam::group_id(void) const
{
    return d->group;
}

void Beam::set_group_id(quint32 id)
{
    d->group = id;
}

quint32 Beam::info(void) const
{
    return d->info;
}

void Beam::set_info(quint32 info)
{
    d->info = info;
}

quint32 Beam::delay(void) const
{
    return d->beamDelay;
}

void Beam::set_delay(quint32 delay)
{
    d->beamDelay = delay;
}

quint32 Beam::gate_a_start(void) const
{
    return d->gateAStart;
}

void Beam::set_gate_a_start(quint32 val)
{
    d->gateAStart = val;
}

quint32 Beam::gate_a_end(void) const
{
    return d->gateAEnd;
}

void Beam::set_gate_a_end(quint32 val)
{
    d->gateAEnd = val;
}

quint32 Beam::gate_b_start(void) const
{
    return d->gateBStart;
}

void Beam::set_gate_b_start(quint32 val)
{
    d->gateBStart = val;
}

quint32 Beam::gate_b_end(void) const
{
    return d->gateBEnd;
}

void Beam::set_gate_b_end(quint32 val)
{
    d->gateBEnd = val;
}

quint32 Beam::gate_i_start(void) const
{
    return d->gateIStart;
}

void Beam::set_gate_i_start(quint32 val)
{
    d->gateIStart = val;
}

quint32 Beam::gate_i_end(void) const
{
    return d->gateIEnd;
}

void Beam::set_gate_i_end(quint32 val)
{
    d->gateIEnd = val;
}

quint32 Beam::tx_channel(void) const
{
    return d->txEnable;
}

void Beam::set_tx_channel(quint32 val)
{
    d->txEnable = val;
}

quint32 Beam::rx_channel(void) const
{
    return d->rxEnable;
}

void Beam::set_rx_channel(quint32 val)
{
    d->rxEnable = val;
}

static quint64 cal_rxtx_channel_start(quint8 n)
{
    quint64 ret = 0;
    if (n == 1) {
        return ret;
    }

    if ( n <= Beam::MAX_CHANNELS + 1 ) {
        /* 2 ~ 33 channels */
        for (int i = 0; i < n; ++i) {
            ret |= 0x1ULL<<(63-(i<<1));
        }
    } else if ( n <= (Beam::MAX_CHANNELS * 2 + 1) ) {
        /* 34 ~ 65 channels */
        ret = 0xAAAAAAAAAAAAAAAA; /* 0b101010....10 */
        n -= (Beam::MAX_CHANNELS + 1);
        for (int i = 0; i < n; ++i) {
            ret &= ~(0x1ULL<<(63-(i<<1)));
            ret |= 0x1ULL<<(62-(i<<1));
        }
    } else if ( n <= (Beam::MAX_CHANNELS * 2 + 1) ){
        /* 66 ~ 97 chanels */
        ret = 5555555555555555;
        n -= (Beam::MAX_CHANNELS * 3 + 1);
        for (int i = 0; i < n; ++i) {
            ret |= 0x1ULL<<(63-(i<<1));
        }
    }
    return ret;
}

quint8 Beam::rx_channel_select(void) const
{
    quint8 ret = 1;
    for (int i = 63; i > 0; i-=2) {
        ret += (d->rxChannelSel>>i)&0x1;
        ret += ((d->rxChannelSel>>(i-1))&0x1)*2;
    }
    return ret;
}

bool Beam::set_rx_channel_select(quint8 n)
{
    if (n == 0 || n > 97) {
        return false;
    }

    d->rxChannelSel = cal_rxtx_channel_start(n);
    qDebug("MAX_CHANNELS(%d) 0x%llx", Beam::MAX_CHANNELS, d->rxChannelSel);

    return true;
}

quint8 Beam::tx_channel_select(void) const
{
    quint8 ret = 1;
    for (int i = 63; i > 0; i-=2) {
        ret += (d->txChannelSel>>i)&0x1;
        ret += ((d->txChannelSel>>(i-1))&0x1)*2;
    }
    return ret;
}

bool Beam::set_tx_channel_select(quint8 n)
{
    if (n == 0 || n > 97) {
        return false;
    }

    d->txChannelSel = cal_rxtx_channel_start(n);

    return true;
}

quint32 Beam::tx_delay(quint32 channel) const
{
    if (channel >= Beam::MAX_CHANNELS) {
        return 0;
    }
    return d->delay[channel].txTime;
}

bool Beam::set_tx_delay(quint32 channel, quint32 val)
{
    if (channel >= Beam::MAX_CHANNELS) {
        return false;
    }
    d->delay[channel].txTime = val;
    return true;
}

quint32 Beam::rx_delay(quint32 channel) const
{
    if (channel >= Beam::MAX_CHANNELS) {
        return 0;
    }
    return d->delay[channel].rxTime;
}

bool Beam::set_rx_delay(quint32 channel, quint32 val)
{
    if (channel >= Beam::MAX_CHANNELS) {
        return false;
    }
    d->delay[channel].rxTime = val;
    return true;
}

bool Beam::refresh(void)
{
    FpgaSpi *spi = FpgaSpi::get_spi();
    if (spi == NULL) {
        return false;
    }
    return spi->send((char *)d, sizeof(BeamData));
}

