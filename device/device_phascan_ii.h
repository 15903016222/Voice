/**
 * @file device_phascan_ii.h
 * @brief Device for Phascan II
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */

#include "device.h"

namespace DplDevice {

class DevicePhascanII : public Device
{
public:
    explicit DevicePhascanII();

    const QString &serial_number() const { return m_serialNo; }

    bool is_valid() const;

private:
    QString m_serialNo;
    QString get_serial_number();
};

}
