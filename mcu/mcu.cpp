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

    qDebug() << "byte size:" << byte.size() << endl;

    if(byte.contains("$$P") || byte.contains("$$Q") || byte.contains("$$R") || byte.contains("$$S")){/*packet header correct*/
        qDebug("In Contain!");
        m_recBuffer.clear();
        m_recBuffer = byte.right(byte.size() - byte.indexOf("$$"));
        qDebug() << "After In, m_recBuffer:" << m_recBuffer.toHex() << endl;

    }
    else{/*packet header dose not appear, append to the prvious array*/
        qDebug("Not Contain!");
        m_recBuffer.append(byte);
        if(m_recBuffer.contains("$$P") || m_recBuffer.contains("$$Q") || m_recBuffer.contains("$$R") || m_recBuffer.contains("$$S")){
            m_recBuffer = m_recBuffer.right(m_recBuffer.size() - m_recBuffer.indexOf("$$"));
        qDebug() << "After Not, m_recBuffer:" << m_recBuffer.toHex() << endl;
        }


    }


    if(m_recBuffer.indexOf("##") > -1){
        if(m_recBuffer.indexOf("##") - m_recBuffer.indexOf("$$")<4){/*wrong length of pack!*/
            m_recBuffer = m_recBuffer.right(m_recBuffer.size() - (m_recBuffer.indexOf("##")+2));
            qDebug() << "m_recBuffer 01: " << m_recBuffer.toHex() << endl;
        }
        else{/*length of packet correct*/
            qDebug() << "m_recBuffer 02: " << m_recBuffer.toHex() << endl;
            switch(QVariant((unsigned char)m_recBuffer[2]).toInt())/*what type of packet??*/
            {
            qDebug() << "m_recBuffer[2]:" << QVariant((unsigned char)m_recBuffer[3]).toInt() << endl;
            case 0x50:/*ack*/
                switch(QVariant((unsigned char)m_recBuffer[3]).toInt())
                {
                case 0x10:/*core pcb temperature*/
                    type = CORE_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x11:/*FPGA temperature*/
                    type = FPGA_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x12:/*power supply temperature*/
                    type = POWERSUPPLY_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x13:/*MCU temperature*/
                    type = MCU_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x31:/*battery1 */
                    type = CORE_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x32:/*battery2 */
                    type = CORE_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x42:/*background brightness*/
                    type = CORE_TEMPERATURE;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                default:/*wrong cmd*/
                    qDebug() << "Wrong packet"<< endl;
                    val = 0;
                    break;
                }

                break;
            case 0x51:/*key or rotary of poweroff request*/
                switch(QVariant((unsigned char)m_recBuffer[3]).toInt())
                {
                case 0x21:/*key event*/
                    type =KEY;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x22:/*rotary event*/
                    type = ROTARY;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                case 0x41:/*power off request*/
                    type = POWEROFF;
                    val = QVariant(m_recBuffer[4]).toInt();
                    break;
                default:/*wrong cmd*/
                    qDebug() << "Wrong packet"<< endl;
                    val = 0;
                    break;
                }
                break;


            default:/*invalued type*/
                break;

            }
            if(m_recBuffer.contains("###")){
                m_recBuffer = m_recBuffer.right(m_recBuffer.size() - (m_recBuffer.indexOf("##")+3));
            }
                else{
                m_recBuffer = m_recBuffer.right(m_recBuffer.size() - (m_recBuffer.indexOf("##")+2));
            }
            qDebug() << "type: " << type << "  val: " << val << endl;

        }
    }


    qDebug() << "Org data: " << byte.toHex() << endl;

    qDebug() << "m_recBuffer03" << m_recBuffer.toHex() << endl;


    /*发送信号*/
    emit event(type, val);
}
