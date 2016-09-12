
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
    void event(Mcu::Cmd cmd, QByteArray &val);
};

#endif /* end of __MCU_P_H__ */
