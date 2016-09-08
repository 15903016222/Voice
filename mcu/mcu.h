#ifndef __MCU_H__
#define __MCU_H__

#include <QObject>
#include <QByteArray>

class McuPrivate;

class Mcu : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Mcu)
public:
    enum Cmd {
        CORE_TEMPERATURE            = 0x10, /* 核心板温度 */
        FPGA_TEMPERATURE            = 0x11, /* FPGA温度 */
        POWER_TEMPERATURE           = 0x12, /* 电源温度 */
        MCU_TEMPERATUREE            = 0x13, /* MCU温度 */
        KEY                         = 0x21, /* 按键 */
        ROTARY                      = 0x22, /* 飞梭 */
        BATTERY1_STATUS             = 0x31, /* 1号电池状态 */
        BATTERY2_STATUS             = 0x35, /* 2号电池状态 */
        BATTERY1_QUANTITY           = 0x32, /* 1号电池电量 */
        BATTERY2_QUANTITY           = 0x36, /* 2号电池电量 */
        POWEROFF                    = 0x41, /* 关机 */
        BRIGHTNESS                  = 0x42, /* 背光亮度 */
        NOTIFY_STARTED              = 0x43, /* 主程序启动通知 */
        PA_PROBE_MODEL              = 0x51, /* 相控阵探头型号 */
        PA_PROBE_SERIES             = 0x52, /* 相控阵探头系列 */
        PA_PROBE_TYPE               = 0x53, /* 相控阵探头类型 */
        PA_PROBE_FREQ               = 0x54, /* 相控阵探头频率 */
        PA_PROBE_ELEMENTS_QTY       = 0x55, /* 相控阵探头阵元数 */
        PA_PROBE_ELEMENTS_DISTANCE  = 0x56, /* 相控阵探头阵元间距 */
        PA_PROBE_FERENCE_POINT      = 0x57, /* 相控阵探头参考点 */
        NORMAL_PROBE_1_MODEL        = 0x61, /* 常规探头I型号 */
        NORMAL_PROBE_1_SERIES       = 0x64, /* 常规探头I系列 */
        NORMAL_PROBE_1_FREQ         = 0x63, /* 常规探头I频率 */
        NORMAL_PROBE_1_SIZE         = 0x64, /* 常规探头I晶片尺寸 */
        NORMAL_PROBE_2_MODEL        = 0x71, /* 常规探头Ii型号 */
        NORMAL_PROBE_2_SERIES       = 0x72, /* 常规探头Ii系列 */
        NORMAL_PROBE_2_FRENQUNCY    = 0x73, /* 常规探头iI频率 */
        NORMAL_PROBE_2_SIZE         = 0x74, /* 常规探头Ii晶片尺寸 */
    };

    void query_core_temp();
    void query_fpga_temp();
    void query_power_temp();
    void query_mcu_temp();
    void query_first_battery();
    void query_second_battery();
    void query_first_battery_status();
    void query_second_battery_status();
    void query_brightness();

    /* pa probe query */
    void query_pa_probe_model();
    void query_pa_probe_series();
    void query_pa_probe_type();
    void query_pa_probe_freq();
    void query_pa_probe_elements();
    void query_pa_probe_elements_distance();
    void query_pa_probe_ference_point();

    void notify_started() {}
    void set_poweroff() {}
    void set_brightness(uchar light) { Q_UNUSED(light); }

    static Mcu* get_instance();
    static void destroyed();

Q_SIGNALS:
    void event(Mcu::Cmd cmd, QByteArray &val);

protected:
    explicit Mcu();
    virtual ~Mcu();

private:
    static Mcu* m_mcu;
    McuPrivate *d_ptr;

};

inline Mcu* Mcu::get_instance()
{
    if (m_mcu == NULL) {
        m_mcu = new Mcu();
    }
    return m_mcu;
}

inline void Mcu::destroyed()
{
    if (m_mcu) {
        delete m_mcu;
        m_mcu = NULL;
    }
}

#endif
