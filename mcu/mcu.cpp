#include "mcu.h"




#define DEF_SERIAL_NODE "/dev/ttymxc2"
#define DEF_PACKET_HEADER "\xff\xff"
#define DEF_PACKET_TAILER "\xfe\xfe"
#define DEF_DATA_ARRAY_HEADER 0xff
#define DEF_DATA_ARRAY_TAILER 0xfe

Mcu *Mcu::m_mcu = NULL;

const char Mcu::m_queryBatteryData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x32, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryBattery_2_Data[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x36, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};


const char Mcu::m_queryCoreTemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x10, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryFPGATemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x11, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPowerSupplyTemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x12, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryMCUTemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x13, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

char Mcu::m_setBrightnessData[8]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x53, 0x01, 0x42, 0x0, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryBrightnessData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x42, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_respondSTM32PowerOffData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x50, 0x0, 0x41, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

/* just for test */
const char Mcu::m_queryLongData[14]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x36, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_HEADER, 0x23, 0x52, DEF_DATA_ARRAY_HEADER, 0x24, 0x80, 0x23};
/* just for test end*/

/********************************************************************/
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

    if(false == setDataBits(QSerialPort::Data8)){
            qDebug("setDataBits error!\n");
        }

    if(false == setFlowControl(QSerialPort::NoFlowControl)){
        qDebug("setFlowControl error!\n");
    }

    if(false == setStopBits(QSerialPort::OneStop)){
        qDebug("setStopBits error!\n");
    }
    if(false == setParity(QSerialPort::NoParity)){
        qDebug("setParity error!\n");
    }


    if(false == open(QIODevice::ReadWrite)){
        qDebug("Serial Open Error!\n");
    }


    m_CMDHash.insert(CORE_TEMPERATURE, 0x10);
    m_CMDHash.insert(FPGA_TEMPERATURE, 0x11);
    m_CMDHash.insert(POWERSUPPLY_TEMPERATURE, 0x12);
    m_CMDHash.insert(MCU_TEMPERATURE, 0x13);
    m_CMDHash.insert(KEY, 0x21);
    m_CMDHash.insert(ROTARY, 0x22);
    m_CMDHash.insert(BATTERY1_STATUS, 0x31);
    m_CMDHash.insert(BATTERY1_QUANTITY, 0x32);
    m_CMDHash.insert(BATTERY2_STATUS, 0x35);
    m_CMDHash.insert(BATTERY2_QUANTITY, 0x36);
    m_CMDHash.insert(POWEROFF, 0x41);
    m_CMDHash.insert(BRIGHTNESS, 0x42);
    m_CMDHash.insert(MAIN_APP_READY, 0x43);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_MODEL, 0x51);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_SERIES, 0x52);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_TYPE, 0x53);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_FREQUNCY, 0x54);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_ELEMENTS_QTY, 0x55);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_ELEMENTS_DISTANCE, 0x56);
    m_CMDHash.insert(PAHSED_ARRAY_PROBE_FERENCE_POINT, 0x57);
    m_CMDHash.insert(NORMAL_PROBE_1_MODEL, 0x61);
    m_CMDHash.insert(NORMAL_PROBE_1_SERIES, 0x62);
    m_CMDHash.insert(NORMAL_PROBE_1_FRENQUNCY, 0x63);
    m_CMDHash.insert(NORMAL_PROBE_1_SIZE, 0x64);
    m_CMDHash.insert(NORMAL_PROBE_2_MODEL, 0x71);
    m_CMDHash.insert(NORMAL_PROBE_2_SERIES, 0x72);
    m_CMDHash.insert(NORMAL_PROBE_2_FRENQUNCY, 0x73);
    m_CMDHash.insert(NORMAL_PROBE_2_SIZE, 0x74);




}

Mcu::~Mcu()
{
    close();
}


void Mcu::parsePacket(QByteArray &read_array)
{
    EventType sig_type;
    QByteArray sig_val;
    int tmp_size;
    int tmp_len;

    tmp_len = QVariant((unsigned char)read_array[3]).toInt();
    tmp_size = read_array.size();
    if(tmp_size<7 && ((tmp_len+7)!=read_array.size())){
        return;
    }
    else{
        sig_type = m_CMDHash.key(QVariant((unsigned char)read_array[4]).toInt());
        sig_val = read_array.right(tmp_len+2);
        sig_val = sig_val.left(tmp_len);
        qDebug() << "In parse, parse ok! [" << __func__ << "], L: " << __LINE__ << ", sig_val: " << sig_val.toHex() << endl;
        emit event(sig_type, sig_val);
    }

}


QByteArray Mcu::findPacket(QByteArray &read_array)
{
    QByteArray tmp_array;
    int tmp_index_header;
    int tmp_index_tailer;
    uint8_t tmp_type;

findPacket_Judge_packet_label:

    qDebug() << "Into find pkg" << endl;
    tmp_index_header = read_array.indexOf(DEF_PACKET_HEADER);
    tmp_index_tailer = read_array.indexOf(DEF_PACKET_TAILER);
    tmp_type = QVariant((unsigned char)read_array[tmp_index_header+2]).toInt();

    if(read_array.contains(DEF_PACKET_HEADER) && read_array.contains(DEF_PACKET_TAILER)){//contains one or more packets.
        if(tmp_index_header > tmp_index_tailer){//if there is a illegal tailer before the header,cut the tailer and the front of illegal TAILER.
            qDebug() << "pkg tail and header position error!" << endl;
            read_array = read_array.right(read_array.size()-tmp_index_tailer-2);
            goto findPacket_Judge_packet_label;
        }
        else if(tmp_type>0x53 || tmp_type<0x4f){
           qDebug() << "pkg type error!" << endl;
           read_array = read_array.right(read_array.size()-tmp_index_tailer-2);
           goto findPacket_Judge_packet_label;
        }
        else
        {
            tmp_array = read_array.right(read_array.size()-tmp_index_header);
            tmp_array = tmp_array.left(tmp_array.indexOf(DEF_PACKET_TAILER)+2);
            read_array = read_array.right(read_array.size()-tmp_index_tailer-2);
            qDebug() << "corrent pkg found" << endl;
            return tmp_array;
        }
    }
    else
    {
        tmp_array.clear();
        return tmp_array;
    }

    qDebug() << "findPacket, [" << __func__ << "], L: " << __LINE__ << ",tmp_array:" << tmp_array.toHex() << endl;

}



void Mcu::on_readyRead_event()
{

    QByteArray byte = readAll();
    /*开始解析数据*/

    m_recBuffer.append(byte);
    qDebug() << "Afer append,[" << __func__ << "], L: " << __LINE__ << ", m_recBuffer: " << m_recBuffer.toHex() << endl;
    while(1) {
        QByteArray pkg = findPacket(m_recBuffer);
        if (pkg.isEmpty()) {
            qDebug() << "pkg is empty " << endl;
            break;
        }
        qDebug() << "Afer While(1),[" << __func__ << "], L: " << __LINE__ << ", m_recBuffer: " << m_recBuffer.toHex() << endl;
        parsePacket(pkg);
    }
    qDebug() << "Org data: " << byte.toHex() << endl;

}
