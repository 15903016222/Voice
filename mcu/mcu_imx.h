#ifndef __MCU_IMX_H__
#define __MCU_IMX_H__

#include "mcu.h"

/**
 * package format
 * -------------------------------------------------------
 * | 0xff | 0xff | TYPE | LEN | CMD | DATA | 0xfe | 0xfe |
 * -------------------------------------------------------
 */

class McuImx : public Mcu
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

    void query_core_temp()      { query(CORE_TEMPERATURE); }
    void query_fpga_temp()      { query(FPGA_TEMPERATURE); }
    void query_power_temp()     { query(POWER_TEMPERATURE); }
    void query_mcu_temp()       { query(MCU_TEMPERATUREE); }
    void query_first_battery()  { query(BATTERY1_QUANTITY); }
    void query_second_battery() { query(BATTERY2_QUANTITY); }
    void query_first_battery_status()   { query(BATTERY1_STATUS); }
    void query_second_battery_status()  { query(BATTERY2_STATUS); }
    void query_brightness()             { query(BRIGHTNESS); }

    /* pa probe query */
    void query_pa_probe_model()     { query(PA_PROBE_MODEL); }
    void query_pa_probe_series()    { query(PA_PROBE_SERIES); }
    void query_pa_probe_type()      { query(PA_PROBE_TYPE); }
    void query_pa_probe_freq()      { query(PA_PROBE_FREQ); }
    void query_pa_probe_elements()  { query(PA_PROBE_ELEMENTS_QTY); }
    void query_pa_probe_elements_distance() { query(PA_PROBE_ELEMENTS_DISTANCE); }
    void query_pa_probe_ference_point()     { query(PA_PROBE_FERENCE_POINT); }


    void notify_started()   { write(m_nofityStarted, sizeof(m_nofityStarted)); }
    void set_poweroff()     { write(m_setPoweroff, sizeof(m_setPoweroff)); }
    void set_brightness(uchar light) { m_setBrightnessData[5]=light; write(m_setBrightnessData, sizeof(m_setBrightnessData)); }

protected:
    McuImx();
    ~McuImx() { close(); }

private:
    static McuImx *m_mcu;
    QMutex m_wrMutex;
    QByteArray m_recBuffer;
    static char m_queryPkg[7];
    static char m_setBrightnessData[8];
    static const char m_setPoweroff[7];
    static const char m_nofityStarted[7];

    void query(Cmd cmd) { m_queryPkg[4] = cmd; write(m_queryPkg, sizeof(m_queryPkg)); }
    qint64 write(const char *data, qint64 len) { QMutexLocker locker(&m_wrMutex); return QIODevice::write(data, len); }
    void on_readyRead_event();

    QByteArray find_packet(QByteArray &data);
    void parse_packet(QByteArray &pkg);
};


inline McuImx* McuImx::get_instance()
{
    if (m_mcu == NULL) {
        m_mcu = new McuImx();
    }
    return m_mcu;
}

inline void McuImx::destroyed()
{
    if (m_mcu) {
        delete m_mcu;
        m_mcu = NULL;
    }
}

#endif // __MCU_IMX_H__
