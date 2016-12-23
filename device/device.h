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
#include "cert.h"

namespace DplDevice {

class DevicePrivate;

class Device
{
public:
    enum Type {
        DEV_16_64_TOFD,
        DEV_32_64_TOFD,
        DEV_32_128_TOFD,
        DEV_32_128_PRO_TOFD
    };

    /**
     * @brief get_device    获取Device类型的对象
     * @return              返回Device类型的对象
     */
    static Device *get_instance();

    /**
     * @brief version  获取设备版本号
     * @return         返回设备版本号
     */
    const QString &version() const;

    /**
     * @brief date_time 获取时间
     * @return          返回time_t类型时间
     */
    uint date_time() const;
    bool set_date_time(uint t);
    bool set_date_time(const QDateTime &t) { return set_date_time(t.toTime_t()); }

    /**
     * @brief import_cert   导入证书
     * @param certFile      证书文件
     * @return              成功返回true，否则返回false
     */
    bool import_cert(const QString &certFile);
    const Cert &get_cert() const;

    /**
     * @brief type      获取设备类型
     * @return          返回设备类型
     */
    Device::Type type() const;
    const QString &type_string();

    /**
     * @brief serial_number 获取设备序列号
     * @return              返回设备序列号
     */
    virtual const QString &serial_number() const = 0;

    /**
     * @brief is_valid  判断设备是否有效
     * @return          true为有效，false为无效
     */
    virtual bool is_valid() const = 0;

protected:
    explicit Device();
    ~Device();

private:
    static Device *s_device;
    static QMutex s_mutex;
    DevicePrivate *d;
};

}
#endif // __DEVICE_H__
