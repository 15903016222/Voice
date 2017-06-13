/**
 * @file device_phascan_ii.cpp
 * @brief Device for Phascan II
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2016-10-21
 */

#include "device_p.h"

#include <QDebug>

/* unix */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

namespace DplDevice {

QString DevicePrivate::get_serial_number()
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
