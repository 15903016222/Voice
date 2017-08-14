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

#include <display/display.h>
#include <fpga/fpga.h>

#include <QDateTime>

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
        DEV_32_128_PR_TOFD
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

    /**
     * @brief set_date_time 设置设备时间
     * @param t             时间
     * @return              成功返回true，否则为false
     */
    bool set_date_time(uint t);

    /**
     * @brief set_date_time 设置设备时间
     * @param t             时间
     * @return              成功返回true，否则为false
     */
    bool set_date_time(const QDateTime &t);

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

    /**
     * @brief type_string   获取设备类型字符串
     * @return              返回设备类型字符串
     */
    const QString &type_string() const;

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
     * @brief first_beam_index  获取指定组中的第一条Beam在所有Beam中的序号
     * @param grp               组
     * @return                  序号
     */
    int first_beam_index(const Group *grp) const;

    /**
     * @brief beam_qty  获取beam的总数
     * @return          返回beam的总数
     */
    int total_beam_qty() const;

    /**
     * @brief display   获取显示配置
     * @return          显示配置
     */
    const DplDisplay::DisplayPointer &display() const;

    /**
     * @brief start 启动设备
     */
    void start();

signals:
    void current_group_changed(const DplDevice::GroupPointer &group);

public slots:
    /**
     * @brief deploy_beams  下发所有Beams的配置信息
     */
    void deploy_beams();

protected:
    explicit Device(QObject *parent = 0);
    ~Device();

private:
    DevicePrivate *d_ptr;
    DplDisplay::DisplayPointer m_display;
};

inline bool Device::set_date_time(const QDateTime &t)
{
    return set_date_time(t.toTime_t());
}

inline const DplDisplay::DisplayPointer &Device::display() const
{
    return m_display;
}

}
#endif // __DEVICE_H__
