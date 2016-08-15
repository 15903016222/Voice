#ifndef MCU_H
#define MCU_H

#include <QtSerialPort>

class Mcu : public QSerialPort
{
    Q_OBJECT
public:
    static Mcu* get_mcu();
    static void destroyed();

    void query_temp() { write(m_queryTempData, sizeof(m_queryTempData)); }
    void query_battery() { write(m_queryTempData, sizeof(m_queryTempData)); }
    void query_brightness() { write(m_queryTempData, sizeof(m_queryTempData)); }
    void set_brightness(int light) { write(m_queryTempData, sizeof(m_queryTempData)); }

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

    inline qint64 write(const char *data, qint64 len) { QMutexLocker locker(&wrMutex); return QIODevice::write(data, len); }
    void on_readyRead_event();
};

const char Mcu::m_queryTempData[6]={0x24, 0x24, 0x52, 0x1, 0x23, 0x23};
const char Mcu::m_queryBatteryData[6]={0x24, 0x24, 0x52, 0x1, 0x23, 0x23};

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
