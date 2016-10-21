#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <QObject>
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

protected:
    explicit Device();
    ~Device();

private:
    static Device *s_device;
    static QMutex s_mutex;
    DevicePrivate *d;
};

#endif // __DEVICE_H__
