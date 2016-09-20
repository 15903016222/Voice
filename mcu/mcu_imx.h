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
    void query_pa_probe();
    void notify_started()           { set(NOTIFY_STARTED, 0); }
    void set_poweroff()             { set(POWEROFF, 0); }
    void set_brightness(char light)  { set(BRIGHTNESS, light); }

private:
    QSerialPort m_tty;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static char m_queryPkg[7];
    static char m_setPkg[8];

    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return m_tty.write(data, len); }

    QByteArray find_packet(QByteArray &data);
    void parse_packet(QByteArray &pkg);

    void query(Mcu::Cmd cmd) { m_queryPkg[4] = cmd; write(m_queryPkg, sizeof(m_queryPkg)); }
    void set(Mcu::Cmd cmd, char value) { m_setPkg[4] = cmd; m_setPkg[5] = value; write(m_setPkg, sizeof(m_setPkg));}

private slots:
    void on_readyRead_event();
};

#endif // __MCU_IMX_H__
