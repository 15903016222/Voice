#ifndef __MCU_H__
#define __MCU_H__

#include "probe.h"

#include <QObject>
#include <QMutex>

class Mcu : public QObject
{
    Q_OBJECT
public:
    enum RotaryType {
        ROTARY_UP,
        ROTARY_DOWN
    };

    enum KeyType {
        KEY_INVALID,
        KEY_UP,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_DOWN,
        KEY_MENU,
        KEY_SURE,
        KEY_BACK,
        KEY_80_PERCENT,
        KEY_DISPLAY,
        KEY_START,
        KEY_STOP,
        KEY_SAVE,
        KEY_OPEN,
        KEY_GATE,
        KEY_CALIBRATION,
        KEY_DB,
        KEY_CURSOR,
        KEY_FREEZE,
        KEY_ANGLE,
        KEY_ERASURE,
        KEY_HELP,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12
    };

    enum BatteryStatus {
        DISCHARGE,
        CHARGE,
        NO_BATTERY,
        BATTERY_FULL,
        BATTERY_NO_WORK
    };

    enum TemperatureType {
        TEMPERATURE_CPU     = 0x10,
        TEMPERATURE_FPGA,
        TEMPERATURE_POWER,
        TEMPERATURE_MCU
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
    void key_event(Mcu::KeyType type);
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
