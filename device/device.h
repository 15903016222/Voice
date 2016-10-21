#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <QObject>

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

    explicit Device();
    ~Device();

    Device::Type type() const;
    const QString &type_string() const;
    const QString &serial_number() const;
    int fpga_version() const;
    int run_count() const;
    uint run_time() const;

private:
    DevicePrivate *d;
};

#endif // __DEVICE_H__
