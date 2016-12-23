/**
 * @file device_pc.cpp
 * @brief device for personal computer
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-25
 */

#include "device_pc.h"

namespace DplDevice {

DevicePc::DevicePc() :
    Device()
{
    m_serialNumber = "1234-5678-90";
}

bool DevicePc::is_valid() const
{
    return true;
}


}
