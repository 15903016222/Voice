/**
 * @file group.cpp
 * @brief Group
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#include "group.h"
#include "fpga_spi.h"

#include <string.h>

static const int GROUP_REGS_NUM = 16;

struct GroupData {
    /* s_group_reg (-1) */
    quint32 offset              :16;/* bit:0-15     地址的偏移 */
    quint32 res0                :12;/* bit:16-27    保留 */
    quint32 chip                :4; /* bit:28-31    片选Group取值0010 */

    /* s_group_reg (0) */
    quint32 freqBand            :4; /* bit:0-3      频带选择 */
    quint32 videoFilter         :1; /* bit:4        视频滤波 */
    quint32 rectifier           :2; /* bit:5-6      检波方式 */
    quint32 compressRato        :12;/* bit:7-18     压缩比 */
    quint32 res1                :2; /* bit:19-20    保留位 */
    quint32 gain                :11;/* bit:21-31    Gain, 0.1 dB */

    /* s_group_reg (1) */
    quint32 thicknessFactor     :24;/* bit:0-23 (2^24) / (thickness_max - thickness_min) 厚度差, 单位mm */
    quint32 res2                :5; /* bit:24-28    保留位 */
    quint32 ut1                 :1; /* bit:29       UT1使能位 */
    quint32 ut2                 :1; /* bit:30       UT2使能位 */
    quint32 pa                  :1; /* bit:31       PA使能位 */

    /* s_group_reg (2) */
    quint32 sumGain             :12;/* bit:0-11     Sum gain */
    quint32 sampleRange         :20;/* bit:12-31    采样范围 */

    /* s_group_reg (3) */
    quint32 pointQty            :16;/* bit:0-15     聚焦法则数量 */
    quint32 tcgPointQty         :8; /* bit:16-23    TCG点个数 */
    quint32 tcg                 :1; /* bit:24       TCG使能  */
    quint32 res3                :7; /* bit:25-31    保留位 */

    /* s_group_reg (4) */
    quint32 rxTime              :20;/* bit:0-19     rx_time */
    quint32 res4                :2; /* bit:20-21    保留位*/
    quint32 gain1               :10;/* bit:22-31    gain1 */

    /* s_group_reg (5) */
    quint32 idelTime            :27;/* bit:0-26     idel time  */
    quint32 res5                :5; /* bit:27-31    保留位 */

    /* s_group_reg (6) */
    quint32 gateAHeight         :12;/* bit:0-11     闸门A 高度 */
    quint32 res6                :20;/* bit:12-31    保留位 */

    /* s_group_reg (7) */
    quint32 gateALogic          :8; /* bit:0-7      闸门A 逻辑 */
    quint32 res7                :24;/* bit:8-31     保留位 */

    /* s_group_reg (8) */
    quint32 gatebHeight         :12;/* bit:0-11     闸门B 高度 */
    quint32 res8                :20;/* bit:12-31    保留位 */

    /* s_group_reg (9) */
    quint32 gateBLogic          :8; /* bit:0-7      闸门B 逻辑 */
    quint32 res9                :24;/* bit:8-31     保留位 */

    /* s_group_reg (10) */
    quint32 gateIHeight         :12;/* bit:0-11     闸门C 高度 */
    quint32 res10               :20;/* bit:12-31    保留位 */

    /* s_group_reg (11) */
    quint32 gateILogic          :8; /* bit:0-7      闸门C 逻辑 */
    quint32 res11               :24;/* bit:8-31     保留位 */

    /* s_group_reg (12) */
    quint32 thicknessMin        :20;/* bit:0-19     测量厚度最小值 */
    quint32 reject              :12;/* bit:20-31    抑制 */

    /* s_group_reg (13) */
    quint32 sampleStart         :21;/* bit:0-20     采样起点 */
    quint32 res12               :8; /* bit:21-28    保留位 */
    quint32 average             :3; /* bit:29-31    求平均 */

    /* s_group_reg  (14)*/
    quint32 thicknessMax        :20;/* bit:0-19     测量厚度最大值 */
    quint32 res13               :8; /* bit:20-27    保留位 */
    quint32 thicknessSource     :4; /* bit:28-31    输出 TTL 模拟电压的条件源 */

    /* s_group_reg  (15)*/
    quint32 txEnd               :14;/* bit:0-13     UT tx end */
    quint32 res14               :2; /* bit:14-15    保留位 */
    quint32 txStart             :14;/* bit:16-29    UT tx start */
    quint32 res15               :2; /* bit:30-31    保留位 */
};

static bool write_reg(GroupData *d, int index, int reg);

Group::Group(const int index)
    : m_index(index), d(new GroupData())
{
    ::memset(d, 0, sizeof(GroupData));
    d->chip = 0b0010;
    d->gain = 1;
    d->sumGain = d->gain;
}

Group::~Group()
{
    delete d;
}

Group::FreqBand Group::freq_band(void)
{
    QReadLocker l(&m_rwlock);
    return (Group::FreqBand)d->freqBand;
}

bool Group::set_freq_band(Group::FreqBand band, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->freqBand = band;
    return (reflesh ? write_reg(d, m_index, 0) : true);
}

bool Group::video_filter(void)
{
    QReadLocker l(&m_rwlock);
    return !!d->videoFilter;
}

bool Group::enable_video_filter(bool flag, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->videoFilter = flag;
    return (reflesh ? write_reg(d, m_index, 0) : true);
}

Group::RectifierType Group::rectifier(void)
{
    QReadLocker l(&m_rwlock);
    return (Group::RectifierType)d->rectifier;
}

bool Group::set_rectifier(Group::RectifierType type, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->rectifier = type;
    return (reflesh ? write_reg(d, m_index, 0) : true);
}

int Group::compress_rato(void)
{
    QReadLocker l(&m_rwlock);
    return d->compressRato;
}

bool Group::set_compress_rato(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->compressRato = val;
    return (reflesh ? write_reg(d, m_index, 0) : true);
}

float Group::gain(void)
{
    QReadLocker l(&m_rwlock);
    return (float)(d->gain/(10.0));
}

bool Group::set_gain(float gain, bool reflesh)
{
    if (gain < 0) {
        return false;
    }
    QWriteLocker l(&m_rwlock);
    d->gain = (quint32)(gain*10);
    return (reflesh ? write_reg(d, m_index, 0) : true);
}

int Group::thickness_factor(void)
{
    QReadLocker l(&m_rwlock);
    return d->thicknessFactor;
}

bool Group::set_thickness_factor(int factor, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->thicknessFactor = factor;
    return (reflesh ? write_reg(d, m_index, 1) : true);
}

bool Group::ut1(void)
{
    QReadLocker l(&m_rwlock);
    return d->ut1;
}

bool Group::enable_ut1(bool flag, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->ut1 = flag;
    return (reflesh ? write_reg(d, m_index, 1) : true);
}

bool Group::ut2(void)
{
    QReadLocker l(&m_rwlock);
    return d->ut2;
}

bool Group::enable_ut2(bool flag, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->ut2 = flag;
    return (reflesh ? write_reg(d, m_index, 1) : true);
}

bool Group::pa(void)
{
    QReadLocker l(&m_rwlock);
    return d->pa;
}

bool Group::enable_pa(bool flag, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->pa = flag;
    return (reflesh ? write_reg(d, m_index, 1) : true);
}

int Group::sum_gain(void)
{
    QReadLocker l(&m_rwlock);
    return d->sumGain;
}

bool Group::set_sum_gain(int gain, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->sumGain = gain;
    return (reflesh ? write_reg(d, m_index, 2) : true);
}

int Group::sample_range(void)
{
    QReadLocker l(&m_rwlock);
    return d->sampleRange;
}

bool Group::set_sample_range(int range, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->sampleRange = range;
    return (reflesh ? write_reg(d, m_index, 2) : true);
}

int Group::point_qty(void)
{
    QReadLocker l(&m_rwlock);
    return d->pointQty;
}

bool Group::set_point_qty(int qty, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->pointQty = qty;
    return (reflesh ? write_reg(d, m_index, 3) : true);
}

int Group::tcg_point_qty(void)
{
    QReadLocker l(&m_rwlock);
    return d->tcgPointQty;
}

bool Group::set_tcg_point_qty(int qty, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->tcgPointQty = qty;
    return (reflesh ? write_reg(d, m_index, 3) : true);
}

bool Group::tcg(void)
{
    QReadLocker l(&m_rwlock);
    return (!!d->tcg);
}

bool Group::enable_tcg(bool flag, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->tcg = flag;
    return (reflesh ? write_reg(d, m_index, 3) : true);
}

int Group::rx_time(void)
{
    QReadLocker l(&m_rwlock);
    return d->rxTime;
}

bool Group::set_rx_time(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->rxTime = val;
    return (reflesh ? write_reg(d, m_index, 4) : true);
}

int Group::idel_time(void)
{
    QReadLocker l(&m_rwlock);
    return d->idelTime;
}

bool Group::set_idel_time(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->idelTime = val;
    return (reflesh ? write_reg(d, m_index, 5) : true);
}

int Group::gate_a_height(void)
{
    QReadLocker l(&m_rwlock);
    return d->gateAHeight;
}

bool Group::set_gate_a_height(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->gateAHeight = val;
    return (reflesh ? write_reg(d, m_index, 6) : true);
}

int Group::gate_a_logic(void)
{
    QReadLocker l(&m_rwlock);
    return d->gateALogic;
}

bool Group::set_gate_a_logic(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->gateALogic = val;
    return (reflesh ? write_reg(d, m_index, 7) : true);
}

int Group::gate_b_height(void)
{
    QReadLocker l(&m_rwlock);
    return d->gatebHeight;
}

bool Group::set_gate_b_height(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->gatebHeight = val;
    return (reflesh ? write_reg(d, m_index, 8) : true);
}

int Group::gate_b_logic(void)
{
    QReadLocker l(&m_rwlock);
    return d->gateBLogic;
}

bool Group::set_gate_b_logic(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->gateBLogic = val;
    return (reflesh ? write_reg(d, m_index, 9) : true);
}

int Group::gate_i_height()
{
    QReadLocker l(&m_rwlock);
    return d->gateIHeight;
}

bool Group::set_gate_i_height(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->gateIHeight = val;
    return (reflesh ? write_reg(d, m_index, 10) : true);
}

int Group::gate_i_logic()
{
    QReadLocker l(&m_rwlock);
    return d->gateILogic;
}

bool Group::set_gate_i_logic(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->gateILogic = val;
    return (reflesh ? write_reg(d, m_index, 11) : true);
}

int Group::thickness_min(void)
{
    QReadLocker l(&m_rwlock);
    return d->thicknessMin;
}

bool Group::set_thickness_min(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->thicknessMin = val;
    return (reflesh ? write_reg(d, m_index, 12) : true);
}

int Group::reject(void)
{
    QReadLocker l(&m_rwlock);
    return d->reject;
}

bool Group::set_reject(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->reject = val;
    return (reflesh ? write_reg(d, m_index, 12) : true);
}

int Group::sample_start(void)
{
    QReadLocker l(&m_rwlock);
    return d->sampleStart;
}

bool Group::set_sample_start(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->sampleStart = val;
    return (reflesh ? write_reg(d, m_index, 13) : true);
}

int Group::average(void)
{
    QReadLocker l(&m_rwlock);
    return d->average;
}

bool Group::set_average(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->average = val;
    return (reflesh ? write_reg(d, m_index, 13) : true);
}

int Group::thickness_max(void)
{
    QReadLocker l(&m_rwlock);
    return d->thicknessMax;
}

bool Group::set_thickness_max(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->thicknessMax = val;
    return (reflesh ? write_reg(d, m_index, 14) : true);
}

int Group::thickness_source(void)
{
    QReadLocker l(&m_rwlock);
    return d->thicknessSource;
}

bool Group::set_thickness_source(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->thicknessSource = val;
    return (reflesh ? write_reg(d, m_index, 14) : true);
}

int Group::tx_end(void)
{
    QReadLocker l(&m_rwlock);
    return d->txEnd;
}

bool Group::set_tx_end(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->txEnd = val;
    return (reflesh ? write_reg(d, m_index, 15) : true);
}

int Group::tx_start(void)
{
    QReadLocker l(&m_rwlock);
    return d->txStart;
}

bool Group::set_tx_start(int val, bool reflesh)
{
    QWriteLocker l(&m_rwlock);
    d->txStart = val;
    return (reflesh ? write_reg(d, m_index, 15) : true);
}

bool Group::reflesh(void)
{
    FpgaSpi *spi = FpgaSpi::get_spi();
    if (spi == NULL) {
        return false;
    }
    d->offset = GROUP_REGS_NUM * m_index;

    QReadLocker l(&m_rwlock);
    return spi->send((char *)d, sizeof(GroupData));
}

bool write_reg(GroupData *d, int index, int reg)
{
    FpgaSpi *spi = FpgaSpi::get_spi();
    if (reg >= GROUP_REGS_NUM
            || spi == NULL) {
        return false;
    }

    d->offset = (GROUP_REGS_NUM * index) + reg;

    quint32 data[2] = {0};
    quint32 *dp = (quint32 *)d;
    data[0] = dp[0];
    data[1] = dp[reg+1];

    return spi->send((char *)data, 8);
}
