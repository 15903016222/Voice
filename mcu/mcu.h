#ifndef MCU_H
#define MCU_H

#include <qmutex.h>
#include "QtSerialPort"
#include "stdint.h"
#include "QHash"
#include <QDebug>

class Mcu : public QSerialPort
{
    Q_OBJECT
public:
    enum EventType {
        CORE_TEMPERATURE = 0x10,//核心板温度	0x10
        FPGA_TEMPERATURE = 0x11,//FPGA温度	0x11
        POWERSUPPLY_TEMPERATURE = 0x12,//电源温度	0x12
        MCU_TEMPERATUREE = 0x13,//MCU温度	0x13
        KEY = 0x21,//按键	0x21
        ROTARY = 0x22,//飞梭	0x22
        BATTERY1_STATUS = 0x31,//1号电池状态	0x31
        BATTERY2_STATUS = 0x35,//2号电池状态	0x35
        BATTERY1_QUANTITY = 0x32,//1号电池电量	0x32
        BATTERY2_QUANTITY = 0x36,//2号电池电量	0x36
        POWEROFF = 0x41,//关机	0x41
        BRIGHTNESS = 0x42,//背光亮度	0x42
        MAIN_APP_READY = 0x43,//主程序启动通知	0x43
        PAHSED_ARRAY_PROBE_MODEL = 0x51,//相控阵探头型号	0x51
        PAHSED_ARRAY_PROBE_SERIES = 0x52,//相控阵探头系列	0x52
        PAHSED_ARRAY_PROBE_TYPE = 0x53,//相控阵探头类型	0x53
        PAHSED_ARRAY_PROBE_FREQUNCY = 0x54,//相控阵探头频率	0x54
        PAHSED_ARRAY_PROBE_ELEMENTS_QTY = 0x55,//相控阵探头阵元数	0x55
        PAHSED_ARRAY_PROBE_ELEMENTS_DISTANCE = 0x56,//相控阵探头阵元间距	0x56
        PAHSED_ARRAY_PROBE_FERENCE_POINT = 0x57,//相控阵探头参考点	0x57
        NORMAL_PROBE_1_MODEL = 0x61,//常规探头I型号	0x61
        NORMAL_PROBE_1_SERIES = 0x64,//常规探头I系列	0x62
        NORMAL_PROBE_1_FRENQUNCY = 0x63,//常规探头I频率	0x63
        NORMAL_PROBE_1_SIZE = 0x64,//常规探头I晶片尺寸	0x64
        NORMAL_PROBE_2_MODEL = 0x71,//常规探头Ii型号	0x71
        NORMAL_PROBE_2_SERIES = 0x72,//常规探头Ii系列	0x72
        NORMAL_PROBE_2_FRENQUNCY = 0x73,//常规探头iI频率	0x73
        NORMAL_PROBE_2_SIZE = 0x74,//常规探头Ii晶片尺寸	0x74
    };

    static Mcu* get_mcu();
    static void destroyed();

    void query_core_temp() { qDebug()<<__func__; write(m_queryCoreTemperatureData, sizeof(m_queryCoreTemperatureData)); }
    void query_FPGA_temp() { qDebug()<<__func__; write(m_queryFPGATemperatureData, sizeof(m_queryFPGATemperatureData)); }
    void query_PowerSupply_temp() { qDebug()<<__func__; write(m_queryPowerSupplyTemperatureData, sizeof(m_queryPowerSupplyTemperatureData)); }
    void query_MCU_temp() { qDebug()<<__func__; write(m_queryMCUTemperatureData, sizeof(m_queryMCUTemperatureData)); }
    void query_battery() { qDebug()<<__func__; write(m_queryBatteryData, sizeof(m_queryBatteryData)); }
    void query_battery2() { qDebug()<<__func__; write(m_queryBattery_2_Data, sizeof(m_queryBattery_2_Data)); }
    void query_batteryStatus() { qDebug()<<__func__; write(m_queryBatteryStatus, sizeof(m_queryBatteryStatus)); }
    void query_battery2Status() { qDebug()<<__func__; write(m_queryBattery_2_Status, sizeof(m_queryBattery_2_Status)); }
    void set_mainAPPReady() { qDebug()<<__func__; write(m_mainAPPReady, sizeof(m_mainAPPReady)); }
    void query_brightness() { qDebug()<<__func__; write(m_queryBrightnessData, sizeof(m_queryBrightnessData)); }
    void set_poweroff(EventType event_type) { qDebug()<<__func__; if(event_type==0x41) write(m_respondSTM32PowerOffData, sizeof(m_respondSTM32PowerOffData)); }
    qint64 set_brightness(uint8_t light) { qDebug()<<__func__; m_setBrightnessData[5]=light; return write(m_setBrightnessData, sizeof(m_setBrightnessData)); }

    void query_pashedArrayProbeModel()  { qDebug()<<__func__; write(m_queryPashedArrayProbeModel, sizeof(m_queryPashedArrayProbeModel)); }
    void query_pashedArrayProbeSeries()  { qDebug()<<__func__; write(m_queryPashedArrayProbeSeries, sizeof(m_queryPashedArrayProbeSeries)); }
    void query_pashedArrayProbeType()  { qDebug()<<__func__; write(m_queryPashedArrayProbeType, sizeof(m_queryPashedArrayProbeType)); }
    void query_pashedArrayProbeFreq()  { qDebug()<<__func__; write(m_queryPashedArrayProbeFreq, sizeof(m_queryPashedArrayProbeFreq)); }
    void query_pashedArrayProbeElements()  { qDebug()<<__func__; write(m_queryPashedArrayProbeElements, sizeof(m_queryPashedArrayProbeElements)); }
    void query_pashedArrayProbeElementsDistance()  {qDebug()<<__func__;  write(m_queryPashedArrayProbeElementsDist, sizeof(m_queryPashedArrayProbeElementsDist)); }
    void query_pashedArrayProbeFerencePoint()  { qDebug()<<__func__; write(m_queryPashedArrayProbeFerencePoint, sizeof(m_queryPashedArrayProbeFerencePoint)); }

    /****** just for special test ******/
    void query_half1() { write(m_queryBattery_2_Data, 3); }
    void query_half2() { write(m_queryBattery_2_Data+3, 4); }
    void query_longdata() { write(m_queryLongData, sizeof(m_queryLongData)); }
    /****** just for special test end******/


Q_SIGNALS:
    void event(EventType type, QByteArray &val);

protected:
    Mcu();
    ~Mcu();

private:
    static Mcu *m_mcu;
    QMutex wrMutex;
    QByteArray m_recBuffer;
    static const char m_queryBatteryData[7];
    static const char m_queryBattery_2_Data[7];
    static const char m_queryBrightnessData[7];
    static char m_setBrightnessData[8];
    static const char m_queryCoreTemperatureData[7];
    static const char m_queryFPGATemperatureData[7];
    static const char m_queryPowerSupplyTemperatureData[7];
    static const char m_queryMCUTemperatureData[7];
    static const char m_respondSTM32PowerOffData[7];

    static const char m_queryBatteryStatus[7];
    static const char m_queryBattery_2_Status[7];
    static const char m_mainAPPReady[7];
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





    /*just for test*/
    static const char m_queryLongData[14];
    /*juset for test end*/

    inline qint64 write(const char *data, qint64 len) {QMutexLocker locker(&wrMutex); return QIODevice::write(data, len); }
    void on_readyRead_event();
    QByteArray findPacket(QByteArray &read_array);
    void parsePacket(QByteArray &read_array);

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
