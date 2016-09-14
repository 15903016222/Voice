
#include "gpio.h"

#ifdef PHASCAN_II
#define GPIO_DEV    ""
#else /* Phascan */
#define GPIO_DEV    "/dev/tt"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <QDebug>

struct GpioPrivate {
    int fd;
};

Gpio* Gpio::m_gpio = nullptr;

Gpio::Gpio()
    : d(new GpioPrivate())
{
    d->fd = ::open(GPIO_DEV, O_RDWR);
    if (d->fd < 0) {
        qCritical()<<"Open"<<GPIO_DEV<<"failed";
    }
}

Gpio::~Gpio()
{
    ::close(d->fd);
    d->fd = -1;
}

bool Gpio::set(GpioPin pinNo, PinState state)
{
    if (d->fd<0) {
        return false;
    }
    return !::ioctl(d->fd, pinNo+state, nullptr);
}
