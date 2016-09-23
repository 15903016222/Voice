#ifndef __FPGA_H__
#define __FPGA_H__

#include <QObject>
#include <QMutex>
#include <QAtomicPointer>

class Fpga : public QObject
{
    Q_OBJECT
public:

    enum EncoderPolarity {
        Normal  = 0,
        Inverse = 0b1000
    };

    enum EncoderMode {
        QUAD    = 0b011,
        UP      = 0b010,
        DOWN    = 0b001,
        OFF     = 0b000,
        PAUSE   = 0b100
    };

    enum DampingType {
        R500 = 500,
        R200 = 200,
        R100 = 100,
        R50  = 50
    };

    enum VoltageType {
        V400 = 400,
        V200 = 200,
        V100 = 100,
        V50  = 50
    };

    enum PowerMode {

    };

    enum SoundMode {
        SOUND_OFF   = 0x000,
        SOUND_300HZ = 0x001,
        SOUND_600HZ = 0x010,
        SOUND_1000HZ= 0x011,
        SOUND_5000HZ= 0x100,
    };

    static Fpga* get_fpga(void);
    virtual bool reset() = 0;
    /* Global */
    virtual int pa_law_qty() const = 0;                     /* PA聚焦法则数 */
    virtual bool set_pa_law_qty(int qty) const = 0;
    virtual int ut_law_qty() const = 0;                     /* UT(虚拟)聚焦法则数 */
    virtual bool set_ut_law_qty(int qty) const = 0;
    virtual EncoderPolarity encoder_x_polarity() const = 0; /* 编码器X极性 */
    virtual EncoderPolarity encoder_y_polarity() const = 0; /* 编码器Y极性 */
    virtual EncoderMode encoder_x_mode() const = 0;         /* 编码器X模式 */
    virtual EncoderMode encoder_y_mode() const = 0;         /* 编码器Y模式 */
    virtual bool set_encoder_x(EncoderPolarity polarity, EncoderMode type) = 0;
    virtual bool set_encoder_y(EncoderPolarity polarity, EncoderMode type) = 0;
    virtual bool ut1_twin() const = 0;                      /* UT1双晶状态 */
    virtual bool set_ut1_twin(bool enable) = 0;
    virtual bool ut2_twin() const = 0;                      /* UT2双晶状态 */
    virtual bool set_ut2_twin(bool enable) = 0;
    virtual DampingType ut1_damping() const = 0;            /* UT1阻尼 */
    virtual DampingType ut2_damping() const = 0;            /* UT2阻尼 */
    virtual VoltageType ut_voltage() const = 0;             /* UT发射电压 */
    virtual PowerMode power() const = 0;                    /* 控制省电 */
    virtual VoltageType pa_voltage() const = 0;             /* PA发射电压 */
    virtual int channel() const = 0;                        /* 接收通道使能组 */
    virtual bool freeze() const = 0;                        /* 冻结 */
    virtual SoundMode sound() const = 0;                    /* 蜂鸣器频率 */
    virtual bool alarm_output1_enable() const = 0;          /* 输出报警使能 */
    virtual bool alarm_output2_enable() const = 0;
    virtual bool alarm_output3_enable() const = 0;
    virtual bool alarm_analog1_enable() const = 0;
    virtual bool alarm_analog1_enable() const = 0;
    virtual short alarm_output1_logic_group() const = 0;    /* 16组报警逻辑组使能位 */
    virtual short alarm_output2_logic_group() const = 0;
    virtual short alarm_output3_logic_group() const = 0;
    virtual short alarm_analog1_logic_group() const = 0;
    virtual short alarm_analog2_logic_group() const = 0;

    enum OutputType {
        Output_NONE,
        Output_GATE_A        = 0b0001,
        Output_GATE_B        = 0b0010,
        Output_GATE_I        = 0b0011,
        Output_NOT_GATE_A    = 0b0100,
        Output_NOT_GATE_B    = 0b0101,
        Output_NOT_GATE_I    = 0b0110,
        Output_MAX_THICKNESS = 0b0111,
        Output_MIN_THICKNESS = 0b1000
    };
    virtual OutputType alarm_output1_type() const = 0;
    virtual OutputType alarm_output2_type() const = 0;
    virtual OutputType alarm_output3_type() const = 0;

    enum OutputOperator {
        AND_OPERATOR,
        OR_OPERATOR
    };
    virtual OutputOperator alarm_output1_operator(int group) const = 0;
    virtual OutputOperator alarm_output2_operator(int group) const = 0;
    virtual OutputOperator alarm_output3_operator(int group) const = 0;

    virtual int alarm_output1_delay() const = 0;            /* 延迟时间，单位us */
    virtual int alarm_output2_delay() const = 0;            /* 延迟时间，单位us */
    virtual int alarm_output3_delay() const = 0;            /* 延迟时间，单位us */
    virtual int alarm_output1_hold_time() const = 0;        /* 保持时间，单位us */
    virtual int alarm_output2_hold_time() const = 0;        /* 保持时间，单位us */
    virtual int alarm_output3_hold_time() const = 0;        /* 保持时间，单位us */

    virtual short alarm_analog1_logic_group() const = 0;    /* 16组报警逻辑组使能位 */
    virtual short alarm_analog2_logic_group() const = 0;    /* 16组报警逻辑组使能位 */

    enum AnalogType {
        ANALOG_GATE_A       = 0b001,                        /* A闸门峰值 */
        ANALOG_GATE_B       = 0b010,                        /* B闸门峰值 */
        ANALOG_THINKNESS    = 0b100                         /* 厚度 */
    };
    virtual AnalogType alarm_analog1_type() const = 0;
    virtual AnalogType alram_analog2_type() const = 0;

    virtual int factor_echo() const = 0;                    /* 回波数 */

    /* Group */
    virtual int freq_band(int group) const = 0;             /* 频带选择 */
    virtual bool video_filter(int group) const = 0;         /* 视频滤波 */
    enum RectifierType {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE
    };
    virtual RectifierType rectifier(int group) const = 0;
    virtual int compress_rato(int group) const = 0;
    virtual int gain(int group) const = 0;
    virtual int thickness_factor(int group) const = 0;
    virtual bool ut1(int group) const = 0;
    virtual bool ut2(int group) const = 0;
    virtual bool pa(int group) const = 0;
    virtual int sum_gain(int group) const = 0;
    virtual int sample_range(int group) const = 0;
    virtual int point_qty(int group) const = 0;
    virtual int tcg_point_qty(int group) const = 0;
    virtual int tcg(int group) const = 0;
    virtual int rx_time(int group) const = 0;
    virtual int idel_time(int group) const = 0;
    virtual int gate_a_height(int group) const = 0;
    virtual int gate_a_logic(int group) const = 0;
    virtual int gate_b_height(int group) const = 0;
    virtual int gate_b_logic(int group) const = 0;
    virtual int gate_i_height(int group) const = 0;
    virtual int gate_i_logic(int group) const = 0;
    virtual int thickness_min(int group) const = 0;
    virtual int reject(int group) const = 0;
    virtual int sample_start(int group) const = 0;
    virtual int average(int group) const = 0;
    virtual int thickness_max(int group) const = 0;
    virtual int thickness_source(int group) const = 0;
    virtual int tx_end(int group) = 0;
    virtual int tx_start(int group) = 0;

    /* Focal Law */
    virtual int gain_offset(int beam) const = 0;
    virtual int group_id(int beam) const = 0;
    virtual int all_beam_info(int beam) const = 0;
    virtual int beam_delay(int beam) const = 0;
    virtual int gate_a_start(int beam) const = 0;
    virtual int gate_a_end(int beam) const = 0;
    virtual int gate_b_start(int beam) const = 0;
    virtual int gate_b_end(int beam) const = 0;
    virtual int gate_i_start(int beam) const = 0;
    virtual int gate_i_end(int beam) const = 0;
    virtual int tx(int beam) const = 0;
    virtual int rx(int beam) const = 0;
    virtual int64_t rx_sel(int beam) const = 0;
    virtual int64_t tx_sel(int beam) const = 0;
    virtual int tx_delay(int beam, int channel) const = 0;
    virtual int rx_delay(int beam, int channel) const = 0;
    virtual int tcg_position(int beam, int point) const = 0;
    virtual int tcg_pregain(int beam, int point) const = 0;
    virtual int tcg_slope(int beam, int point) const = 0;
    virtual int tcg_flag(int beam, int point) const = 0;


protected:
    Fpga() {}
//    Fpga(const Fpga& fpga){Q_UNUSED(fpga);}
//    Fpga & operator=(const Fpga &fpga) {Q_UNUSED(fpga);}
    virtual ~Fpga() {}


private:
    static QMutex m_mutex;
    static Fpga *m_fpga;
};

#endif // __FPGA_H__
