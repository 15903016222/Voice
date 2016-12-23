/**
 * @file device_pc.h
 * @brief device for personal computer
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-25
 */

#include "device.h"

namespace DplDevice {

class DevicePc : public Device
{
public:
    explicit DevicePc();

    const QString &serial_number() const;
    bool is_valid() const;

private:
    QString m_serialNumber;
};

}
