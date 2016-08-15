#include "mcu.h"

Mcu *Mcu::m_mcu = NULL;

Mcu::Mcu()
    :QSerialPort("/dev/ttyMUX2")
{
    connect(this, &Mcu::readyRead, this, &Mcu::on_readyRead_event);
    open(QIODevice::ReadWrite);
    setBaudRate(Baud115200);
    setDataBits(Data8);
    setFlowControl(NoFlowControl);
    setStopBits(OneStop);
    setParity(OddParity);
}

Mcu::~Mcu()
{
    close();
}

void Mcu::on_readyRead_event()
{
    EventType type;
    int val = 0;
    QByteArray byte = readAll();
    /*开始解析数据*/

    /*发送信号*/
    emit event(type, val);
}
