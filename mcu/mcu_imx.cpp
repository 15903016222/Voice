#include "mcu_imx.h"

#include <QDebug>

#define UART_DEVICE         "/dev/ttymxc2"
#define PKG_BEGIN_STRING    "\xff\xff"
#define PKG_END_STRING      "\xfe\xfe"
#define PKG_BEING_STRING_LEN (2)
#define PKG_END_STRING_LEN   (2)
#define PKG_BEGIN_CHAR      ((char)0xff)
#define PKG_END_CHAR        ((char)0xfe)
#define PKG_HEADER_LEN      (5)


McuImx *McuImx::m_mcu = NULL;

char McuImx::m_queryPkg[7] = {PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, McuImx::QueryPkg, 0x0, 0x10, PKG_END_CHAR, PKG_END_CHAR};

char McuImx::m_setBrightnessData[8]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, McuImx::SettingPkg, 0x01, Mcu::BRIGHTNESS, 0x0, PKG_END_CHAR, PKG_END_CHAR};

const char McuImx::m_setPoweroff[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, McuImx::SettingPkg, 0x0, Mcu::POWEROFF, PKG_END_CHAR, PKG_END_CHAR};
const char McuImx::m_nofityStarted[7]={PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, McuImx::SettingPkg, 0x0, Mcu::NOTIFY_STARTED, PKG_END_CHAR, PKG_END_CHAR};

McuImx::McuImx()
    :Mcu(UART_DEVICE)
{
    connect(this, &McuImx::readyRead, this, &McuImx::on_readyRead_event);
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

void McuImx::parse_packet(QByteArray &pkg)
{
    if (pkg.size() != (pkg.at(3)+PKG_HEADER_LEN+PKG_END_STRING_LEN)) {
        return;
    }

    QByteArray data = pkg.mid(PKG_HEADER_LEN, pkg.at(3));
    emit event((Cmd)pkg.at(4), data);
}

QByteArray McuImx::find_packet(QByteArray &data)
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

void McuImx::on_readyRead_event()
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
        qDebug()<<"Packet:"<<data.toHex();
        parse_packet(data);
    }
}
