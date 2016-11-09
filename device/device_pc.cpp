/**
 * @file device_pc.cpp
 * @brief device for personal computer
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-25
 */


#include "device.h"
#include <time.h>

class DevicePrivate
{
public:
    DevicePrivate();
    QString m_serialNo;
    QString m_version;
    QString m_typeString;
    Device::Type m_type;
};
DevicePrivate::DevicePrivate()
{
    m_serialNo = "";
    m_version = "";
#ifdef PC_UNIX
    m_type = Device::DEV_PC_UNIX;
    m_typeString = "Unix PC";
#elif PC_WIN
    m_type = Device::DEV_PC_WIN;
    m_typeString = "Window PC";
#endif
}

/********************* Device ***************************/
Device *Device::s_device = NULL;
QMutex Device::s_mutex;

Device *Device::get_device()
{
    QMutexLocker l(&s_mutex);
    if (s_device == NULL) {
        s_device = new Device();
    }
    return s_device;
}

const QString &Device::version() const
{
    return d->m_version;
}

Device::Type Device::type() const
{
    return d->m_type;
}

const QString &Device::type_string() const
{
    return d->m_typeString;
}

const QString &Device::serial_number() const
{
    return d->m_serialNo;
}

uint Device::date_time() const
{
    return ::time(NULL);
}

bool Device::set_date_time(uint t)
{
    Q_UNUSED(t);
    return true;
}

uint Device::run_time() const
{
    return 0;
}

int Device::run_count() const
{
    return 0;
}

bool Device::import_cert(const QString &certFile)
{
    Q_UNUSED(certFile);
    return true;
}

const QString Device::cert_info() const
{
    return "";
}

bool Device::is_valid() const
{
    return true;
}

Device::Device()
    : d(new DevicePrivate())
{

}
Device::~Device()
{
    delete d;
}
