
#ifndef __MCU_P_H__
#define __MCU_P_H__

#include "mcu.h"

class McuPrivate : public QObject
{
    Q_OBJECT
public:
    explicit McuPrivate(QObject *parent=0) : QObject(parent) {}
    virtual ~McuPrivate() {}
    virtual void query(Mcu::Cmd cmd) = 0;
    virtual void set(Mcu::Cmd cmd, char value) = 0;
Q_SIGNALS:
//    void event(Mcu::Cmd cmd, QByteArray &val);
    void brightness_event(int val);
    void key_event(int val);
    void battery_status_event(int index, Mcu::BatteryStatus);
    void battery_quantity_event(int index, int quantity);
    void temperature_event(Mcu::TemperatureType type, int value);
    void pa_probe_event(Mcu::PaProbeAttrType type, const QByteArray &data);
    void poweroff_event();
};

#endif /* end of __MCU_P_H__ */
