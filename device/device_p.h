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

namespace DplDevice {

class DevicePrivate
{
public:
    DevicePrivate();

    mutable QReadWriteLock m_rwlock;

    QString m_serialNo;         // 序列号
    QString m_version;          // 软件版本号

    time_t m_time;
    Cert m_cert;
    Device::Type m_type;

    /* Group */
    QList<GroupPointer> m_groups;
    GroupPointer m_curGroup;
    mutable QReadWriteLock m_groupsRWLock;

private:
    QByteArray get_version();
    time_t get_time();
    QString get_serial_number();
};

}

#endif /* end of include guard */
