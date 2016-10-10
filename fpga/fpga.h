#ifndef __FPGA_H__
#define __FPGA_H__

#include "group.h"
#include "beam.h"

#include <QMutex>
#include <QReadWriteLock>
#include <QSharedPointer>

struct GlobalData;

class Fpga;

class AlarmOutput
{
public:
    AlarmOutput(Fpga *fpga, int index) : m_fpga(fpga), m_index(index) {}

    bool is_valid() const;
    bool set_valid(bool flag, bool reflesh = false);

    quint16 logic_group() const;
    bool set_logic_group(quint16 groups, bool reflesh = false);

    enum Operator {
        AND,
        OR
    };
    Operator op(void);
    bool set_op(Operator op, bool reflesh = false);

    enum Condition {
        CONDITION_NONE,
        CONDITION_GATE_A        = 0b0001,
        CONDITION_GATE_B        = 0b0010,
        CONDITION_GATE_I        = 0b0011,
        CONDITION_NOT_GATE_A    = 0b0100,
        CONDITION_NOT_GATE_B    = 0b0101,
        CONDITION_NOT_GATE_I    = 0b0110,
        CONDITION_MAX_THICKNESS = 0b0111,
        CONDITION_MIN_THICKNESS = 0b1000
    };
    Condition condition(int index);
    bool set_condition(int index, Condition cond, bool reflesh = false);

    quint32 count() const;
    bool set_count(quint32 count, bool reflesh = false);

    int delay() const;                                  /* 延迟时间，单位us */
    bool set_delay(int delay, bool reflesh = false);

    int hold_time() const;                              /* 保持时间，单位us */
    bool set_hold_time(int time, bool reflesh = false);

private:
    Fpga *m_fpga;
    int m_index;
};

class AlarmAnalog
{
public:
    AlarmAnalog(Fpga *fpga, int index) : m_fpga(fpga), m_index(index) {}
    bool is_valid() const;
    bool set_valid(bool flag, bool reflesh = false);

    quint16 logic_group() const;
    bool set_logic_group(quint16 groups, bool reflesh = false);

    enum Type {
        NONE         = 0b000,                        /* 无效类型 */
        GATE_A       = 0b001,                        /* A闸门峰值 */
        GATE_B       = 0b010,                        /* B闸门峰值 */
        THICKNESS    = 0b100                         /* 厚度 */
    };
    Type type() const;
    bool set_type(Type type, bool reflesh = false);

private:
    Fpga *m_fpga;
    int m_index;
};

typedef QSharedPointer<Group> FpgaGroup;
typedef QSharedPointer<Beam> FpgaBeam;

class Fpga
{
    friend class AlarmOutput;
    friend class AlarmAnalog;

public:
    static Fpga* get_fpga(void);

    bool reset();

    /* Global */
    int pa_law_qty();                     /* PA聚焦法则数 */
    bool set_pa_law_qty(int qty, bool reflesh = false);

    int ut_law_qty();                     /* UT(虚拟)聚焦法则数 */
    bool set_ut_law_qty(int qty, bool reflesh = false);

    /* 编码器 */
    enum EncoderPolarity {
        NORMAL  = 0,
        INVERSE = 0b1000
    };
    enum EncoderMode {
        QUAD    = 0b011,
        UP      = 0b010,
        DOWN    = 0b001,
        OFF     = 0b000,
        PAUSE   = 0b100
    };
    EncoderPolarity encoder_x_polarity(); /* 编码器X极性 */
    EncoderPolarity encoder_y_polarity(); /* 编码器Y极性 */
    EncoderMode encoder_x_mode();         /* 编码器X模式 */
    EncoderMode encoder_y_mode();         /* 编码器Y模式 */
    bool set_encoder_x(EncoderMode type, EncoderPolarity polarity = NORMAL, bool reflesh = false);
    bool set_encoder_y(EncoderMode type, EncoderPolarity polarity = NORMAL, bool reflesh = false);

    /* UT双晶状态 */
    bool ut1_twin();
    bool set_ut1_twin(bool enable, bool reflesh = false);
    bool ut2_twin();
    bool set_ut2_twin(bool enable, bool reflesh = false);

    /* UT发射接收阻尼 */
    enum DampingType {
        R50  = 0b00,
        R100 = 0b01,
        R200 = 0b10,
        R500 = 0b11
    };
    DampingType ut1_tx_damping();
    bool set_ut1_tx_damping(DampingType type, bool reflesh = false);
    DampingType ut2_tx_damping();
    bool set_ut2_tx_damping(DampingType type, bool reflesh = false);
    DampingType ut1_rx_damping();
    bool set_ut1_rx_damping(DampingType type, bool reflesh = false);
    DampingType ut2_rx_damping();
    bool set_ut2_rx_damping(DampingType type, bool reflesh = false);

    /* PA/UT发射电压 */
    enum VoltageType {
        VOLTAGE_LOW     = 0b00,
        VOLTAGE_MIDDLE  = 0b01,
        VOLTAGE_HIGHT   = 0b10
    };
    VoltageType ut_voltage();
    bool set_ut_voltage(VoltageType type, bool reflesh = false);
    VoltageType pa_voltage();
    bool set_pa_voltage(VoltageType type, bool reflesh = false);

    /* 控制省电 */
    enum PowerMode {
        NONE_POWER_MODE
    };
    PowerMode power();
    bool set_power(Fpga::PowerMode mode, bool reflesh = false);

    /* 接收通道使能组 */
    quint32 rx_channels();
    bool set_rx_channels(quint32 channels, bool reflesh = false);

    /* 冻结 */
    bool is_freeze();
    bool set_freeze(bool freeze, bool reflesh = false);

    /* 蜂鸣器频率 */
    enum SoundMode {
        SOUND_OFF   = 0b000,
        SOUND_300HZ = 0b001,
        SOUND_600HZ = 0b010,
        SOUND_1000HZ= 0b011,
        SOUND_5000HZ= 0b100,
    };
    SoundMode sound();
    bool set_sound(SoundMode mode, bool reflesh = false);

    AlarmOutput *alarm_output(int index);
    AlarmAnalog *alarm_analog(int index);

    /* 回波数 */
    int factor_echo();
    bool set_factor_echo(int val, bool reflesh = false);

    /** Group **/
    int groups();
    bool create_group();
    bool remove_group();
    FpgaGroup& get_group(int index);

    /** Beam **/
    int beams();
    bool create_beam();
    bool remove_beam(int index);
    FpgaBeam &get_beam(int index);

protected:
    Fpga();
    ~Fpga();

private:
    static QMutex s_mutex;
    static Fpga *s_fpga;
    GlobalData *m_global;
    AlarmOutput m_alarmOutput0;
    AlarmOutput m_alarmOutput1;
    AlarmOutput m_alarmOutput2;
    AlarmAnalog m_alarmAnalog0;
    AlarmAnalog m_alarmAnalog1;
    QReadWriteLock m_lock;
    QList<FpgaGroup> m_groups;
    QReadWriteLock m_groupsLock;
    QList<FpgaBeam> m_beams;
    QReadWriteLock m_beamsLock;
};

#endif // __FPGA_H__
