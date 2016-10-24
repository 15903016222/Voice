
#include "gpio.h"

#ifdef PHASCAN_II
#define GPIO_DEV    ""
#elif PHASCAN
#define GPIO_DEV    "/dev/tt"
#else
#error "No specify device"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <QDebug>

struct GpioPrivate {
    int fd;
    QMutex mutex;
};

QMutex Gpio::m_mutex;
Gpio *Gpio::m_gpio = NULL;

Gpio *Gpio::get_gpio()
{
    QMutexLocker locker(&m_mutex);
    if (m_gpio == NULL) {
        m_gpio = new Gpio();
    }
    return m_gpio;
}

void Gpio::destroy()
{
    QMutexLocker locker(&m_mutex);
    if (m_gpio != NULL) {
        delete m_gpio;
    }
    m_gpio = NULL;
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
    ::close(d->fd);
    d->fd = -1;
}

bool Gpio::set(GpioPin pinNo, PinState state)
{
    QMutexLocker locker(&d->mutex);
    if (d->fd<0) {
        return false;
    }
    return !! ::ioctl(d->fd, pinNo+state, 0);
}
