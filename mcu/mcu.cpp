#include "mcu.h"

#include <QDebug>

#define UART_DEVICE         "/dev/ttymxc2"
#define PKG_BEGIN_STRING    "\xff\xff"
#define PKG_END_STRING      "\xfe\xfe"
#define PKG_BEING_STRING_LEN (2)
#define PKG_END_STRING_LEN   (2)
#define PKG_BEGIN_CHAR      ((char)0xff)
#define PKG_END_CHAR        ((char)0xfe)
#define PKG_HEADER_LEN      (5)


Mcu *Mcu::m_mcu = NULL;

const char Mcu::m_queryFstBattery[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, 0x52, 0x0, 0x32, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_querySndBattery[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x36, PKG_END_CHAR, PKG_END_CHAR};

const char Mcu::m_queryFstBatteryStatus[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x31, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_querySndBattery_Status[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x35, PKG_END_CHAR, PKG_END_CHAR};

const char Mcu::m_queryCoreTemperatureData[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x10, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryFPGATemperatureData[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x11, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPowerSupplyTemperatureData[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x12, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryMCUTemperatureData[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x13, PKG_END_CHAR, PKG_END_CHAR};

char Mcu::m_setBrightnessData[8]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, 0x53, 0x01, 0x42, 0x0, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryBrightnessData[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x42, PKG_END_CHAR, PKG_END_CHAR};

const char Mcu::m_respondSTM32PowerOffData[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, 0x53, 0x0, 0x41, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_nofityStarted[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, 0x53, 0x0, 0x43, PKG_END_CHAR, PKG_END_CHAR};

const char Mcu::m_queryPashedArrayProbeModel[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x51, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPashedArrayProbeSeries[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x52, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPashedArrayProbeType[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x53, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPashedArrayProbeFreq[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x54, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPashedArrayProbeElements[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x55, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPashedArrayProbeElementsDist[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x56, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryPashedArrayProbeFerencePoint[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x57, PKG_END_CHAR, PKG_END_CHAR};

const char Mcu::m_queryNormalProbe1Model[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x61, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryNormalProbe1Series[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x62, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryNormalProbe1Freq[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x63, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryNormalProbe1Size[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x64, PKG_END_CHAR, PKG_END_CHAR};

const char Mcu::m_queryNormalProbe2Model[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x71, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryNormalProbe2Series[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x72, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryNormalProbe2Freq[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x73, PKG_END_CHAR, PKG_END_CHAR};
const char Mcu::m_queryNormalProbe2Size[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, Mcu::QueryPkg, 0x0, 0x74, PKG_END_CHAR, PKG_END_CHAR};


Mcu::Mcu()
    :QSerialPort(UART_DEVICE)
{
    connect(this, &Mcu::readyRead, this, &Mcu::on_readyRead_event);
    m_recBuffer.clear();

    if ( ! setBaudRate(QSerialPort::Baud115200) ) {
        qDebug("setBaudRate error!\n");
    }

    if ( ! setDataBits(QSerialPort::Data8) ) {
        qDebug("setDataBits error!\n");
    }

    if ( ! setFlowControl(QSerialPort::NoFlowControl) ) {
        qDebug("setFlowControl error!\n");
    }

    if ( ! setStopBits(QSerialPort::OneStop) ) {
        qDebug("setStopBits error!\n");
    }

    if ( ! setParity(QSerialPort::NoParity) ) {
        qDebug("setParity error!\n");
    }

    if ( ! open(QIODevice::ReadWrite) ) {
        qDebug("Serial Open Error!\n");
    }

}

void Mcu::parse_packet(QByteArray &pkg)
{
    if (pkg.size() != (pkg.at(3)+PKG_HEADER_LEN+PKG_END_STRING_LEN)) {
        return;
    }

    QByteArray data = pkg.mid(PKG_HEADER_LEN, pkg.at(3));
    emit event((EventType)pkg.at(4), data);
}

QByteArray Mcu::find_packet(QByteArray &data)
{
    int begin;
    int end;

    while(1) {
        begin = data.indexOf(PKG_BEGIN_STRING);
        if ( begin<0 ) {
            return NULL;
        }

        end = data.indexOf(PKG_END_STRING);
        if (end<0) {
            return NULL;
        }

        if (begin > end) {
            data = data.mid(begin);
            continue;
        } else if ( end != begin+PKG_HEADER_LEN+data.at(begin+3) ) {
            data = data.mid(begin+PKG_BEING_STRING_LEN);
            continue;
        } else {
            QByteArray pkg = data.mid(begin, PKG_HEADER_LEN + data.at(begin+3) + PKG_END_STRING_LEN);
            data = data.mid(end+PKG_END_STRING_LEN);
            return pkg;
        }
    }
}

void Mcu::on_readyRead_event()
{
    QByteArray data = readAll();

    if (data.isEmpty()) {
        return;
    }

    m_recBuffer.append(data);

    while(1) {
        data = find_packet(m_recBuffer);
        if (data.isEmpty()) {
            break;
        }
        parse_packet(data);
    }
}
