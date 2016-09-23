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

void McuImx::query_probe()
{
    m_probeFlag = 1;
    query(PA_PROBE_MODEL);
    query(PA_PROBE_SERIAL);
    query(PA_PROBE_TYPE);
    query(PA_PROBE_FREQ);
    query(PA_PROBE_ELEMENTS_QTY);
    query(PA_PROBE_ELEMENTS_DISTANCE);
    query(PA_PROBE_REFERENCE_POINT);
}

void McuImx::parse_packet(QByteArray &pkg)
{
    if (pkg.size() != (pkg.at(3)+PKG_HEADER_LEN+PKG_END_STRING_LEN)) {
        return;
    }

    QByteArray data = pkg.mid(PKG_HEADER_LEN, pkg.at(3));
    switch (pkg.at(4)) {
    case KEY:
        emit key_event(data.toHex().toInt(0, 16));
        break;
    case ROTARY:
        emit rotary_event((Mcu::RotaryType)(data.toHex().toInt(0, 16)));
        break;
    case BATTERY1_QUANTITY:
        emit battery_quantity_event(0, data.toHex().toInt(0, 16));
        break;
    case BATTERY1_STATUS:
        emit battery_status_event(0, (Mcu::BatteryStatus)data.toHex().toInt(0, 16));
        break;
    case BATTERY2_QUANTITY:
        emit battery_quantity_event(1, data.toHex().toInt(0, 16));
        break;
    case BATTERY2_STATUS:
        emit battery_status_event(1, (Mcu::BatteryStatus)data.toHex().toInt(0, 16));
        break;
    case BRIGHTNESS:
        emit brightness_event(data.toHex().toInt(0, 16));
        break;
    case CORE_TEMPERATURE:
    case FPGA_TEMPERATURE:
    case MCU_TEMPERATUREE:
    case POWER_TEMPERATURE:
        emit temperature_event((Mcu::TemperatureType)pkg.at(4), data.toHex().toInt(0, 16));
        break;
    case PA_PROBE_MODEL:
        m_probeFlag <<= 1;
        m_probe.set_model(data);
        break;
    case PA_PROBE_SERIAL:
        m_probeFlag <<= 1;
        m_probe.set_serial(data);
        break;
    case PA_PROBE_TYPE:
        m_probeFlag <<= 1;
        m_probe.set_type((Probe::ProbeType)data.toHex().toInt(0, 16));
        break;
    case PA_PROBE_FREQ:
        m_probeFlag <<= 1;
        m_probe.set_freq(data.toHex().toInt(0, 16));
        break;
    case PA_PROBE_ELEMENTS_QTY:
        m_probeFlag <<= 1;
        m_probe.set_elements_quantity(data.toHex().toInt(0, 16));
        break;
    case PA_PROBE_ELEMENTS_DISTANCE:
        m_probeFlag <<= 1;
        m_probe.set_pitch(data.toHex().toInt(0, 16));
        break;
    case PA_PROBE_REFERENCE_POINT:
        m_probeFlag <<= 1;
        m_probe.set_reference_point(data.toHex().toInt(0, 16));
        break;
    case POWEROFF:
        emit poweroff_event();
    default:
        break;
    }

    if (m_probeFlag == 0x80) {
        emit probe_event(m_probe);
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
