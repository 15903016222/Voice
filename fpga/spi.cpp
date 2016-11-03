#include "spi.h"

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>

Spi::Spi()
    : m_fd(-1), m_mode(MODE0), m_bits(8), m_speed(500*1000), m_lsbFirst(false)
{
}

Spi::~Spi()
{
    close();
}

bool Spi::open(const char *name)
{
    if (is_open()) {
        close();
    }
    m_fd = ::open(name, O_RDWR);

    set_mode(m_mode);
    set_bits_per_word(m_bits);
    set_speed(m_speed);

    return is_open();
}

void Spi::close()
{
    ::close(m_fd);
    m_fd = -1;
}

bool Spi::is_open() const
{
    return m_fd > 0;
}

bool Spi::set_mode(Spi::SpiMode mode)
{
    if (! is_open()) {
        return false;
    }

    if ( ::ioctl(m_fd, SPI_IOC_WR_MODE, &mode) == -1 ) {
        return false;
    }

    if ( ::ioctl(m_fd, SPI_IOC_RD_MODE, &m_mode) == -1) {
        return false;
    }

    return true;
}

bool Spi::set_bits_per_word(quint8 bits)
{
    if (! is_open()) {
        return false;
    }
    if ( ::ioctl(m_fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1 ) {
        return false;
    }
    if ( ::ioctl(m_fd, SPI_IOC_RD_BITS_PER_WORD, &m_bits) == -1 ) {
        return false;
    }
    return true;
}

bool Spi::set_speed(quint32 speed)
{
    if (! is_open()) {
        return false;
    }
    if (::ioctl(m_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
        return false;
    }
    if (::ioctl(m_fd, SPI_IOC_RD_MAX_SPEED_HZ, &m_speed) == -1) {
        return false;
    }
    return true;
}

bool Spi::set_lsb_first(bool flag)
{
    char lsb = flag;
    if (! is_open()) {
        return false;
    }

    if (::ioctl(m_fd, SPI_IOC_WR_LSB_FIRST, &lsb) == -1) {
        return false;
    }

    if (::ioctl(m_fd, SPI_IOC_RD_LSB_FIRST, &lsb) == -1) {
        return false;
    }

    m_lsbFirst = !!lsb;

    return true;
}

static const int MAX_LEN = 32;
bool Spi::write(char *data, quint32 len)
{
    if (! is_open()) {
        return false;
    }

    int i = 0;
    const int j = len / MAX_LEN;
    const int k = len % MAX_LEN;
    struct spi_ioc_transfer xfer[j+1];
    ::memset(xfer, 0, sizeof(xfer));
    for (i=0; i<j; ++i) {
        xfer[i].tx_buf = (unsigned long)(data+i);
        xfer[i].len = MAX_LEN;
    }

    if (k != 0) {
        xfer[j].tx_buf = (unsigned long)(data + (j*MAX_LEN));
        xfer[j].len = k;
    }

    if (::ioctl(m_fd, SPI_IOC_MESSAGE(j+1), xfer) == -1) {
        return false;
    }

//    ::usleep(100);
    return true;
}

