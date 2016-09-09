#ifndef __MCU_OMAP_H__
#define __MCU_OMAP_H__

#include "mcu_p.h"

class McuOmap : public McuPrivate
{
    Q_OBJECT
public:
    McuOmap();
    ~McuOmap(){}
    void query(Mcu::Cmd cmd) { Q_UNUSED(cmd); }
    void set(Mcu::Cmd cmd, char value) { Q_UNUSED(cmd); Q_UNUSED(value); }
private:
    QSerialPort m_ttyDev1;
private slots:
    void on_readyRead_event() {}
    void on_ttyDev1_readyRead_event();
};



#endif
