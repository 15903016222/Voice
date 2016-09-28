#include "phascan_spi.h"

QMutex PhascanSpi::m_mutex;
PhascanSpi* PhascanSpi::m_spi = NULL;

PhascanSpi* PhascanSpi::get_spi(void)
{
    QMutexLocker l(&m_mutex);
    if (m_spi == NULL) {
        m_spi = new PhascanSpi();
        m_spi->setFileName("/dev/spidev1.0");
        m_spi->set_mode(Spi::MODE0);
    }

    return m_spi;
}

void PhascanSpi::little_to_big(quint32 *data, int n)
{
    quint32 *p = data;
    for (int i = 0; i < n; ++i) {
        *p = ((*p)<<24) | ((*p<<8) & 0xff0000) | ((*p>>8)&0xff00) | ((*p)>>24);
        ++p;
    }
}

bool PhascanSpi::write(const char *data, int len)
{
    QMutexLocker l(&m_mutex);
    if ( ! isOpen()
         || data == NULL
         || len <= 0) {
        return false;
    }

    char buf[len] = {0};
    memcpy(buf, data, len);
    little_to_big(buf, len/4);
    return (!! Spi::write(buf, len));
}
