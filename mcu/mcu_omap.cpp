#include "mcu_omap.h"

#include <QDebug>

#define TTY_DEV0    "/dev/ttyS0"
#define TTY_DEV1    "/dev/ttyS1"

/* Probe */
struct ProbeData
{
    char            res0[4];        /* reserve */
    char            res1[2];        /* reserve */
    unsigned char	paType;         /* PA probe type, 1:Custom; 3:angle beam; 5:Contact; 6:Immersion */
    char            res2;           /* reserve */
    unsigned char	utType;         /* UT probe type, 1:n/a; 0:converntional */
    char            res3;           /* reserve */
    char            model[20];		/* Model */
    char            serial[20];		/* Serial */
    unsigned char	elemQty;		/* Elements Qty */
    unsigned char	freq2;			/* UT 时候 频率是 (freq2 << 8) + elem_qty */
    unsigned int	pitch;			/* Elements distance, unit is 0.001mm, range is 0.01~65.00mm, Elemet_size when UT*/
    unsigned int	res4;           /* reserve */
    unsigned short  res5;           /* reserve */
    unsigned short	freq;           /* Frequency */
    unsigned int	res6[75];       /* reserve */
    unsigned short  res7;           /* reserve */
    unsigned short  res8;           /* reserve */
    unsigned short  res9;           /* reserve */
    unsigned short	point;          /* Reference Point */
    unsigned int	res10[36];      /* reserve */
};


McuOmap::McuOmap()
    :Mcu(), m_ttyS0(TTY_DEV0), m_ttyS1(TTY_DEV1), m_brightness(70)
{
    m_statusMap.insert(0x00, Mcu::NO_BATTERY);
    m_statusMap.insert(0x80, Mcu::CHARGE);
    m_statusMap.insert(0xc0, Mcu::DISCHARGE);
    m_statusMap.insert(0xe0, Mcu::BATTERY_FULL);

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

#define PROBE_BEGIN_FLAG    "\x53\x53\x53"
#define PROBE_END_FLAG      "\x54\x54\x54"
#define BATTERY_BEGIN_FLAG  "\x55\x55\x55"
#define BATTERY_END_FLAG    "\x56\x56\x56"
void McuOmap::on_ttyS0_readyRead_event()
{
    /**
      *         -----------------------------------------------------------------------------------------------------------------------------------------
      * 电池信息 |BATTERY_BEGIN_FLAG|电量1|状态1|剩余时间1|电量2|状态3|剩余时间3|FPGA供电芯片温度|PCB板温度|CPU温度|接收板温度|FPGA温度|接收板温度|开关|BATTERY_END_FLAG|
      *         -----------------------------------------------------------------------------------------------------------------------------------------
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

    if (m_buffer.at(1) == 0x55 && m_buffer.at(2) == 0x55) {
        if (m_buffer.at(27) == 0xaa) {
            emit poweroff_event();
        }
        /* first battery */
        emit battery_quantity_event(0, m_buffer.mid(4, 1).toHex().toInt(0, 16));

        emit battery_status_event(0, m_statusMap[m_buffer.at(6)]);

        /* second battery */
        emit battery_quantity_event(1, m_buffer.mid(10, 1).toHex().toInt(0, 16));

        emit battery_status_event(1, m_statusMap[m_buffer.at(12)]);

        /* temperature */
        emit temperature_event(Mcu::TEMPERATURE_POWER,m_buffer.mid(15, 2).toHex().toInt(0, 16)>>7);
//        emit temperature_event(Mcu::TEMPERATURE_PCB,m_buffer.mid(17, 2).toHex().toInt(0, 16)>>7);
        emit temperature_event(Mcu::TEMPERATURE_CPU,m_buffer.mid(19, 2).toHex().toInt(0, 16)>>7);
//        emit temperature_event(,m_buffer.mid(21, 2).toHex().toInt(0, 16)>>7);
        emit temperature_event(Mcu::TEMPERATURE_FPGA,m_buffer.mid(23, 2).toHex().toInt(0, 16)>>7);
//        emit temperature_event(Mcu::FPGA_TEMPERATURE,m_buffer.mid(25, 2).toHex().toInt(0, 16)>>7);


    } else if (m_buffer.at(1) == 0x53 && m_buffer.at(2) == 0x53) {
        if (m_buffer.size() < 549) {
            return;
        }
        const ProbeData *probeData = (ProbeData *)m_buffer.mid(3).constData();
        Probe probe;
        probe.set_type((Probe::ProbeType)probeData->paType);
//        qDebug()<<"ut type"<<probe->utType;
        probe.set_model(probeData->model);
        probe.set_serial(probeData->serial);
        probe.set_elements_quantity(probeData->elemQty);
//        qDebug()<<"freq2"<<probe->freq2;
        probe.set_pitch(probeData->pitch);
        probe.set_freq(probeData->freq);
        probe.set_reference_point(probeData->point);
        emit probe_event(probe);
    }

    m_buffer.clear();
}

void McuOmap::on_ttyS1_readyRead_event()
{
    QByteArray data = m_ttyS1.readAll();
    int key;
    while ( ! data.isEmpty() ) {
        key = data.at(0);
        data = data.mid(1);
        if (key == 216) {
            emit rotary_event(Mcu::ROTARY_DOWN);
        } else if (key == 208) {
            emit rotary_event(Mcu::ROTARY_UP);
        } else {
            emit key_event(key);
        }
    }
}
