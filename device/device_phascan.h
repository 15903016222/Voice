/**
 * @file device_phascan.h
 * @brief Device for Phascan
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */

#ifndef __DEVICE_PHASCAN_H__
#define __DEVICE_PHASCAN_H__

#include "device.h"

namespace DplDevice {

class DevicePhascan : public Device
{
public:
    explicit DevicePhascan();

    const QString &serial_number() const { return m_serialNo; }

    bool is_valid() const;

private:
    QString m_serialNo;
    QString get_serial_number();
};

}

#endif // __DEVICE_PHASCAN_H__
