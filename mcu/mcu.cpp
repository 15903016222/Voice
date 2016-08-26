#include "mcu.h"




#define DEF_SERIAL_NODE "/dev/ttymxc2"
#define DEF_PACKET_HEADER "\xff\xff"
#define DEF_PACKET_TAILER "\xfe\xfe"
#define DEF_DATA_ARRAY_HEADER 0xff
#define DEF_DATA_ARRAY_TAILER 0xfe

Mcu *Mcu::m_mcu = NULL;

const char Mcu::m_queryBatteryData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x32, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryBattery_2_Data[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x36, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_queryBatteryStatus[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x31, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryBattery_2_Status[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x35, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_queryCoreTemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x10, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryFPGATemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x11, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPowerSupplyTemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x12, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryMCUTemperatureData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x13, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

char Mcu::m_setBrightnessData[8]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x53, 0x01, 0x42, 0x0, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryBrightnessData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x42, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_respondSTM32PowerOffData[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x53, 0x0, 0x41, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_mainAPPReady[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x53, 0x0, 0x43, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_queryPashedArrayProbeModel[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x51, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPashedArrayProbeSeries[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x52, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPashedArrayProbeType[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x53, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPashedArrayProbeFreq[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x54, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPashedArrayProbeElements[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x55, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPashedArrayProbeElementsDist[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x56, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryPashedArrayProbeFerencePoint[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x57, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_queryNormalProbe1Model[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x61, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryNormalProbe1Series[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x62, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryNormalProbe1Freq[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x63, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryNormalProbe1Size[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x64, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

const char Mcu::m_queryNormalProbe2Model[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x71, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryNormalProbe2Series[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x72, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryNormalProbe2Freq[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x73, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};
const char Mcu::m_queryNormalProbe2Size[7]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x52, 0x0, 0x74, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER};

/* just for test */
const char Mcu::m_queryLongData[14]={DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x0, 0xfe, DEF_DATA_ARRAY_HEADER, DEF_DATA_ARRAY_HEADER, 0x53, 0x0, 0x43, DEF_DATA_ARRAY_TAILER, DEF_DATA_ARRAY_TAILER, 0x80, 0x23};
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

}

Mcu::~Mcu()
{
    close();
}


void Mcu::parsePacket(QByteArray &read_array)
{
    QByteArray sig_val;
    int tmp_size;
    int tmp_len;

    tmp_len = QVariant((unsigned char)read_array[3]).toInt();
    tmp_size = read_array.size();
    qDebug() << "pkg size:" << tmp_size << endl;

    if(tmp_size<7){
        return;
    }
    else{

        sig_val = read_array.right(tmp_len+2);
        sig_val = sig_val.left(tmp_len);
        qDebug() << "Parse OK,[" << __func__ << "], L:_" << __LINE__ << "_, type:"<< read_array[4] << ",sig_val:" << sig_val.toHex() << endl;
        emit event(static_cast<EventType>(QVariant((unsigned char)read_array[4]).toUInt()), sig_val);
    }

}


QByteArray Mcu::findPacket(QByteArray &read_array)
{
    QByteArray tmp_array;
    int tmp_index_header;
    int tmp_index_tailer;
    uint8_t tmp_type;
    uint tmp_len;
    uint8_t tmp_len_tailer1, tmp_len_tailer2;

findPacket_Judge_packet_label:

    qDebug() << "finding pkg" << endl;
    tmp_index_header = read_array.indexOf(DEF_PACKET_HEADER);
    if(tmp_index_header<0){
        qDebug() << "Find pkg: index_Header -1 "<< endl;
        tmp_array.clear();
        return tmp_array;
    }
    tmp_index_tailer = read_array.indexOf(DEF_PACKET_TAILER);
    if(tmp_index_tailer<0){
        qDebug() << "Find pkg: index_Tailer -1 "<< endl;
        tmp_array.clear();
        return tmp_array;
    }
    tmp_type = QVariant((unsigned char)read_array[tmp_index_header+2]).toInt();
    tmp_len = QVariant((unsigned char)read_array[tmp_index_header+3]).toInt();
    tmp_len_tailer1 = QVariant((unsigned char)read_array[tmp_index_header+5+tmp_len]).toInt();
    tmp_len_tailer2 = QVariant((unsigned char)read_array[tmp_index_header+6+tmp_len]).toInt();

    if(tmp_index_header > tmp_index_tailer){
        qDebug() << "pkg tail and header position error!" << endl;
        read_array = read_array.right(read_array.size()-tmp_index_tailer-2);
        goto findPacket_Judge_packet_label;
    }
    else if(tmp_len_tailer1 !=0xfe || tmp_len_tailer2!=0xfe ){
        read_array = read_array.right(read_array.size()-tmp_index_header-2);
        qDebug() << "Find pkg: read_array: "<< read_array.toHex() << endl;
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
    qDebug() << "Correct pkg found" << endl;
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
