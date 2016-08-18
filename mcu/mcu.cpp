#include "mcu.h"

#define DEF_SERIAL_NODE "/dev/ttymxc2"
#define DEF_PACKET_HEADER 0X24
Mcu *Mcu::m_mcu = NULL;

const char Mcu::m_queryBatteryData[7]={0x24, 0x24, 0x52, 0x31, 0x0, 0x23, 0x23};
const char Mcu::m_queryBattery_2_Data[7]={0x24, 0x24, 0x52, 0x32, 0x0, 0x23, 0x23};


const char Mcu::m_queryCoreTemperatureData[7]={0x24, 0x24, 0x52, 0x10, 0x0, 0x23, 0x23};
const char Mcu::m_queryFPGATemperatureData[7]={0x24, 0x24, 0x52, 0x11, 0x0, 0x23, 0x23};
const char Mcu::m_queryPowerSupplyTemperatureData[7]={0x24, 0x24, 0x52, 0x12, 0x0, 0x23, 0x23};
const char Mcu::m_queryMCUTemperatureData[7]={0x24, 0x24, 0x52, 0x13, 0x0, 0x23, 0x23};

char Mcu::m_setBrightnessData[7]={0x24, 0x24, 0x53, 0x42, 0x0, 0x23, 0x23};
const char Mcu::m_queryBrightnessData[7]={0x24, 0x24, 0x52, 0x42, 0x0, 0x23, 0x23};

Mcu::Mcu()
    :QSerialPort(DEF_SERIAL_NODE)
{
    connect(this, &Mcu::readyRead, this, &Mcu::on_readyRead_event);
    m_recBuffer.clear();
    m_recBuffer.fill(0);
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

    type = this->KEY;

    QByteArray byte = readAll();
    /*开始解析数据*/
    if(byte.contains("$$")){
        m_recBuffer.clear();
        m_recBuffer = byte.right(byte.indexOf("$$"));
    }
    else{
        m_recBuffer.append(byte);
    }

//    qDebug() << byte.size();
    qDebug() << m_recBuffer.toHex();
//    qDebug() << QVariant((unsigned char)byte[1]).toInt();
//    qDebug() << byte.toHex();

    /*发送信号*/
    emit event(type, val);
}
