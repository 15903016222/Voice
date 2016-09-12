#include "mcu_omap.h"

#include <QDebug>

#define TTY_DEV0    "/dev/ttyS0"
#define TTY_DEV1    "/dev/ttyS1"

McuOmap::McuOmap()
    :McuPrivate(), m_ttyS0(TTY_DEV0), m_ttyS1(TTY_DEV1),
      m_brightness(70)
{
    init_tty(m_ttyS0);
    init_tty(m_ttyS1);
    connect(&m_ttyS0, SIGNAL(readyRead()), this, SLOT(on_ttyS0_readyRead_event()));
    connect(&m_ttyS1, SIGNAL(readyRead()), this, SLOT(on_ttyS1_readyRead_event()));
    if ( ! m_ttyS0.open(QIODevice::ReadWrite)) {
        qDebug("ttyS0: Open Error!\n");
    }
    if ( ! m_ttyS1.open(QIODevice::ReadWrite)) {
        qDebug("ttyS1: Open Error!\n");
    }
}

void McuOmap::init_tty(QSerialPort &tty)
{
    qDebug()<<"Init "<<tty.portName();
    if ( ! tty.setBaudRate(QSerialPort::Baud115200) ) {
        qDebug("setBaudRate error!\n");
    }

    if ( ! tty.setDataBits(QSerialPort::Data8) ) {
        qDebug("setDataBits error!\n");
    }

    if ( ! tty.setFlowControl(QSerialPort::NoFlowControl) ) {
        qDebug("setFlowControl error!\n");
    }

    if ( ! tty.setStopBits(QSerialPort::OneStop) ) {
        qDebug("setStopBits error!\n");
    }

    if ( ! tty.setParity(QSerialPort::NoParity) ) {
        qDebug("setParity error!\n");
    }
}


void McuOmap::query(Mcu::Cmd cmd)
{
    if ( Mcu::BRIGHTNESS == cmd ) {
        QByteArray data(&m_brightness, 1);
        emit event(Mcu::BRIGHTNESS, data);
    }
}

void McuOmap::set(Mcu::Cmd cmd, char value)
{
    if ( Mcu::BRIGHTNESS == cmd ) {
        m_ttyS1.write(&value, 1);
        m_brightness = value;
    } else if ( Mcu::POWEROFF == cmd ) {
        qDebug("poweroff");
        value = 0xaa;
        m_ttyS1.write(&value, 1);
        m_ttyS1.write(&value, 1);
        m_ttyS1.write(&value, 1);
    } else if ( Mcu::PA_PROBE_MODEL ) {
        value = 0xcc;
        m_ttyS1.write(&value, 1);
    }
}

#define PROBE_BEGIN_FLAG    "\x53\x53\x53"
#define PROBE_END_FLAG      "\x54\x54\x54"
#define BATTERY_BEGIN_FLAG  "\x55\x55\x55"
#define BATTERY_END_FLAG    "\x56\x56\x56"
void McuOmap::on_ttyS0_readyRead_event()
{
    /**
      *         ---------------------------------------------------------------------------------------------------------
      * 电池信息 |BATTERY_BEGIN_FLAG|电量1|状态1|剩余时间1|电量2|状态3|剩余时间3|温度|温度|温度|温度|温度|温度|温度|开关|BATTERY_END_FLAG|
      *         ---------------------------------------------------------------------------------------------------------
      *         ----------------------------------------
      * 探头信息 |PROBE_BEGIN_FLAG|探头信息|PROBE_END_FLAG|
      *         ----------------------------------------
      */
    m_buffer.append(m_ttyS0.readAll());

    if (m_buffer.at(0) != 0x53 && m_buffer.at(0) != 0x55) {
        m_buffer.clear();
    }

    if (m_buffer.size() < 31) {
        return;
    }

    qDebug()<<__LINE__<<m_buffer.size()<<":"<<m_buffer.toHex();

    if (m_buffer.at(1) == 0x55 && m_buffer.at(2) == 0x55) {
        if (m_buffer.at(27) == 0xaa) {
            QByteArray s;
            emit event(Mcu::POWEROFF, s);
        }
        /* first battery */
        QByteArray s = m_buffer.mid(3, 1);
        emit event(Mcu::BATTERY1_QUANTITY, s);

        /* second battery */
        s = m_buffer.mid(9, 2);
        emit event(Mcu::BATTERY2_QUANTITY, s);
        qDebug()<<"power2"<<s.toHex().toInt(0, 16);

    } else if (m_buffer.at(1) == 0x53 && m_buffer.at(2) == 0x53) {

    }

    m_buffer.clear();
}

void McuOmap::on_ttyS1_readyRead_event()
{
    QByteArray data = m_ttyS1.readAll();

    while ( ! data.isEmpty() ) {
        QByteArray key = data.left(1);
        data = data.mid(1);
        emit event(Mcu::KEY, key);
    }
}
