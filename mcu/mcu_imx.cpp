#include "mcu_imx.h"

#define UART_DEVICE         "/dev/ttymxc2"
#define PKG_BEGIN_STRING    "\xff\xff"
#define PKG_END_STRING      "\xfe\xfe"
#define PKG_BEING_STRING_LEN (2)
#define PKG_END_STRING_LEN   (2)
#define PKG_BEGIN_CHAR      ((char)0xff)
#define PKG_END_CHAR        ((char)0xfe)
#define PKG_HEADER_LEN      (5)

char McuImx::m_queryPkg[7] = {PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, McuImx::QueryPkg, 0x0, 0x10, PKG_END_CHAR, PKG_END_CHAR};
char McuImx::m_setPkg[8] = {PKG_BEGIN_CHAR, PKG_BEGIN_CHAR, McuImx::SettingPkg, 0x01, 0, 0x0, PKG_END_CHAR, PKG_END_CHAR};

McuImx::McuImx()
    : Mcu(), m_tty(UART_DEVICE)
{
    connect(&m_tty, SIGNAL(readyRead()), this, SLOT(on_readyRead_event()));
    m_recBuffer.clear();

    if ( ! m_tty.setBaudRate(QSerialPort::Baud115200) ) {
        qDebug("setBaudRate error!\n");
    }

    if ( ! m_tty.setDataBits(QSerialPort::Data8) ) {
        qDebug("setDataBits error!\n");
    }

    if ( ! m_tty.setFlowControl(QSerialPort::NoFlowControl) ) {
        qDebug("setFlowControl error!\n");
    }

    if ( ! m_tty.setStopBits(QSerialPort::OneStop) ) {
        qDebug("setStopBits error!\n");
    }

    if ( ! m_tty.setParity(QSerialPort::NoParity) ) {
        qDebug("setParity error!\n");
    }

    if ( ! m_tty.open(QIODevice::ReadWrite) ) {
        qDebug("Serial Open Error!\n");
    }

}

void McuImx::parse_packet(QByteArray &pkg)
{
    if (pkg.size() != (pkg.at(3)+PKG_HEADER_LEN+PKG_END_STRING_LEN)) {
        return;
    }

    QByteArray data = pkg.mid(PKG_HEADER_LEN, pkg.at(3));
    switch (pkg.at(4)) {
    case Mcu::KEY:
    case Mcu::ROTARY:
        emit key_event(data.toHex().toInt(0, 16));
        break;
    case Mcu::BATTERY1_QUANTITY:
        emit battery_quantity_event(0, data.toHex().toInt(0, 16));
        break;
    case Mcu::BATTERY1_STATUS:
        emit battery_status_event(0, (Mcu::BatteryStatus)data.toHex().toInt(0, 16));
        break;
    case Mcu::BATTERY2_QUANTITY:
        emit battery_quantity_event(1, data.toHex().toInt(0, 16));
        break;
    case Mcu::BATTERY2_STATUS:
        emit battery_status_event(1, (Mcu::BatteryStatus)data.toHex().toInt(0, 16));
        break;
    case Mcu::BRIGHTNESS:
        emit brightness_event(data.toHex().toInt(0, 16));
        break;
    case Mcu::CORE_TEMPERATURE:
    case Mcu::FPGA_TEMPERATURE:
    case Mcu::MCU_TEMPERATUREE:
    case Mcu::POWER_TEMPERATURE:
        emit temperature_event((Mcu::TemperatureType)pkg.at(4), data.toHex().toInt(0, 16));
        break;
    case Mcu::PA_PROBE_MODEL:
    case Mcu::PA_PROBE_SERIES:
    case Mcu::PA_PROBE_TYPE:
    case Mcu::PA_PROBE_FREQ:
    case Mcu::PA_PROBE_ELEMENTS_QTY:
    case Mcu::PA_PROBE_ELEMENTS_DISTANCE:
    case Mcu::PA_PROBE_FERENCE_POINT:
        emit pa_probe_event((Mcu::PaProbeAttrType)pkg.at(4), data);
        break;
    case Mcu::POWEROFF:
        emit poweroff_event();
    default:
        break;
    }
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
    QByteArray data = m_tty.readAll();

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
