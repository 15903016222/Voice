#include "group.h"
#include "phascan_spi.h"

#define GROUP_REG_NUM   (16)

struct GroupData {
    /* s_group_reg (-1) 地址 */
    quint32 offset              :16;/* bit:0-15 地址的偏移 */
    quint32 res0                :12;/* bit:16-27 保留 */
    quint32 chip                :4; /* bit:28-31 片选Group取值0010 */

    /* s_group_reg (0) */
    quint32 freqBand            :4; /* bit:0-3 频带选择 */
    quint32 videoFilter         :1; /* bit:4   视频滤波 */
    quint32 rectifier           :2; /* bit:5-6 检波方式 */
    quint32 compressRato        :12;/* bit:7-18 压缩比 */
    quint32 res1                :2; /* bit:19-20 保留位 */
    quint32 gain                :11;/* bit:21-31 Gain, 0.1 dB */

    /* s_group_reg (1) */
    quint32 thicknessFactor     :24;/* bit:0-23 (2^24) / (thickness_max - thickness_min) 厚度差 */
    quint32 res2                :5; /* bit:24-28 保留位 */
    quint32 ut1                 :1; /* bit:29  UT1使能位 */
    quint32 ut2                 :1; /* bit:30 UT2使能位 */
    quint32 pa                  :1; /* bit:31 PA使能位 */

    /* s_group_reg (2) */
    quint32 sumGain             :12;/* bit:0-11 Sum gain */
    quint32 sampleRange         :20;/* bit:12-31 capture end 采样范围 */

    /* s_group_reg (3) */
    quint32 pointQty            :16;/* bit:0-15 聚焦法则数量 */
    quint32 tcgPointQty         :8; /* bit:16-23 TCG点个数 */
    quint32 tcg                 :1; /* bit:24   TCG使能  */
    quint32 res3                :7; /* bit:25-31 保留位 */

    /* s_group_reg (4) */
    quint32 rxTime              :20;/* bit:0-19 rx_time */
    quint32 res4                :2; /* bit:20-21 保留位*/
    quint32 gain1               :10;/* bit:22-31 gain1 */

    /* s_group_reg (5) */
    quint32 idelTime            :27;/* bit:0-26 idel time  */
    quint32 res5                :5; /* bit:27-31 保留位 */

    /* s_group_reg (6) */
    quint32 gateAHeight         :12;/* bit:0-11  闸门A 高度 */
    quint32 res6                :20;/* bit:12-31 保留位 */

    /* s_group_reg (7) */
    quint32 gateALogic          :8; /* bit:0-7 闸门A 逻辑 */
    quint32 res7                :24;/* bit:8-31 保留位 */

    /* s_group_reg (8) */
    quint32 gatebHeight         :12;/* bit:0-11 闸门B 高度 */
    quint32 res8                :20;/* bit:12-31 保留位 */

    /* s_group_reg (9) */
    quint32 gateBLogic          :8; /* bit:0-7 闸门B 逻辑 */
    quint32 res9                :24;/* bit:8-31 保留位 */

    /* s_group_reg (10) */
    quint32 gateIHeight         :12;/* bit:0-11 闸门C 高度 */
    quint32 res10               :20;/* bit:12-31 保留位 */

    /* s_group_reg (11) */
    quint32 gateILogic          :8; /* bit:0-7 闸门C 逻辑 */
    quint32 res11               :24;/* bit:8-31 保留位 */

    /* s_group_reg (12) */
    quint32 thicknessMin        :20;/* bit:0-19 */
    quint32 reject              :12;/* bit:20-31 闸门C 结束 */

    /* s_group_reg (13) */
    quint32 sampleStart         :21;/* bit:0-20 采样起点 */
    quint32 res12               :8; /* bit:21-28 保留位 */
    quint32 average             :3; /* bit:29-31 求平均 */

    /* s_group_reg  (14)*/
    quint32 thicknessMax        :20;/* bit:0-19 测量厚度最大值 */
    quint32 res13               :8; /* bit:20-27 保留位 */
    quint32 thicknessSource     :4; /* bit:28-31 输出 TTL 模拟电压的条件源 */

    /* s_group_reg  (15)*/
    quint32 txEnd               :14;/* bit:0-13  UT tx end */
    quint32 res14               :2; /* bit:14-15 保留位 */
    quint32 txStart             :14;/* bit:16-29 UT tx start */
    quint32 res15               :2; /* bit:30-31 保留位 */
};

static bool write_one_reg(GroupData *d, int index, int reg);

Group::Group(const int index)
    : m_index(index), d(new GroupData())
{
    d->chip = 0b0010;
}

Group::~Group()
{
    delete d;
}

int Group::freq_band(void) const
{
    return d->freqBand;
}

bool Group::set_freq_band(int band, bool reflesh)
{
    d->freqBand = band;
    return reflesh ? write_one_reg(d, m_index, 0) : true;
}

bool video_filter(void) const
{
    return !!d->videoFilter;
}

bool Group::enable_video_filter(bool flag, bool reflesh)
{
    d->videoFilter = flag;
    return reflesh ? write_one_reg(d, m_index, 0) : true;
}

Group::RectifierType Group::rectifier(void) const
{
    return d->rectifier;
}

bool Group::set_rectifier(Group::RectifierType type, bool reflesh)
{
    d->rectifier = type;
    return reflesh ? write_one_reg(d, m_index, 0) : true;
}

int Group::compress_rato(void) const
{
    return d->compressRato;
}

bool Group::set_compress_rato(int val, bool reflesh)
{
    d->compressRato = val;
    return reflesh ? write_one_reg(d, m_index, 0) : true;
}

int Group::gain(void) const
{
    return d->gain;
}

bool Group::set_gain(int gain, bool reflesh)
{
    d->gain = gain;
    return reflesh ? write_one_reg(d, m_index, 0) : true;
}

int Group::thickness_factor(void) const
{
    return d->thicknessFactor;
}

bool Group::set_thickness_factor(int factor, bool reflesh)
{
    d->thicknessFactor = factor;
    return reflesh ? write_one_reg(d, m_index, 1) : true;
}

bool Group::ut1(void) const
{
    return d->ut1;
}

bool Group::enable_ut1(bool flag, bool reflesh)
{
    d->ut1 = flag;
    return reflesh ? write_one_reg(d, m_index, 1) : true;
}

bool Group::ut2(void) const
{
    return d->ut2;
}

bool Group::enable_ut2(bool flag, bool reflesh)
{
    d->ut2 = flag;
    return reflesh ? write_one_reg(d, m_index, 1) : true;
}

bool Group::pa(void) const
{
    return d->pa;
}

bool Group::enable_pa(bool flag, bool reflesh)
{
    d->pa = flag;
    return reflesh ? write_one_reg(d, m_index, 1) : true;
}

int Group::sum_gain(void) const
{
    return d->sumGain;
}

bool Group::set_sum_gain(int gain, bool reflesh)
{
    d->sumGain = gain;
    return reflesh ? write_one_reg(d, m_index, 2) : true;
}

int Group::sample_range(void) const
{
    return d->sampleRange;
}

bool Group::set_sample_range(int range, bool reflesh)
{
    d->sampleRange = range;
    return reflesh ? write_one_reg(d, m_index, 2) : true;
}

int Group::point_qty(void) const
{
    return d->pointQty;
}

bool Group::set_point_qty(int qty, bool reflesh)
{
    d->pointQty = qty;
    return reflesh ? write_one_reg(d, m_index, 3) : true;
}

int Group::tcg_point_qty(void) const
{
    return d->tcgPointQty;
}

bool Group::set_tcg_point_qty(int qty, bool reflesh)
{
    d->tcgPointQty = qty;
    return reflesh ? write_one_reg(d, m_index, 3) : true;
}

bool tcg(void) const
{
    return (!!d->tcg);
}

bool Group::enable_tcg(bool flag, bool reflesh)
{
    d->tcg = flag;
    return reflesh ? write_one_reg(d, m_index, 3) : true;
}

int Group::rx_time(void) const
{
    return d->rxTime;
}

bool Group::set_rx_time(int val, bool reflesh)
{
    d->rxTime = val;
    return reflesh ? write_one_reg(d, m_index, 4) : true;
}

int Group::idel_time(void) const
{
    return d->idelTime;
}

bool Group::set_idel_time(int val, bool reflesh)
{
    d->idelTime = val;
    return reflesh ? write_one_reg(d, m_index, 5) : true;
}

int Group::gate_a_height(void) const
{
    return d->gateAHeight;
}

bool Group::set_gate_a_height(int val, bool reflesh)
{
    d->gateAHeight = val;
    return reflesh ? write_one_reg(d, m_index, 6) : true;
}

int Group::gate_a_logic(void) const
{
    return d->gateALogic;
}

bool Group::set_gate_a_logic(int val, bool reflesh)
{
    d->gateALogic = val;
    return reflesh ? write_one_reg(d, m_index, 7) : true;
}

int Group::gate_b_height(void) const
{
    return d->gatebHeight;
}

bool Group::set_gate_b_height(int val, bool reflesh)
{
    d->gatebHeight = val;
    return reflesh ? write_one_reg(d, m_index, 8) : true;
}

int Group::gate_b_logic(void) const
{
    return d->gateBLogic;
}

bool Group::set_gate_b_logic(int val, bool reflesh)
{
    d->gateBLogic = val;
    return reflesh ? write_one_reg(d, m_index, 9) : true;
}

int Group::gate_i_height() const
{
    return d->gateIHeight;
}

bool Group::set_gate_i_height(int val, bool reflesh)
{
    d->gateIHeight = val;
    return reflesh ? write_one_reg(d, m_index, 10) : true;
}

int Group::gate_i_logic() const
{
    return d->gateILogic;
}

bool Group::set_gate_i_logic(int val, bool reflesh)
{
    d->gateILogic = val;
    return reflesh ? write_one_reg(d, m_index, 11) : true;
}

int Group::thickness_min(void) const
{
    return d->thicknessMin;
}

bool Group::set_thickness_min(int val, bool reflesh)
{
    d->thicknessMin = val;
    return reflesh ? write_one_reg(d, m_index, 12) : true;
}

int Group::reject(void) const
{
    return d->reject;
}

bool Group::set_reject(int val, bool reflesh)
{
    d->reject = val;
    return reflesh ? write_one_reg(d, m_index, 12) : true;
}

int Group::sample_start(void) const
{
    return d->sampleStart;
}

bool Group::set_sample_start(int val, bool reflesh)
{
    d->sampleStart = val;
    return reflesh ? write_one_reg(d, m_index, 13) : true;
}

int Group::average(void) const
{
    return d->average;
}

bool Group::set_average(int val, bool reflesh)
{
    d->average = val;
    return reflesh ? write_one_reg(d, m_index, 13) : true;
}

int Group::thickness_max(void) const
{
    return d->thicknessMax;
}

bool Group::set_thickness_max(int val, bool reflesh)
{
    d->thicknessMax = val;
    return reflesh ? write_one_reg(d, m_index, 14) : true;
}

int Group::thickness_source(void) const
{
    return d->thicknessSource;
}

bool Group::set_thickness_source(int val, bool reflesh)
{
    d->thicknessSource = val;
    return reflesh ? write_one_reg(d, m_index, 14) : true;
}

int Group::tx_end(void) const
{
    return d->txEnd;
}

bool Group::set_tx_end(int val, bool reflesh)
{
    d->txEnd = val;
    return reflesh ? write_one_reg(d, m_index, 15) : true;
}

int Group::tx_start(void) const
{
    return d->txStart;
}

bool Group::set_tx_start(int val, bool reflesh)
{
    d->txStart = val;
    return reflesh ? write_one_reg(d, m_index, 15) : true;
}

bool Group::reflesh(void)
{
    PhascanSpi *spi = PhascanSpi::get_spi();
    if (spi == NULL) {
        return false;
    }
    d->offset = GROUP_REG_NUM * m_index;
    return spi->write((char *)d, sizeof(GroupData));
}

bool write_one_reg(GroupData *d, int index, int reg)
{
    PhascanSpi *spi = PhascanSpi::get_spi();
    if (reg >= GROUP_REG_NUM
            || spi == NULL) {
        return false;
    }

    d->offset = (GROUP_REG_NUM * index) + reg;

    quint32 data[2] = {0};
    quint32 *dp = &d;
    data[0] = dp[0];
    data[1] = dp[reg];
    return spi->write((char *)data, 8);
}
