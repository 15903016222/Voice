#include "mcu_omap.h"

#define TTY_DEV0    "/dev/ttyS0"
#define TTY_DEV1    "/dev/ttyS1"

McuOmap::McuOmap()
    :McuPrivate(TTY_DEV0), m_ttyDev1(TTY_DEV1)
{
    /* ttyS0 setting */
    connect(this, SIGNAL(readyRead()), this, SLOT(on_readyRead_event()));
    if ( ! setBaudRate(QSerialPort::Baud115200) ) {
        qDebug("ttyS0: setBaudRate error!\n");
    }

    if ( ! setDataBits(QSerialPort::Data8) ) {
        qDebug("ttyS0: setDataBits error!\n");
    }

    if ( ! setFlowControl(QSerialPort::NoFlowControl) ) {
        qDebug("ttyS0: setFlowControl error!\n");
    }

    if ( ! setStopBits(QSerialPort::OneStop) ) {
        qDebug("ttyS0: setStopBits error!\n");
    }

    if ( ! setParity(QSerialPort::NoParity) ) {
        qDebug("ttyS0: setParity error!\n");
    }

    if ( ! open(QIODevice::ReadWrite)) {
        qDebug("ttyS0: Open Error!\n");
    }

    /* ttyS1 setting */
    connect(&m_ttyDev1, SIGNAL(readyRead()), this, SLOT(on_ttyDev1_readyRead_event()));
    if ( ! m_ttyDev1.setBaudRate(QSerialPort::Baud115200) ) {
        qDebug("ttyS1: setBaudRate error!\n");
    }

    if ( ! m_ttyDev1.setDataBits(QSerialPort::Data8) ) {
        qDebug("ttyS1: setDataBits error!\n");
    }

    if ( ! m_ttyDev1.setFlowControl(QSerialPort::NoFlowControl) ) {
        qDebug("ttyS1: setFlowControl error!\n");
    }

    if ( ! m_ttyDev1.setStopBits(QSerialPort::OneStop) ) {
        qDebug("ttyS1: setStopBits error!\n");
    }

    if ( ! m_ttyDev1.setParity(QSerialPort::NoParity) ) {
        qDebug("ttyS1: setParity error!\n");
    }

    if ( ! m_ttyDev1.open(QIODevice::ReadWrite)) {
        qDebug("ttyS1: Open Error\n");
    }
}


void McuOmap::on_ttyDev1_readyRead_event()
{
    QByteArray data = m_ttyDev1.readAll();

    while ( ! data.isEmpty() ) {
        QByteArray key = data.left(1);
        data = data.mid(1);
        emit event(Mcu::KEY, key);
    }
}
