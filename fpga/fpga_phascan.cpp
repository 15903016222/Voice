
#include "fpga.h"
#include "phascan_spi.h"
#include "gpio.h"

#include <QDebug>

static const int GLOBAL_REG_NUM = 32;

struct AlarmOutputData{
    /* reg 17 20 23 */
    quint32 count           :7; /* bit:0-6 */
    quint32 logicCondition2 :4; /* bit:7-10 报警条件2*/
    quint32 op              :1; /* bit:11 与或操作 */
    quint32 logicCondition1 :4; /* bit:12-15 报警条件1*/
    quint32 logicGroup      :16;/* bit:16-31使能的组 */

    /* reg 18 21 24 */
    quint32 delay           :20;/* bit:0-19 单位10us */
    quint32 res0            :12;/* bit:20-31 */

    /* reg 19 22 25 */
    quint32 holdTime        :20;/* bit:0-19 单位10us */
    quint32 res1            :12;/* bit:20-31 */
};

struct AlarmAnalogData{
    /* reg 26 27 */
    quint32 type            :3; /* bit:0-2 A% B%或thickness */
    quint32 logicGroup      :4; /* bit:3-6 源组 */
    quint32 res             :25;/* bit:7-31 */
};

struct GlobalData{
    /* reg (-1) */
    quint32 offset          :28;/* bit:0-27 地址的偏移 */
    quint32 chip            :4; /* bit:28-31 片选 Group取值1000 */

    /* reg (0) */
    quint32 paLawQty        :16;
    quint32 utLawQty        :16;

    /* reg (1) */
    quint32 encX            :4; /* bit:0-3 编码器x编码器逻辑; 011:双向增减; 010:正向增; 001:负向递增; 000:关掉编码器; 1xx:暂停编码器; 1XXX:反向逻辑 */
    quint32 encY            :4; /* bit:4-7 编码器y; 同编码器x */
    quint32 res0            :1; /* bit:8 保留 */
    quint32 ut2Twin         :1; /* bit:9 */
    quint32 ut2Damping      :2;
    quint32 ut1Twin         :1;
    quint32 ut1Damping      :2;
    quint32 utVoltage       :6;
    quint32 power           :5;
    quint32 paVoltage       :6;

    /* reg (2) */
    quint32 rxChannels;

    /* reg (3) */
    quint32 res1            :31;
    quint32 freeze          :1;

    /* reg (4-15) */
    quint32 res2[12];

    /* reg (16) */
    quint32 soundFreqency   :3; /* bit: 0-2 */
    quint32 alarmFlags      :5; /* bit: 3-7 */
    quint32 res3            :24;/* bit: 8-31 */

    /* reg (17-19) */
    /* reg (20-22) */
    /* reg (23-25) */
    AlarmOutputData alarmOutput[3];

    /* reg (26-27) */
    AlarmAnalogData alarmAnalog[2];

    /* reg (28) */
    quint32 res4            :20;/* bit: 0-19 */
    quint32 factorEcho      :12;/* bit: 20-32 4095/回波数 */

    /* reg (29 31) */
    quint32 res5[3];
};

QMutex Fpga::s_mutex;
Fpga *Fpga::s_fpga = NULL;
Fpga *Fpga::get_fpga(void)
{
    QMutexLocker locker(&s_mutex);
    if (s_fpga == NULL) {
        s_fpga = new Fpga();
    }

    return s_fpga;
}

bool Fpga::reset()
{
    return true;
}

static bool write_reg(GlobalData *d, int reg);

int Fpga::pa_law_qty()
{
    QReadLocker l(&m_lock);
    return m_global->paLawQty;
}

bool Fpga::set_pa_law_qty(int qty, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->paLawQty = qty;
    return (reflesh ? write_reg(m_global, 0) : true);
}

int Fpga::ut_law_qty()
{
    QReadLocker l(&m_lock);
    return m_global->utLawQty;
}

bool Fpga::set_ut_law_qty(int qty, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->utLawQty = qty;
    return (reflesh ? write_reg(m_global, 0) : true);
}

Fpga::EncoderPolarity Fpga::encoder_x_polarity()
{
    QReadLocker l(&m_lock);
    return (Fpga::EncoderPolarity)(m_global->encX & 0b1000);
}

Fpga::EncoderPolarity Fpga::encoder_y_polarity()
{
    QReadLocker l(&m_lock);
    return (Fpga::EncoderPolarity)(m_global->encY & 0b1000);
}

Fpga::EncoderMode Fpga::encoder_x_mode()
{
    QReadLocker l(&m_lock);
    return (Fpga::EncoderMode)(m_global->encX & 0b0111);
}

Fpga::EncoderMode Fpga::encoder_y_mode()
{
    QReadLocker l(&m_lock);
    return (Fpga::EncoderMode)(m_global->encY & 0b0111);
}

bool Fpga::set_encoder_x(Fpga::EncoderMode mode, Fpga::EncoderPolarity polarity, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->encX = mode|polarity;
    return (reflesh ? write_reg(m_global, 1) : true);
}

bool Fpga::set_encoder_y(Fpga::EncoderMode mode, Fpga::EncoderPolarity polarity, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->encY = mode|polarity;
    return (reflesh ? write_reg(m_global, 1) : true);
}

bool Fpga::ut1_twin()
{
    QReadLocker l(&m_lock);
    return m_global->ut1Twin;
}

bool Fpga::set_ut1_twin(bool enable, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->ut1Twin = enable;
    return (reflesh ? write_reg(m_global, 1) : true);
}

bool Fpga::ut2_twin()
{
    QReadLocker l(&m_lock);
    return m_global->ut2Twin;
}

bool Fpga::set_ut2_twin(bool enable, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->ut2Twin = enable;
    return (reflesh ? write_reg(m_global, 1) : true);
}

Fpga::DampingType Fpga::ut1_damping()
{
    QReadLocker l(&m_lock);
    return (Fpga::DampingType)m_global->ut1Damping;
}

bool Fpga::set_ut1_damping(Fpga::DampingType type, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->ut1Damping = type;
    return (reflesh ? write_reg(m_global, 1) : true);
}

Fpga::DampingType Fpga::ut2_damping()
{
    QReadLocker l(&m_lock);
    return (Fpga::DampingType)m_global->ut2Damping;
}

bool Fpga::set_ut2_damping(Fpga::DampingType type, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->ut2Damping = type;
    return (reflesh ? write_reg(m_global, 1) : true);
}

Fpga::VoltageType Fpga::ut_voltage()
{
    QReadLocker l(&m_lock);
    return (Fpga::VoltageType)m_global->utVoltage;
}

bool Fpga::set_ut_voltage(Fpga::VoltageType type, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->utVoltage = type;
    return (reflesh ? write_reg(m_global, 1) : true);
}

Fpga::VoltageType Fpga::pa_voltage()
{
    QReadLocker l(&m_lock);
    return (Fpga::VoltageType)m_global->paVoltage;
}

bool Fpga::set_pa_voltage(Fpga::VoltageType type, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->paVoltage = type;
    return (reflesh ? write_reg(m_global, 1) : true);
}

Fpga::PowerMode Fpga::power()
{
    QReadLocker l(&m_lock);
    return (Fpga::PowerMode)m_global->power;
}

bool Fpga::set_power(Fpga::PowerMode mode, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->power = mode;
    return (reflesh ? write_reg(m_global, 1) : true);
}

quint32 Fpga::rx_channels()
{
    QReadLocker l(&m_lock);
    return m_global->rxChannels;
}

bool Fpga::set_rx_channels(quint32 channels, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->rxChannels = channels;
    return (reflesh ? write_reg(m_global, 2) : true);
}

bool Fpga::is_freeze()
{
    QReadLocker l(&m_lock);
    return m_global->freeze;
}

bool Fpga::set_freeze(bool freeze, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->freeze = freeze;
    Gpio::get_gpio()->set(Gpio::PIN_43, (Gpio::PinState)!freeze);
    return (reflesh ? write_reg(m_global, 3) : true);
}

Fpga::SoundMode Fpga::sound()
{
    QReadLocker l(&m_lock);
    return (Fpga::SoundMode)m_global->soundFreqency;
}

bool Fpga::set_sound(Fpga::SoundMode mode, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->soundFreqency = mode;
    return (reflesh ? write_reg(m_global, 16) : true);
}

AlarmOutput *Fpga::alarm_output(int index)
{
    switch (index) {
    case 0:
        return &m_alarmOutput0;
        break;
    case 1:
        return &m_alarmOutput1;
        break;
    case 2:
        return &m_alarmOutput2;
        break;
    default:
        return NULL;
        break;
    }
}

AlarmAnalog *Fpga::alarm_analog(int index)
{
    switch (index) {
    case 0:
        return &m_alarmAnalog0;
        break;
    case 1:
        return &m_alarmAnalog1;
        break;
    default:
        return NULL;
        break;
    }
}

int Fpga::factor_echo()
{
    QReadLocker l(&m_lock);
    return m_global->factorEcho;
}

bool Fpga::set_factor_echo(int val, bool reflesh)
{
    QWriteLocker l(&m_lock);
    m_global->factorEcho = val;
    return (reflesh ? write_reg(m_global, 28) : true);
}

int Fpga::groups()
{
    QReadLocker l(&m_groupsLock);
    return m_groups.size();
}

static const int MAX_GROUPS_NUM = 8;
static const int MAX_BEAMS_NUM = 1024;
bool Fpga::create_group()
{
    QWriteLocker l(&m_groupsLock);
    int size = m_groups.size();
    if (size >= MAX_GROUPS_NUM) {
        return false;
    }
    m_groups.append(FpgaGroup(new Group(size)));
    return true;
}

bool Fpga::remove_group(int index)
{
    QWriteLocker l(&m_groupsLock);
    if (index < 0 || m_groups.size() - 1 < index) {
        return false;
    }
    m_groups.removeAt(index);
    return true;
}

FpgaGroup &Fpga::get_group(int index)
{
    QReadLocker l(&m_groupsLock);
    return m_groups[index];
}

int Fpga::beams()
{
    QReadLocker l(&m_beamsLock);
    return m_beams.size();
}

bool Fpga::create_beam()
{
    QWriteLocker l(&m_beamsLock);
    int size = m_beams.size();
    if (size >= MAX_BEAMS_NUM) {
        return false;
    }
    m_beams.append(FpgaBeam(new Beam(size)));
    return true;
}

bool Fpga::remove_beam(int index)
{
    QWriteLocker l(&m_beamsLock);
    if (index < 0 || m_beams.size() -1 < index) {
        return false;
    }
    m_beams.removeAt(index);
    return true;
}

FpgaBeam &Fpga::get_beam(int index)
{
    QReadLocker l(&m_beamsLock);
    return m_beams[index];
}

Fpga::Fpga()
    :m_global(new GlobalData()), m_alarmOutput0(this, 0), m_alarmOutput1(this, 1), m_alarmOutput2(this, 2),
      m_alarmAnalog0(this, 0), m_alarmAnalog1(this, 1)
{
    /* Global */
    qMemSet(m_global, 0, sizeof(GlobalData));
    /** reg -1 **/
    m_global->chip = 0b1000;
    /* reg (1) */
    m_global->encX = Fpga::QUAD|Fpga::NORMAL;
    m_global->encY = Fpga::QUAD|Fpga::NORMAL;
    m_global->ut2Twin = false;
    m_global->ut1Twin = false;
    /* reg (3) */
    m_global->freeze = false;

    /* reg (16) */
//    alarmFlags      :5; /* bit: 3-7 */

//    /* reg (17-19) */
//    /* reg (20-22) */
//    /* reg (23-25) */
//    AlarmOutputData alarmOutput[3];

//    /* reg (26-27) */
//    AlarmAnalogData alarmAnalog[2];

//    /* reg (28) */
//    factorEcho      :12;/* bit: 20-32 4095/回波数 */
}

bool write_reg(GlobalData *d, int reg)
{
    PhascanSpi *spi = PhascanSpi::get_spi();
    if (reg >= GLOBAL_REG_NUM
            || spi == NULL) {
        qWarning()<<"write reg failed";
        return false;
    }

    d->offset = reg;

    quint32 data[2] = {0};
    quint32 *dp = (quint32 *)d;
    data[0] = dp[0];
    data[1] = dp[reg];
    return spi->send((char *)data, 8);
}

/** Alarm Output **/

bool AlarmOutput::is_valid() const
{
    QReadLocker l(&m_fpga->m_lock);
    return !!((m_fpga->m_global->alarmFlags)&(0x1<<m_index));
}

bool AlarmOutput::set_valid(bool flag, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    if (flag) {
        m_fpga->m_global->alarmFlags |= (0x1 << m_index);
    } else {
        m_fpga->m_global->alarmFlags &= ~(0x1 << m_index);
    }
    return (reflesh ? write_reg(m_fpga->m_global, 16) : true);
}

quint16 AlarmOutput::logic_group() const
{
    QReadLocker l(&m_fpga->m_lock);
    return m_fpga->m_global->alarmOutput[m_index].logicGroup;
}

bool AlarmOutput::set_logic_group(quint16 groups, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    m_fpga->m_global->alarmOutput[m_index].logicGroup = groups;
    return (reflesh ? write_reg(m_fpga->m_global, 17+(3*m_index)) : true);
}

AlarmOutput::Operator AlarmOutput::op(void)
{
    QReadLocker l(&m_fpga->m_lock);
    return (AlarmOutput::Operator)m_fpga->m_global->alarmOutput[m_index].op;
}

bool AlarmOutput::set_op(AlarmOutput::Operator op, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    m_fpga->m_global->alarmOutput[m_index].op = op;
    return (reflesh ? write_reg(m_fpga->m_global, 17+3*m_index) : true);
}

AlarmOutput::Condition AlarmOutput::condition(int index)
{
    QReadLocker l(&m_fpga->m_lock);
    if (0 == index) {
        return (AlarmOutput::Condition)m_fpga->m_global->alarmOutput[m_index].logicCondition1;
    } else if (1 == index) {
        return (AlarmOutput::Condition)m_fpga->m_global->alarmOutput[m_index].logicCondition2;
    } else {
        return CONDITION_NONE;
    }
}

bool AlarmOutput::set_condition(int index, AlarmOutput::Condition cond, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    if (0 == index) {
        m_fpga->m_global->alarmOutput[m_index].logicCondition1 = cond;
    } else if (1 == index) {
        m_fpga->m_global->alarmOutput[m_index].logicCondition2 = cond;
    } else {
        return false;
    }
    return (reflesh ? write_reg(m_fpga->m_global, 17+3*m_index) : true);
}

quint32 AlarmOutput::count() const
{
    QReadLocker l(&m_fpga->m_lock);
    return m_fpga->m_global->alarmOutput[m_index].count;
}

bool AlarmOutput::set_count(quint32 count, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    if (count > 100) {
        return false;
    }
    m_fpga->m_global->alarmOutput[m_index].count = count;
    return (reflesh ? write_reg(m_fpga->m_global, 17+3*m_index) : true);
}

int AlarmOutput::delay() const
{
    QReadLocker l(&m_fpga->m_lock);
    return m_fpga->m_global->alarmOutput[m_index].delay*10;
}

bool AlarmOutput::set_delay(int delay, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    if (delay > 5000 * 1000) {
        return false;
    }
    m_fpga->m_global->alarmOutput[m_index].delay = delay/10;
    return (reflesh ? write_reg(m_fpga->m_global, 18+3*m_index) : true);
}

int AlarmOutput::hold_time() const
{
    QReadLocker l(&m_fpga->m_lock);
    return m_fpga->m_global->alarmOutput[m_index].holdTime*10;
}

bool AlarmOutput::set_hold_time(int time, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    if (time > 5000 * 1000) {
        return false;
    }
    m_fpga->m_global->alarmOutput[m_index].holdTime = time/10;
    return (reflesh ? write_reg(m_fpga->m_global, 19+3*m_index) : true);
}

/** AlarmAnalog **/

bool AlarmAnalog::is_valid() const
{
    QReadLocker l(&m_fpga->m_lock);
    return !!((m_fpga->m_global->alarmFlags)&(0b1000<<m_index));
}

bool AlarmAnalog::set_valid(bool flag, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    if (flag) {
        m_fpga->m_global->alarmFlags |= (0b1000<<m_index);
    } else {
        m_fpga->m_global->alarmFlags &= ~(0b1000<<m_index);
    }
    return (reflesh ? write_reg(m_fpga->m_global, 16) : true);
}

quint16 AlarmAnalog::logic_group() const
{
    QReadLocker l(&m_fpga->m_lock);
    return m_fpga->m_global->alarmAnalog[m_index].logicGroup;
}

bool AlarmAnalog::set_logic_group(quint16 groups, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    m_fpga->m_global->alarmAnalog[m_index].logicGroup = groups;
    return (reflesh ? write_reg(m_fpga->m_global, 26+m_index) : true);
}

AlarmAnalog::Type AlarmAnalog::type() const
{
    QReadLocker l(&m_fpga->m_lock);
    return (AlarmAnalog::Type)m_fpga->m_global->alarmAnalog[m_index].type;
}

bool AlarmAnalog::set_type(AlarmAnalog::Type type, bool reflesh)
{
    QWriteLocker l(&m_fpga->m_lock);
    m_fpga->m_global->alarmAnalog[m_index].type = type;
    return (reflesh ? write_reg(m_fpga->m_global, 26+m_index) : true);
}
