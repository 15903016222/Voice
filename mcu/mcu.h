#ifndef __MCU_H__
#define __MCU_H__

#include "probe.h"

#include <QObject>
#include <QMutex>

class Mcu : public QObject
{
    Q_OBJECT
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
        NORMAL_PROBE_2_FREQUENCY    = 0x73, /* 常规探头Ii频率 */
        NORMAL_PROBE_2_SIZE         = 0x74, /* 常规探头Ii晶片尺寸 */
    };

    enum RotaryType {
        ROTARY_UP,
        ROTARY_DOWN
    };

    enum BatteryStatus {
        DISCHARGE,
        CHARGE,
        NO_BATTERY,
        BATTERY_FULL,
        BATTERY_NO_WORK
    };

    enum TemperatureType {
        TEMPERATURE_CPU     = CORE_TEMPERATURE,
        TEMPERATURE_FPGA    = FPGA_TEMPERATURE,
        TEMPERATURE_MCU     = MCU_TEMPERATUREE,
        TEMPERATURE_POWER   = POWER_TEMPERATURE
    };

    virtual void query_core_temp()              = 0;
    virtual void query_fpga_temp()              = 0;
    virtual void query_power_temp()             = 0;
    virtual void query_mcu_temp()               = 0;
    virtual void query_first_battery()          = 0;
    virtual void query_second_battery()         = 0;
    virtual void query_first_battery_status()   = 0;
    virtual void query_second_battery_status()  = 0;
    virtual void query_brightness()             = 0;
    virtual void query_probe()                  = 0;

    static Mcu* get_mcu();
    static void destroyed();

public slots:
    virtual void notify_started()   = 0;
    virtual void set_poweroff()     = 0;
    virtual void set_brightness(char light)  = 0;


Q_SIGNALS:
    void key_event(int value);
    void rotary_event(Mcu::RotaryType type);
    void brightness_event(int value);
    void battery_status_event(int index, Mcu::BatteryStatus status);
    void battery_quantity_event(int index, int value);
    void temperature_event(Mcu::TemperatureType type, int value);
    void probe_event(const Probe& probe);
    void poweroff_event(void);

protected:
    explicit Mcu() {}
    virtual ~Mcu() {}

private:
    static QMutex m_mutex;
    static Mcu* m_mcu;
};

#endif
