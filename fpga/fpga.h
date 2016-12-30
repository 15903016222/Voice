/**
 * @file fpga.h
 * @brief Fpga Class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#ifndef __FPGA_H__
#define __FPGA_H__

#include "fpga_global.h"
#include "group.h"
#include "beam.h"
#include "tcg.h"

#include <QMutex>
#include <QReadWriteLock>
#include <QSharedPointer>

namespace DplFpga {

struct GlobalData;

class Fpga;

class FPGASHARED_EXPORT AlarmOutput
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

class FPGASHARED_EXPORT AlarmAnalog
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

typedef QSharedPointer<Group> GroupPointer;
typedef QSharedPointer<Beam> BeamPointer;
typedef QSharedPointer<Tcg> TcgPointer;

class FPGASHARED_EXPORT Fpga
{
    friend class AlarmOutput;
    friend class AlarmAnalog;

public:
    static Fpga* get_instance(void);

    bool reset();

    /**
     * @brief sample_precision  采样精度
     * @return                  返回采样精度, 单位(ns)
     */
    float sample_precision();

    /**
     * @brief loading_time  获取FPGA每条Beam设置寄存器的时间
     * @return              时间, 单位(采样精度)
     */
    int loading_time();


    /* Global */
    int pa_law_qty();                     /* PA聚焦法则数 */
    bool set_pa_law_qty(int qty, bool reflesh = false);

    int ut_law_qty();                     /* UT(虚拟)聚焦法则数 */
    bool set_ut_law_qty(int qty, bool reflesh = false);

    /* 编码器 */
    enum EncoderPolarity {
        NORMAL  = 0,
        INVERSE = 1
    };
    enum EncoderMode {
        OFF     = 0b000,
        DOWN    = 0b001,
        UP      = 0b010,
        QUAD    = 0b011,
        PAUSE   = 0b100
    };
    EncoderPolarity encoder_x_polarity(); /* 编码器X极性 */
    EncoderPolarity encoder_y_polarity(); /* 编码器Y极性 */
    bool set_encoder_x_polarity(Fpga::EncoderPolarity polarity, bool reflesh = false);
    bool set_encoder_y_polarity(Fpga::EncoderPolarity polarity, bool reflesh = false);
    EncoderMode encoder_x_mode();         /* 编码器X模式 */
    EncoderMode encoder_y_mode();         /* 编码器Y模式 */
    bool set_encoder_x_mode(EncoderMode type, bool reflesh = false);
    bool set_encoder_y_mode(EncoderMode type, bool reflesh = false);

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

    static const int MAX_GROUPS_NUM;
    static const int MAX_BEAMS_NUM;
    static const int MAX_TCGS_NUM;

    /** Beam **/
    int beams();
    bool create_beam();
    bool remove_beam();
    BeamPointer &get_beam(int index);

    /** Tcg **/
    int tcgs();
    bool create_tcg();
    bool remove_tcg();
    TcgPointer &get_tcg(int index);

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

    QList<GroupPointer> m_groups;
    GroupPointer m_curGroup;
    QReadWriteLock m_groupsLock;

    QList<BeamPointer> m_beams;
    QReadWriteLock m_beamsLock;

    QList<TcgPointer> m_tcgs;
    QReadWriteLock m_tcgsLock;
};

}

#endif // __FPGA_H__
