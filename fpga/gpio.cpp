
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

QMutex Gpio::m_mutex;
QAtomicPointer<Gpio> Gpio::m_gpio = 0;

Gpio& Gpio::get_gpio()
{
    QMutexLocker locker(&m_mutex);
    if (m_gpio.testAndSetOrdered(0, 0)) {
        m_gpio.testAndSetOrdered(0, new Gpio());
    }
    return *m_gpio;
}

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
    QMutexLocker locker(&m_mutex);
    ::close(d->fd);
    d->fd = -1;
}

bool Gpio::set(GpioPin pinNo, PinState state)
{
    QMutexLocker locker(&m_mutex);
    if (d->fd<0) {
        return false;
    }
    return !! ::ioctl(d->fd, pinNo+state, 0);
}
