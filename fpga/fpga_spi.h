#ifndef __FPGA_SPI_H__
#define __FPGA_SPI_H__

#include "spi.h"

#include <QMutex>

class FpgaSpi : Spi
{
public:
    static FpgaSpi *get_spi(void);

    bool send(char *data, quint32 len) { QMutexLocker l(&s_mutex); return s_spi->write(data, len); }

protected:
    FpgaSpi();

private:
    static FpgaSpi *s_spi;
    static QMutex s_mutex;
};

#endif // __FPGA_SPI_H__
