#include "spi.h"

#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

#include <QDebug>

bool Spi::set_mode(Spi::SpiMode mode)
{
    int fd = handle();
    if (fd < 0) {
        return false;
    }

    int val = 0;
    if (::ioctl(fd, SPI_IOC_RD_MODE, &val) == -1) {
        qWarning("read spi mode failed");
        return false;
    }

    val = (val&0xfc) | mode;
    if (::ioctl(fd, SPI_IOC_WR_MODE, &val) == -1) {
        qWarning("write spi mode failed");
        return false;
    }

    return true;
}

Spi::SpiMode Spi::mode()
{
    int fd = handle();
    int val = 0;
    if (fd < 0) {
        return MODE0;
    }
    if (::ioctl(fd, SPI_IOC_RD_MODE, &val) < 0) {
        return MODE0;
    }
    return (Spi::SpiMode)val;
}
