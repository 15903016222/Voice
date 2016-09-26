#include "phascan_fpga.h"

PhascanFpga::PhascanFpga()
{
    m_spi.setFileName("/dev/spidev1.0");
    m_spi.set_mode(Spi::MODE0);
}

bool PhascanFpga::reset()
{
    return false;
}

void PhascanFpga::little_to_big(quint32 *data, int n)
{
    quint32 *p = data;
    for (int i = 0; i < n; ++i) {
        *p = ((*p)<<24) | ((*p<<8) & 0xff0000) | ((*p>>8)&0xff00) | ((*p)>>24);
        ++p;
    }
}

bool PhascanFpga::send(const char *data, int len)
{
    QMutexLocker l(&m_mutex);
    if ( ! m_spi.isOpen()
         || data == NULL
         || len <= 0
         || len/4 != 0) {
        return false;
    }

    char buf[len] = {0};
    memcpy(buf, data, len);
    little_to_big(buf, len/4);
    return (!! m_spi.write(buf, len));
}
