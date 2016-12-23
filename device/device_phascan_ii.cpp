/**
 * @file device_phascan_ii.cpp
 * @brief Device for Phascan II
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */

#include "device_phascan_ii.h"

#include <QDebug>

/* unix */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

namespace DplDevice {

DevicePhascanII::DevicePhascanII() :
    Device()
{
    m_serialNo = get_serial_number();
}

bool DevicePhascanII::is_valid() const
{
    if (get_cert().get_serial_number() != m_serialNo) {
        return false;
    }
    if (get_cert().get_auth_mode() == Cert::ALWAYS_VALID) {
        return true;
    } else if (get_cert().get_auth_mode() == Cert::VALID_DATE) {
        return (get_cert().get_expire() > ::time(NULL));
    }
    return false;
}

QString DevicePhascanII::get_serial_number()
{
    QString serialNo;
    int fd = ::open("/dev/mem", O_RDWR | O_NDELAY);
    unsigned char *base = NULL;

    if ( fd < 0) {
        qWarning("Can't Open /dev/mem");
        return serialNo;
    }

    base = (unsigned char *)
            ::mmap (NULL,  1*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd,0x021bc000);

    if (base == MAP_FAILED) {
        ::close(fd);
        return serialNo;
    }

    serialNo.sprintf("%08lx-%08lx-%08lx-%08lx",
                     *(volatile long *)(base+0x410),
                     *(volatile long *)(base+0x420),
                     *(volatile long *)(base+0x430),
                     *(volatile long *)(base+0x440)
                     );

//    serialNo.sprintf("%08lx-%08lx-%08lx-%08lx-%08lx-%08lx--%08lx",
//                     *(volatile long *)(base+0x410),
//                     *(volatile long *)(base+0x420),
//                     *(volatile long *)(base+0x430),
//                     *(volatile long *)(base+0x440),
//                     *(volatile long *)(base+0x450),
//                     *(volatile long *)(base+0x460),
//                     *(volatile long *)(base+0x470)
//                     );
    ::munmap(base, 1*1024);
    ::close(fd);
    return serialNo;
}

}
