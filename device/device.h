/**
 * @file device.h
 * @brief Device 
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <QDateTime>
#include <QMutex>

class DevicePrivate;

class Device
{
public:
    enum Type {
        DEV_16_64_TOFD,
        DEV_32_64_TOFD,
        DEV_32_128_TOFD,
        DEV_32_128_PRO_TOFD,
        DEV_TYPE_MAX
    };

    static Device *get_device();

    Device::Type type() const;
    const QString &type_string() const;
    const QString &serial_number() const;
    int fpga_version() const;
    int run_count() const;
    uint run_time() const;  /* Unit: seconds */

    /* 设备时间及日期 */
    uint date_time() const;
    bool set_date_time(uint t);
    bool set_date_time(const QDateTime &t) { return set_date_time(t.toTime_t()); }

    bool import_cert(const QString &certFile);
    const QString &cert_mode_string() const;
    const QString cert_expire() const;

    bool is_valid() const;

protected:
    explicit Device();
    ~Device();

private:
    static Device *s_device;
    static QMutex s_mutex;
    DevicePrivate *d;
};

#endif // __DEVICE_H__
