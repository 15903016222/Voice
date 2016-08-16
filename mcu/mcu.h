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

    void query_temp() { write(m_queryTempData, sizeof(m_queryTempData)); }
    void query_battery() { write(m_queryBatteryData, sizeof(m_queryBatteryData)); }
    void query_brightness() { write(m_queryBrightnessData, sizeof(m_queryBrightnessData)); }
    qint64 set_brightness(uint8_t light) { m_setBrightnessData[4]=light; return write(m_setBrightnessData, sizeof(m_setBrightnessData)); }

    enum EventType {
        TEMPERATURE,
        BATTERY,
        BRIGHTNESS,
        POWEROFF,
        KEY,
    };

Q_SIGNALS:
    void event(EventType type, int val);

protected:
    Mcu();
    ~Mcu();

private:
    static Mcu *m_mcu;
    QMutex wrMutex;

    static const char m_queryTempData[6];
    static const char m_queryBatteryData[6];
    static const char m_queryBrightnessData[6];
    static char m_setBrightnessData[7];

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
