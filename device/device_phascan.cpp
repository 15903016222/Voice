/**
 * @file device_phascan.cpp
 * @brief Device for Phascan
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2016-11-07
 */
#include "device_p.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <QDebug>

namespace DplDevice {

QString DevicePrivate::get_serial_number()
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
