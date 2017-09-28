/**
 * @file device_p.h
 * @brief device private class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-07
 */

#ifndef __DEVICE_P_H__
#define __DEVICE_P_H__

#include "device.h"
#include <source/source.h>
#include <source/scan.h>

namespace DplDevice {

class DevicePrivate : public QObject
{
    Q_OBJECT
public:
    explicit DevicePrivate(Device *parent);
    ~DevicePrivate();

    const QString &serial_number() const;

    const QString &version() const;

    time_t relative_time() const;

    bool set_relative_time(time_t t);

    bool import_cert(const QString &certFile);

    const Cert &cert() const;

    Device::Type type() const;

    bool is_valid() const;

    /**
     * @brief pa_max_power  PA最大输出功率
     * @return              功率(W)
     */
    float pa_max_power() const;

    /**
     * @brief total_beam_qty    获取所有组的Beam总数
     * @return                  数量
     */
    int total_beam_qty() const;

    /**
     * @brief max_txrx_time 获取最大工作时间
     * @return              时间(ns)
     */
    quint32 max_txrx_time() const;

    /**
     * @brief max_acquisition_rate  获取最大的采集率
     * @return                      采集率(Hz)
     */
    int max_acquisition_rate() const;

    int acquisition_rate() const;

    void set_acquisition_rate(int val);

protected:
    /**
     * @brief get_serial_number 获取序列号
     * @return                  序列号
     */
    QString get_serial_number();

    /**
     * @brief get_version   获取设备版本号
     * @return              版本号
     */
    QString get_version();

    /**
     * @brief get_relative_time 获取相对设备的时间差
     * @return                  时间差
     */
    time_t get_relative_time();

protected slots:
    void do_encX_enabled_changed(bool enable);
    void do_encX_mode_changed(DplSource::Encoder::Mode mode);
    void do_encX_polarity_changed(DplSource::Encoder::Polarity polarity);
    void do_encY_enabled_changed(bool enable);
    void do_encY_mode_changed(DplSource::Encoder::Mode mode);
    void do_encY_polarity_changed(DplSource::Encoder::Polarity polarity);

public:
    /* Group */
    QVector<GroupPointer> m_groups;
    GroupPointer m_curGroup;

private:
    Device *q_ptr;
    QString m_serialNo;         // 序列号
    QString m_version;          // 设备版本号
    time_t m_time;              // 相对设备的时间差
    Cert m_cert;
    Device::Type m_type;
    int m_acqRate;              // 采集频率, prf*总声束数
};

inline const QString &DevicePrivate::serial_number() const
{
    return m_serialNo;
}

inline const QString &DevicePrivate::version() const
{
    return m_version;
}

inline time_t DevicePrivate::relative_time() const
{
    return m_time;
}

inline const Cert &DevicePrivate::cert() const
{
    return m_cert;
}

inline Device::Type DevicePrivate::type() const
{
    return m_type;
}

inline float DevicePrivate::pa_max_power() const
{
    return 1.0;
}

inline int DevicePrivate::acquisition_rate() const
{
    return m_acqRate;
}

inline void DevicePrivate::set_acquisition_rate(int val)
{
    m_acqRate = val;
}

}

#endif /* end of include guard */
