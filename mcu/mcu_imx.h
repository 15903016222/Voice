#ifndef __MCU_IMX_H__
#define __MCU_IMX_H__

#include "mcu_p.h"

#include <QMutex>

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

    static McuImx* get_instance();
    static void destroyed();

    void query(Mcu::Cmd cmd) { m_queryPkg[4] = cmd; write(m_queryPkg, sizeof(m_queryPkg)); }
    void set(Mcu::Cmd cmd, char value) { m_queryPkg[4] = cmd; m_queryPkg[5] = value; }
//    void notify_started()   { write(m_nofityStarted, sizeof(m_nofityStarted)); }
//    void set_poweroff()     { write(m_setPoweroff, sizeof(m_setPoweroff)); }
//    void set_brightness(uchar light) { m_setBrightnessData[5]=light; write(m_setBrightnessData, sizeof(m_setBrightnessData)); }

protected:
    McuImx();
    ~McuImx() { close(); }

private:
    static McuImx *m_mcuImx;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static char m_queryPkg[7];
    static char m_setPkg[8];
    static char m_setBrightnessData[8];
    static const char m_setPoweroff[7];
    static const char m_nofityStarted[7];

    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return QIODevice::write(data, len); }

    QByteArray find_packet(QByteArray &data);
    void parse_packet(QByteArray &pkg);

private slots:
    void on_readyRead_event();
};


inline McuImx* McuImx::get_instance()
{
    if (m_mcuImx == NULL) {
        m_mcuImx = new McuImx();
    }
    return m_mcuImx;
}

inline void McuImx::destroyed()
{
    if (m_mcuImx) {
        delete m_mcuImx;
        m_mcuImx = NULL;
    }
}

#endif // __MCU_IMX_H__
