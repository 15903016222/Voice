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

    enum EventType {
        CORE_TEMPERATURE            = 0x10, /* 核心板温度 */
        FPGA_TEMPERATURE            = 0x11, /* FPGA温度 */
        POWERSUPPLY_TEMPERATURE     = 0x12, /* 电源温度 */
        MCU_TEMPERATUREE            = 0x13, /* MCU温度 */
        KEY                         = 0x21, /* 按键 */
        ROTARY                      = 0x22, /* 飞梭 */
        BATTERY1_STATUS             = 0x31, /* 1号电池状态 */
        BATTERY2_STATUS             = 0x35, /* 2号电池状态 */
        BATTERY1_QUANTITY           = 0x32, /* 1号电池电量 */
        BATTERY2_QUANTITY           = 0x36, /* 2号电池电量 */
        POWEROFF                    = 0x41, /* 关机 */
        BRIGHTNESS                  = 0x42, /* 背光亮度 */
        MAIN_APP_READY              = 0x43, /* 主程序启动通知 */
        PAHSED_ARRAY_PROBE_MODEL    = 0x51, /* 相控阵探头型号 */
        PAHSED_ARRAY_PROBE_SERIES   = 0x52, /* 相控阵探头系列 */
        PAHSED_ARRAY_PROBE_TYPE     = 0x53, /* 相控阵探头类型 */
        PAHSED_ARRAY_PROBE_FREQUNCY = 0x54, /* 相控阵探头频率 */
        PAHSED_ARRAY_PROBE_ELEMENTS_QTY         = 0x55, /* 相控阵探头阵元数 */
        PAHSED_ARRAY_PROBE_ELEMENTS_DISTANCE    = 0x56, /* 相控阵探头阵元间距 */
        PAHSED_ARRAY_PROBE_FERENCE_POINT        = 0x57, /* 相控阵探头参考点 */
        NORMAL_PROBE_1_MODEL        = 0x61, /* 常规探头I型号 */
        NORMAL_PROBE_1_SERIES       = 0x64, /* 常规探头I系列 */
        NORMAL_PROBE_1_FRENQUNCY    = 0x63, /* 常规探头I频率 */
        NORMAL_PROBE_1_SIZE         = 0x64, /* 常规探头I晶片尺寸 */
        NORMAL_PROBE_2_MODEL        = 0x71, /* 常规探头Ii型号 */
        NORMAL_PROBE_2_SERIES       = 0x72, /* 常规探头Ii系列 */
        NORMAL_PROBE_2_FRENQUNCY    = 0x73, /* 常规探头iI频率 */
        NORMAL_PROBE_2_SIZE         = 0x74, /* 常规探头Ii晶片尺寸 */
    };

    static Mcu* get_mcu();
    static void destroyed();

    void query_core_temp() { write(m_queryCoreTemperatureData, sizeof(m_queryCoreTemperatureData)); }
    void query_fpga_temp() { write(m_queryFPGATemperatureData, sizeof(m_queryFPGATemperatureData)); }
    void query_power_temp() { write(m_queryPowerSupplyTemperatureData, sizeof(m_queryPowerSupplyTemperatureData)); }
    void query_mcu_temp() { write(m_queryMCUTemperatureData, sizeof(m_queryMCUTemperatureData)); }
    void query_first_battery() { write(m_queryFstBattery, sizeof(m_queryFstBattery)); }
    void query_second_battery() { write(m_querySndBattery, sizeof(m_querySndBattery)); }
    void query_first_battery_status() { write(m_queryFstBatteryStatus, sizeof(m_queryFstBatteryStatus)); }
    void query_second_battery_status() { write(m_querySndBattery_Status, sizeof(m_querySndBattery_Status)); }
    void notify_started() { write(m_nofityStarted, sizeof(m_nofityStarted)); }
    void query_brightness() { write(m_queryBrightnessData, sizeof(m_queryBrightnessData)); }
    void set_poweroff() { write(m_respondSTM32PowerOffData, sizeof(m_respondSTM32PowerOffData)); }
    qint64 set_brightness(uchar light) { m_setBrightnessData[5]=light; return write(m_setBrightnessData, sizeof(m_setBrightnessData)); }

    void query_pa_probe_model()  { write(m_queryPashedArrayProbeModel, sizeof(m_queryPashedArrayProbeModel)); }
    void query_pa_probe_series()  { write(m_queryPashedArrayProbeSeries, sizeof(m_queryPashedArrayProbeSeries)); }
    void query_pa_probe_type()  { write(m_queryPashedArrayProbeType, sizeof(m_queryPashedArrayProbeType)); }
    void query_pa_probe_freq()  { write(m_queryPashedArrayProbeFreq, sizeof(m_queryPashedArrayProbeFreq)); }
    void query_pa_probe_elements()  { write(m_queryPashedArrayProbeElements, sizeof(m_queryPashedArrayProbeElements)); }
    void query_pa_probe_elements_distance()  { write(m_queryPashedArrayProbeElementsDist, sizeof(m_queryPashedArrayProbeElementsDist)); }
    void query_pa_probe_ference_point()  { write(m_queryPashedArrayProbeFerencePoint, sizeof(m_queryPashedArrayProbeFerencePoint)); }


Q_SIGNALS:
    void event(EventType type, QByteArray &val);

protected:
    Mcu();
    ~Mcu() { close(); }

private:
    static Mcu *m_mcu;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static const char m_queryFstBattery[7];
    static const char m_querySndBattery[7];
    static const char m_queryBrightnessData[7];
    static char m_setBrightnessData[8];
    static const char m_queryCoreTemperatureData[7];
    static const char m_queryFPGATemperatureData[7];
    static const char m_queryPowerSupplyTemperatureData[7];
    static const char m_queryMCUTemperatureData[7];
    static const char m_respondSTM32PowerOffData[7];

    static const char m_queryFstBatteryStatus[7];
    static const char m_querySndBattery_Status[7];
    static const char m_nofityStarted[7];
    static const char m_queryPashedArrayProbeModel[7];
    static const char m_queryPashedArrayProbeSeries[7];
    static const char m_queryPashedArrayProbeType[7];
    static const char m_queryPashedArrayProbeFreq[7];
    static const char m_queryPashedArrayProbeElements[7];
    static const char m_queryPashedArrayProbeElementsDist[7];
    static const char m_queryPashedArrayProbeFerencePoint[7];
    static const char m_queryNormalProbe1Model[7];
    static const char m_queryNormalProbe1Series[7];
    static const char m_queryNormalProbe1Freq[7];
    static const char m_queryNormalProbe1Size[7];
    static const char m_queryNormalProbe2Model[7];
    static const char m_queryNormalProbe2Series[7];
    static const char m_queryNormalProbe2Freq[7];
    static const char m_queryNormalProbe2Size[7];

    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return QIODevice::write(data, len); }
    void on_readyRead_event();

    QByteArray findPacket(QByteArray &data);
    void parsePacket(QByteArray &pkg);

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
