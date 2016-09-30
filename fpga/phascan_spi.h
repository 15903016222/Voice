#ifndef __PHASCAN_SPI_H__
#define __PHASCAN_SPI_H__

#include "spi.h"

#include <QMutex>

class PhascanSpi : public Spi
{
public:
    static PhascanSpi* get_spi(void);

    bool send(const char *data, int len);

protected:
    PhascanSpi();

private:
    static PhascanSpi *s_spi;
    static QMutex s_mutex;

    void little_to_big(quint32 *data, int n);
};

#endif // __PHASCAN_SPI_H__
