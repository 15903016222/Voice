#include "mcu.h"

#define DEF_SERIAL_NODE "/dev/ttymxc3"
Mcu *Mcu::m_mcu = NULL;
const char Mcu::m_queryTempData[6]={0x24, 0x24, 0x52, 0x1, 0x23, 0x23};
const char Mcu::m_queryBatteryData[6]={0x24, 0x24, 0x52, 0x3, 0x23, 0x23};
const char Mcu::m_queryBrightnessData[6]={0x24, 0x24, 0x52, 0x6, 0x23, 0x23};
char Mcu::m_setBrightnessData[7]={0x24, 0x24, 0x53, 0x6, 0x0, 0x23, 0x23};

Mcu::Mcu()
    :QSerialPort(DEF_SERIAL_NODE)
{
    connect(this, &Mcu::readyRead, this, &Mcu::on_readyRead_event);

    setPortName(DEF_SERIAL_NODE);
    if(false == setBaudRate(QSerialPort::Baud115200)){
        qDebug("setBaudRate error!\n");
    }
    else{
        qDebug("setBaudRate OK!\n");
    }
    if(false == setDataBits(QSerialPort::Data8)){
            qDebug("setDataBits error!\n");
        }
    else{
        qDebug("setDataBits OK!\n");
    }
    if(false == setFlowControl(QSerialPort::NoFlowControl)){
        qDebug("setFlowControl error!\n");
    }
    else{
        qDebug("setFlowControl OK!\n");
    }
    if(false == setStopBits(QSerialPort::OneStop)){
        qDebug("setStopBits error!\n");
    }
    if(false == setParity(QSerialPort::NoParity)){
        qDebug("setParity error!\n");
    }
    else{
       qDebug("setParity OK!\n");
    }

    if(false == open(QIODevice::ReadWrite)){
        qDebug("Serial Open Error!\n");
    }
    else{
        qDebug("Serial Open OK!\n");
    }
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
    qDebug("arr:%s\n",byte.data());
    /*发送信号*/
    emit event(type, val);
}
