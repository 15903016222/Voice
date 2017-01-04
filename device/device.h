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

typedef QSharedPointer<Group> GroupPointer;

class DevicePrivate;

class Device : public QObject
{
    Q_OBJECT
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
    GroupPointer &get_group(int index);

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
    GroupPointer &current_group();

    /**
     * @brief beam_qty  获取beam的总数
     * @return          返回beam的总数
     */
    int beam_qty();

signals:
    void current_group_changed();

protected:
    explicit Device(QObject *parent = 0);
    ~Device();

private:
    static Device *s_device;
    static QMutex s_mutex;
    DevicePrivate *d;
};

}
#endif // __DEVICE_H__
