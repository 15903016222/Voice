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

QMap<int, Mcu::BatteryStatus> McuOmap::s_statusMap;
QMap<int, Mcu::KeyType> McuOmap::s_keyMap;


McuOmap::McuOmap()
    :Mcu(), m_ttyS0(TTY_DEV0), m_ttyS1(TTY_DEV1), m_brightness(70)
{
    if (s_statusMap.isEmpty()) {
        s_statusMap.insert(0x00, Mcu::NO_BATTERY);
        s_statusMap.insert(0x80, Mcu::CHARGE);
        s_statusMap.insert(0xc0, Mcu::DISCHARGE);
        s_statusMap.insert(0xe0, Mcu::BATTERY_FULL);
    }

    if (s_keyMap.isEmpty()) {
//        s_keyMap.insert(0,  KEY_UP);
        s_keyMap.insert(209,  KEY_LEFT);
        s_keyMap.insert(215,  KEY_RIGHT);
//        s_keyMap.insert(10, KEY_DOWN);
        s_keyMap.insert(210,  KEY_MENU);
        s_keyMap.insert(227, KEY_MENU);
        s_keyMap.insert(214,  KEY_SURE);
        s_keyMap.insert(241, KEY_SURE);
        s_keyMap.insert(217, KEY_BACK);
        s_keyMap.insert(239, KEY_BACK);
        s_keyMap.insert(211,  KEY_80_PERCENT);
        s_keyMap.insert(218, KEY_DISPLAY);
        s_keyMap.insert(212,  KEY_START);
//        s_keyMap.insert(KEY_STOP);
        s_keyMap.insert(219, KEY_SAVE);
        s_keyMap.insert(213,  KEY_OPEN);
        s_keyMap.insert(220, KEY_GATE);
        s_keyMap.insert(221, KEY_CALIBRATION);
        s_keyMap.insert(222, KEY_DB);
        s_keyMap.insert(223, KEY_CURSOR);
        s_keyMap.insert(224, KEY_FREEZE);
        s_keyMap.insert(225, KEY_ANGLE);
        s_keyMap.insert(226, KEY_ERASURE);
        s_keyMap.insert(233, KEY_HELP);
//        s_keyMap.insert(KEY_F1);
        s_keyMap.insert(228, KEY_F2);
        s_keyMap.insert(229, KEY_F3);
        s_keyMap.insert(230, KEY_F4);
        s_keyMap.insert(231, KEY_F5);
        s_keyMap.insert(232, KEY_F6);
        s_keyMap.insert(234, KEY_F7);
        s_keyMap.insert(235, KEY_F8);
        s_keyMap.insert(236, KEY_F9);
        s_keyMap.insert(237, KEY_F10);
        s_keyMap.insert(238, KEY_F11);
        s_keyMap.insert(242, KEY_F12);
    }

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
        if ((unsigned char)(m_buffer.at(27)) == 0xaa) {
            emit poweroff_event();
        }
        /* first battery */
        emit battery_quantity_event(0, m_buffer.mid(4, 1).toHex().toInt(0, 16));

        emit battery_status_event(0, s_statusMap[m_buffer.at(6)]);

        /* second battery */
        emit battery_quantity_event(1, m_buffer.mid(10, 1).toHex().toInt(0, 16));

        emit battery_status_event(1, s_statusMap[m_buffer.at(12)]);

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
        emit probe_event(m_buffer.mid(3).constData());
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
            emit key_event(s_keyMap[key]);
        }
    }
}
