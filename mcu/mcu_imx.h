#ifndef __MCU_IMX_H__
#define __MCU_IMX_H__

#include "mcu.h"

#include <QSerialPort>
#include <QMutex>
#include <QDebug>
/**
 * package format
 * -------------------------------------------------------
 * | 0xff | 0xff | TYPE | LEN | CMD | DATA | 0xfe | 0xfe |
 * -------------------------------------------------------
 */

class McuImx : public Mcu
{
    Q_OBJECT
public:
    enum PkgType {
        RespondPkg = 0x50,  /* 应答包 */
        EventPkg,           /* 事件包 */
        QueryPkg,           /* 查询包 */
        SettingPkg          /* 设置包 */
    };
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
        PA_PROBE_SERIAL             = 0x52, /* 相控阵探头系列 */
        PA_PROBE_TYPE               = 0x53, /* 相控阵探头类型 */
        PA_PROBE_FREQ               = 0x54, /* 相控阵探头频率 */
        PA_PROBE_ELEMENTS_QTY       = 0x55, /* 相控阵探头阵元数 */
        PA_PROBE_ELEMENTS_DISTANCE  = 0x56, /* 相控阵探头阵元间距 */
        PA_PROBE_REFERENCE_POINT      = 0x57, /* 相控阵探头参考点 */
        NORMAL_PROBE_1_MODEL        = 0x61, /* 常规探头I型号 */
        NORMAL_PROBE_1_SERIES       = 0x64, /* 常规探头I系列 */
        NORMAL_PROBE_1_FREQ         = 0x63, /* 常规探头I频率 */
        NORMAL_PROBE_1_SIZE         = 0x64, /* 常规探头I晶片尺寸 */
        NORMAL_PROBE_2_MODEL        = 0x71, /* 常规探头Ii型号 */
        NORMAL_PROBE_2_SERIES       = 0x72, /* 常规探头Ii系列 */
        NORMAL_PROBE_2_FREQUENCY    = 0x73, /* 常规探头Ii频率 */
        NORMAL_PROBE_2_SIZE         = 0x74, /* 常规探头Ii晶片尺寸 */
    };

    McuImx();
    void query_core_temp()          { query(CORE_TEMPERATURE); }
    void query_fpga_temp()          { query(FPGA_TEMPERATURE); }
    void query_power_temp()         { query(POWER_TEMPERATURE);}
    void query_mcu_temp()           { query(MCU_TEMPERATUREE); }
    void query_first_battery()      { query(BATTERY1_QUANTITY); }
    void query_second_battery()     { query(BATTERY2_QUANTITY); }
    void query_first_battery_status() { query(BATTERY1_STATUS); }
    void query_second_battery_status(){ query(BATTERY2_STATUS); }
    void query_brightness()         { query(BRIGHTNESS); }
    void query_probe();
    void notify_started()           { set(NOTIFY_STARTED, 0); }
    void set_poweroff()             { set(POWEROFF, 0); }
    void set_brightness(char light)  { set(BRIGHTNESS, light); }

private:
    QSerialPort m_tty;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static char m_queryPkg[7];
    static char m_setPkg[8];
    Probe m_probe;
    int m_probeFlag;

    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return m_tty.write(data, len); }

    QByteArray find_packet(QByteArray &data);
    void parse_packet(QByteArray &pkg);

    void query(Cmd cmd) { m_queryPkg[4] = cmd; write(m_queryPkg, sizeof(m_queryPkg)); }
    void set(Cmd cmd, char value) { m_setPkg[4] = cmd; m_setPkg[5] = value; write(m_setPkg, sizeof(m_setPkg));}

private slots:
    void on_readyRead_event();
};

#endif // __MCU_IMX_H__
