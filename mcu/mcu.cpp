#include "mcu.h"

Mcu *Mcu::m_mcu = NULL;
const char Mcu::m_queryTempData[6]={0x24, 0x24, 0x52, 0x1, 0x23, 0x23};
const char Mcu::m_queryBatteryData[6]={0x24, 0x24, 0x52, 0x3, 0x23, 0x23};
const char Mcu::m_queryBrightnessData[6]={0x24, 0x24, 0x52, 0x6, 0x23, 0x23};
char Mcu::m_setBrightnessData[7]={0x24, 0x24, 0x53, 0x6, 0x0, 0x23, 0x23};

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
