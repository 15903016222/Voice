#ifndef __MCU_OMAP_H__
#define __MCU_OMAP_H__

#include "mcu_p.h"

#include <QSerialPort>
#include <QMap>

class McuOmap : public McuPrivate
{
    Q_OBJECT

public:
    McuOmap();

    void query(Mcu::Cmd cmd);
    void set(Mcu::Cmd cmd, char value);

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



#endif
