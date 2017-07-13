/**
 * @file device.h
 * @brief Device 
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "group.h"
#include "cert.h"

#include <fpga/fpga.h>

#include <QDateTime>
#include <QMutex>

namespace DplDevice {

class DevicePrivate;

class Device : public QObject
{
    Q_DECLARE_PRIVATE(Device)
    Q_OBJECT
public:
    enum Type {
        DEV_16_64_TOFD,
        DEV_32_64_TOFD,
        DEV_32_128_TOFD,
        DEV_32_128_PRO_TOFD
    };

    /**
     * @brief instance  获取Device的单例对象
     * @return          返回Device的单例对象
     */
    static Device *instance();

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

    /**
     * @brief get_cert  获取证书
     * @return          证书对象
     */
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
    const QString &serial_number() const;

    /**
     * @brief is_valid  判断设备是否有效
     * @return          true为有效，false为无效
     */
    bool is_valid() const;

    /* Group */
    /**
     * @brief groups    获取组数量
     * @return          返回组数
     */
    int groups();

    /**
     * @brief create_group  创建组
     * @return              成功返回true，失败返回false
     */
    bool add_group();

    /**
     * @brief remove_group  删除指定的组
     * @param               组号
     * @return              成功返回true，失败返回false
     */
    bool remove_group(int id);

    /**
     * @brief get_group 获取指定组
     * @param index     指定组号
     * @return          成功返回指定组，失败返回空组
     */
    const GroupPointer &get_group(int index) const;

    /**
     * @brief set_current_group 指定当前组
     * @param index             组号
     * @return                  成功返回true，失败返回false
     */
    bool set_current_group(int index);

    /**
     * @brief current_group 获取当前组
     * @return              返回当前组
     */
    const GroupPointer &current_group() const;

    /**
     * @brief beam_qty  获取beam的总数
     * @return          返回beam的总数
     */
    int total_beam_qty() const;

signals:
    void current_group_changed(const DplDevice::GroupPointer &group);

public slots:
    void refresh_beams();

protected:
    explicit Device(QObject *parent = 0);
    ~Device();

private:
    DevicePrivate *d_ptr;
};

}
#endif // __DEVICE_H__
