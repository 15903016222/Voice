#ifndef MCU_H
#define MCU_H

#include <qmutex.h>
#include "QtSerialPort"
#include "stdint.h"
#include <QDebug>

class Mcu : public QSerialPort
{
    Q_OBJECT
public:
    static Mcu* get_mcu();
    static void destroyed();


    void query_core_temp() { write(m_queryCoreTemperatureData, sizeof(m_queryCoreTemperatureData)); }
    void query_FPGA_temp() { write(m_queryFPGATemperatureData, sizeof(m_queryFPGATemperatureData)); }
    void query_PowerSupply_temp() { write(m_queryPowerSupplyTemperatureData, sizeof(m_queryPowerSupplyTemperatureData)); }
    void query_MCU_temp() { write(m_queryMCUTemperatureData, sizeof(m_queryMCUTemperatureData)); }
    void query_battery() { write(m_queryBatteryData, sizeof(m_queryBatteryData)); }
    void query_battery2() { write(m_queryBattery_2_Data, sizeof(m_queryBattery_2_Data)); }
    void query_brightness() { write(m_queryBrightnessData, sizeof(m_queryBrightnessData)); }
    qint64 set_brightness(uint8_t light) { m_setBrightnessData[4]=light; return write(m_setBrightnessData, sizeof(m_setBrightnessData)); }


    enum EventType {
        CORE_TEMPERATURE,
        FPGA_TEMPERATURE,
        POWERSUPPLY_TEMPERATURE,
        MCU_TEMPERATURE,
        BATTERY1,
        BATTERY2,
        BRIGHTNESS,
        POWEROFF,
        KEY,
        ROTARY,
    };

Q_SIGNALS:
    void event(EventType type, int val);

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
    static char m_setBrightnessData[7];
    static const char m_queryCoreTemperatureData[7];
    static const char m_queryFPGATemperatureData[7];
    static const char m_queryPowerSupplyTemperatureData[7];
    static const char m_queryMCUTemperatureData[7];

    inline qint64 write(const char *data, qint64 len) {QMutexLocker locker(&wrMutex); return QIODevice::write(data, len); }
    void on_readyRead_event();
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
