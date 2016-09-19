#ifndef __MCU_OMAP_H__
#define __MCU_OMAP_H__

#include "mcu.h"

#include <QSerialPort>
#include <QMap>

class McuOmap : public Mcu
{
    Q_OBJECT

public:
    McuOmap();
    void query_core_temp()          { }
    void query_fpga_temp()          { }
    void query_power_temp()         { }
    void query_mcu_temp()           { }
    void query_first_battery()      { }
    void query_second_battery()     { }
    void query_first_battery_status() { }
    void query_second_battery_status(){ }
    void query_brightness();
    void query_pa_probe_model()     { }
    void query_pa_probe_series()    { }
    void query_pa_probe_type()      { }
    void query_pa_probe_freq()      { }
    void query_pa_probe_elements()  { }
    void query_pa_probe_elements_distance() { }
    void query_pa_probe_ference_point()     { }
    void notify_started() {}
    void set_poweroff();
    void set_brightness(char light);

private:
    QSerialPort m_ttyS0;
    QSerialPort m_ttyS1;

    char m_brightness;      /* used by ttyS1 */
    QByteArray m_buffer;    /* used by ttyS1 */

    QMap<int, Mcu::BatteryStatus> m_statusMap;

    void init_tty(QSerialPort &tty);

private slots:
    void on_ttyS0_readyRead_event();
    void on_ttyS1_readyRead_event();
};

inline void McuOmap::query_brightness()
{
    emit brightness_event(m_brightness);
}

inline void McuOmap::set_brightness(char light)
{
    m_ttyS1.write(&light, 1);
    m_brightness = light;
}

inline void McuOmap::set_poweroff()
{
    char value = 0xaa;
    m_ttyS1.write(&value, 1);
    m_ttyS1.write(&value, 1);
    m_ttyS1.write(&value, 1);
}

#endif
