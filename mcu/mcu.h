#ifndef __MCU_H__
#define __MCU_H__

#include <QMutex>
#include <QtSerialPort>
#include <QByteArray>

/**
 * mcu package format
 * -------------------------------------------------------
 * | 0xff | 0xff | TYPE | LEN | CMD | DATA | 0xfe | 0xfe |
 * -------------------------------------------------------
 */

class Mcu : public QSerialPort
{
    Q_OBJECT
public:

    enum PkgType {
        RespondPkg = 0x50,  /* 应答包 */
        EventPkg,           /* 事件包 */
        QueryPkg,           /* 查询包 */
        SettingPkg          /* 设置包 */
    };

    enum PkgCmd {
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

    static Mcu* get_mcu();
    static void destroyed();

    void query_core_temp()      { query(CORE_TEMPERATURE); }
    void query_fpga_temp()      { query(FPGA_TEMPERATURE); }
    void query_power_temp()     { query(POWER_TEMPERATURE); }
    void query_mcu_temp()       { query(MCU_TEMPERATUREE); }
    void query_first_battery()  { query(BATTERY1_QUANTITY); }
    void query_second_battery() { query(BATTERY2_QUANTITY); }
    void query_first_battery_status()   { query(BATTERY1_STATUS); }
    void query_second_battery_status()  { query(BATTERY2_STATUS); }
    void query_brightness()             { query(BRIGHTNESS); }

    /* pa probe query */
    void query_pa_probe_model()     { query(PA_PROBE_MODEL); }
    void query_pa_probe_series()    { query(PA_PROBE_SERIES); }
    void query_pa_probe_type()      { query(PA_PROBE_TYPE); }
    void query_pa_probe_freq()      { query(PA_PROBE_FREQ); }
    void query_pa_probe_elements()  { query(PA_PROBE_ELEMENTS_QTY); }
    void query_pa_probe_elements_distance() { query(PA_PROBE_ELEMENTS_DISTANCE); }
    void query_pa_probe_ference_point()     { query(PA_PROBE_FERENCE_POINT); }


    void notify_started()   { write(m_nofityStarted, sizeof(m_nofityStarted)); }
    void set_poweroff()     { write(m_setPoweroff, sizeof(m_setPoweroff)); }
    qint64 set_brightness(uchar light) { m_setBrightnessData[5]=light; return write(m_setBrightnessData, sizeof(m_setBrightnessData)); }

Q_SIGNALS:
    void event(PkgCmd cmd, QByteArray &val);

protected:
    Mcu();
    ~Mcu() { close(); }

private:
    static Mcu *m_mcu;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static char m_queryPkg[7];
    static char m_setBrightnessData[8];
    static const char m_setPoweroff[7];
    static const char m_nofityStarted[7];

    void query(PkgCmd cmd) { m_queryPkg[4] = cmd; write(m_queryPkg, sizeof(m_queryPkg)); }
    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return QIODevice::write(data, len); }
    void on_readyRead_event();

    QByteArray find_packet(QByteArray &data);
    void parse_packet(QByteArray &pkg);
};


inline Mcu* Mcu::get_mcu()
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

#endif // MCU_H
