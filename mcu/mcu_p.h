
#ifndef __MCU_P_H__
#define __MCU_P_H__

#include "mcu.h"
#include <QSerialPort>

class McuPrivate : public QSerialPort
{
    Q_OBJECT
public:
    McuPrivate(const QString &name) : QSerialPort(name) {}
    virtual ~McuPrivate() {}
    virtual void query(Mcu::Cmd cmd) = 0;
    virtual void set(Mcu::Cmd cmd, int value) {Q_UNUSED(cmd); Q_UNUSED(value);}
Q_SIGNALS:
    void event(Mcu::Cmd cmd, QByteArray &val);
};

#endif /* end of __MCU_P_H__ */
