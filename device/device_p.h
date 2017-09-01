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
    QByteArray get_version();

    /**
     * @brief get_relative_time 获取相对设备的时间差
     * @return                  时间差
     */
    time_t get_relative_time();

protected slots:
    void do_encX_enabled_changed(bool enable);
    void do_encX_mode_changed(DplSource::Encoder::Mode mode);
    void do_encY_enabled_changed(bool enable);
    void do_encY_mode_changed(DplSource::Encoder::Mode mode);

public:
    /* Group */
    QVector<GroupPointer> m_groups;
    GroupPointer m_curGroup;
    mutable QReadWriteLock m_groupsRWLock;

private:
    Device *q_ptr;
    QString m_serialNo;         // 序列号
    QString m_version;          // 设备版本号
    time_t m_time;              // 相对设备的时间差
    Cert m_cert;
    Device::Type m_type;
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

}

#endif /* end of include guard */
