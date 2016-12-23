/**
 * @file device_phascan.cpp
 * @brief Device for Phascan
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-07
 */
#include "device_phascan.h"

/* unix */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <QDebug>

namespace DplDevice {

DevicePhascan::DevicePhascan() :
    Device()
{
    m_serialNo = get_serial_number();
}

bool DevicePhascan::is_valid() const
{
    bool flag = false;
    if (get_cert().get_serial_number() == m_serialNo) {
        switch (get_cert().get_auth_mode()) {
        case Cert::ALWAYS_VALID:
            flag = true;
            break;
        case Cert::VALID_DATE:
            flag = (get_cert().get_expire() > ::time(NULL));
            break;
        default:
            break;
        }
    }
    return flag;
}

QString DevicePhascan::get_serial_number()
{
    QString serialNo;
    int fd = ::open("/dev/mem", O_RDWR | O_NDELAY);
    unsigned char *base = NULL;

    if ( fd < 0) {
        qWarning("Cannot Open /dev/mem");
        return serialNo;
    }

    base = (unsigned char *)
        ::mmap (NULL,  4*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x4830a000);

    if (base == MAP_FAILED) {
        ::close(fd);
        return serialNo;
    }

    serialNo.sprintf("%08lx-%08lx-%08lx-%08lx",
                           *(volatile long *)(base+0x224),
                           *(volatile long *)(base+0x220),
                           *(volatile long *)(base+0x21c),
                           *(volatile long *)(base+0x218));
    ::munmap(base, 4*1024);
    ::close(fd);
    return serialNo;
}

}
