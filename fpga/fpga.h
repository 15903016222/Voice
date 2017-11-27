/**
 * @file fpga.h
 * @brief Fpga Class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#ifndef __DPLFPGA_FPGA_H__
#define __DPLFPGA_FPGA_H__

#include "group.h"
#include "beam.h"
#include "tcg.h"
#include "alarm_output.h"
#include "alarm_analog.h"

namespace DplFpga {

class FpgaPrivate;
class FPGASHARED_EXPORT Fpga
{
    Q_DECLARE_PRIVATE(Fpga)
public:
    /**
     * @brief SAMPLE_PRECISION  采样精度(ns), 如10ns即采样频率为100MHz
     */
    static const float SAMPLE_PRECISION;

    /**
     * @brief LOADING_TIME  FPGA在每次聚焦时的寄存器设置时间(单位，采样精度)
     */
    static const int LOADING_TIME;

    /**
     * @brief MAX_BEAMS_NUM 最大Beam数
     */
    static const int MAX_BEAMS_NUM;

    /**
     * @brief MAX_TCGS_NUM  最大TCG数
     */
    static const int MAX_TCGS_NUM;

    /**
     * @brief instance  获取Fpga对象
     * @return          Fpga对象
     */
    static Fpga* instance(void);

    bool reset();

    /**
     * @brief pa_law_qty    PA聚焦法则数
     * @return              数量
     */
    int pa_law_qty() const;

    /**
     * @brief set_pa_law_qty    设置PA聚焦法则数
     * @param qty               数量
     * @return                  成功返回true，否则false
     */
    bool set_pa_law_qty(int qty);

    /**
     * @brief ut_law_qty    获取UT(虚拟)聚焦法则数
     * @return              数量
     */
    int ut_law_qty() const;

    /**
     * @brief set_ut_law_qty    设置UT(虚拟)聚焦法则数
     * @param qty               数量
     * @return                  成功返回true，否则false
     */
    bool set_ut_law_qty(int qty);

    /**
     * @brief The EncoderPolarity enum  编码器极性类型
     */
    enum EncoderPolarity {
        NORMAL  = 0,
        INVERSE = 1
    };

    /**
     * @brief The EncoderMode enum  编码器工作模式
     */
    enum EncoderMode {
        OFF     = 0b000,
        DOWN    = 0b001,
        UP      = 0b010,
        QUAD    = 0b011,
        PAUSE   = 0b100
    };

    /**
     * @brief encoder_x_polarity    获取编码器X极性
     * @return                      极性
     */
    EncoderPolarity encoder_x_polarity() const;

    /**
     * @brief encoder_y_polarity    获取编码器Y极性
     * @return                      极性
     */
    EncoderPolarity encoder_y_polarity() const;

    /**
     * @brief set_encoder_x_polarity    设置编码器X极性
     * @param polarity                  极性
     * @return                          成功返回true，否则为false
     */
    bool set_encoder_x_polarity(Fpga::EncoderPolarity polarity);

    /**
     * @brief set_encoder_y_polarity    设置编码器Y极性
     * @param polarity                  极性
     * @return                          成功返回true，否则为false
     */
    bool set_encoder_y_polarity(Fpga::EncoderPolarity polarity);

    /**
     * @brief encoder_x_mode    获取编码器X模式
     * @return                  编码器模式
     */
    EncoderMode encoder_x_mode() const;

    /**
     * @brief encoder_y_mode    获取编码器Y模式
     * @return                  编码器Y模式
     */
    EncoderMode encoder_y_mode() const;

    /**
     * @brief set_encoder_x_mode    设置编码器X模式
     * @param type                  编码器模式
     * @return                      设置成功返回true，否则为false
     */
    bool set_encoder_x_mode(EncoderMode type);

    /**
     * @brief set_encoder_y_mode    设置编码器Y模式
     * @param type                  编码器模式
     * @return                      设置成功返回true，否则为false
     */
    bool set_encoder_y_mode(EncoderMode type);

    /**
     * @brief ut1_twin  获取UT1通道的双晶状态
     * @return          开启返回true，关闭返回false
     */
    bool ut1_twin() const;

    /**
     * @brief set_ut1_twin  设置UT1通道的双晶状态
     * @param enable        true为开启，关闭为false
     * @return              设置成功返回true，失败返回false
     */
    bool set_ut1_twin(bool enable);

    /**
     * @brief ut2_twin  设置UT2通道的双晶状态
     * @return          开启返回true，关闭返回false
     */
    bool ut2_twin() const;

    /**
     * @brief set_ut2_twin  设置UT2通道的双晶状态
     * @param enable        true为开启，false为关闭
     * @return              设置成功返回true，失败返回false
     */
    bool set_ut2_twin(bool enable);

    /**
     * @brief The DampingType enum  UT发射接收阻尼类型
     */
    enum DampingType {
        R50  = 0b00,
        R100 = 0b01,
        R200 = 0b10,
        R500 = 0b11
    };

    /**
     * @brief ut1_tx_damping    获取UT1发射通道阻尼
     * @return                  阻尼类型
     */
    DampingType ut1_tx_damping() const;

    /**
     * @brief set_ut1_tx_damping    设置UT1发射通道阻尼
     * @param type                  阻尼类型
     * @return                      设置成功返回true，失败返回false
     */
    bool set_ut1_tx_damping(DampingType type);

    /**
     * @brief ut2_tx_damping    获取UT2发射通道阻尼
     * @return                  阻尼类型
     */
    DampingType ut2_tx_damping() const;

    /**
     * @brief set_ut2_tx_damping    设置UT2发射通道阻尼
     * @param type                  阻尼类型
     * @return                      设置成功返回true，失败返回false
     */
    bool set_ut2_tx_damping(DampingType type);

    /**
     * @brief ut1_rx_damping    获取UT1接收通道阻尼
     * @return                  阻尼类型
     */
    DampingType ut1_rx_damping() const;

    /**
     * @brief set_ut1_rx_damping    设置UT1接收通道阻尼
     * @param type                  阻尼类型
     * @return                      设置成功返回true，失败返回false
     */
    bool set_ut1_rx_damping(DampingType type);

    /**
     * @brief ut2_rx_damping    获取UT2接收通道阻尼
     * @return                  阻尼类型
     */
    DampingType ut2_rx_damping() const;

    /**
     * @brief set_ut2_rx_damping    设置UT2接收通道阻尼
     * @param type                  阻尼类型
     * @return                      设置成功返回true，失败返回false
     */
    bool set_ut2_rx_damping(DampingType type);

    /**
     * @brief The VoltageType enum  PA/UT发射电压类型
     */
    enum VoltageType {
        VOLTAGE_LOW     = 0b00,
        VOLTAGE_MIDDLE  = 0b01,
        VOLTAGE_HIGHT   = 0b10
    };

    /**
     * @brief ut_voltage    获取UT电压类型
     * @return              电压类型
     */
    VoltageType ut_voltage() const;

    /**
     * @brief set_ut_voltage    设置UT电压类型
     * @param type              电压类型
     * @return                  成功返回true，否则为false
     */
    bool set_ut_voltage(VoltageType type);

    /**
     * @brief pa_voltage    获取PA电压类型
     * @return              电压类型
     */
    VoltageType pa_voltage() const;

    /**
     * @brief set_pa_voltage    设置PA电压类型
     * @param type              电压类型
     * @return                  成功返回true，否则为false
     */
    bool set_pa_voltage(VoltageType type);

    /* 控制省电 */
    enum PowerMode {
        NONE_POWER_MODE
    };
    PowerMode power() const;
    bool set_power(Fpga::PowerMode mode);

    /* 接收通道使能组 */
    quint32 rx_channels() const;
    bool set_rx_channels(quint32 channels);

    /* 冻结 */
    bool is_freeze() const;
    bool set_freeze(bool freeze);

    /**
     * @brief The SoundMode enum    蜂鸣器工作频率
     */
    enum SoundMode {
        SOUND_OFF   = 0b000,
        SOUND_300HZ = 0b001,
        SOUND_600HZ = 0b010,
        SOUND_1000HZ= 0b011,
        SOUND_5000HZ= 0b100,
    };

    /**
     * @brief sound 获取蜂鸣器工作频率
     * @return      频率模式
     */
    SoundMode sound() const;

    /**
     * @brief set_sound 设置蜂鸣器工作频率
     * @param mode      频率模式
     * @return          成功返回true，否则为false
     */
    bool set_sound(SoundMode mode);

    AlarmOutput *alarm_output(int index);
    AlarmAnalog *alarm_analog(int index);

    /* 回波数 */
    int factor_echo() const;
    bool set_factor_echo(int val);

    void init();

    void show_info() const;

    /**
     * @brief deploy    下发FPGA配置参数
     * @return          成功返回true，失败返回false
     */
    bool deploy() const;

protected:
    Fpga();
    ~Fpga();

private:
    FpgaPrivate *d_ptr;
};

}

#endif // __DPLFPGA_FPGA_H__
