#ifndef __MCU_IMX_H__
#define __MCU_IMX_H__

#include "mcu_p.h"

#include <QSerialPort>
#include <QMutex>
#include <QDebug>
/**
 * package format
 * -------------------------------------------------------
 * | 0xff | 0xff | TYPE | LEN | CMD | DATA | 0xfe | 0xfe |
 * -------------------------------------------------------
 */

class McuImx : public McuPrivate
{
    Q_OBJECT
public:
    enum PkgType {
        RespondPkg = 0x50,  /* 应答包 */
        EventPkg,           /* 事件包 */
        QueryPkg,           /* 查询包 */
        SettingPkg          /* 设置包 */
    };

    McuImx();

    void query(Mcu::Cmd cmd) { m_queryPkg[4] = cmd; write(m_queryPkg, sizeof(m_queryPkg)); }
    void set(Mcu::Cmd cmd, char value) { m_setPkg[4] = cmd; m_setPkg[5] = value; write(m_setPkg, sizeof(m_setPkg));}

private:
    QSerialPort m_tty;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static char m_queryPkg[7];
    static char m_setPkg[8];

    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return m_tty.write(data, len); }

    QByteArray find_packet(QByteArray &data);
    void parse_packet(QByteArray &pkg);

private slots:
    void on_readyRead_event();
};

#endif // __MCU_IMX_H__
