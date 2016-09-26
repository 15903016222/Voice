#ifndef __PHASCAN_FPGA_H__
#define __PHASCAN_FPGA_H__

#include "fpga.h"
#include "spi.h"
#include <QMutex>

class PhascanFpga : public Fpga
{
public:
    PhascanFpga();
    bool reset();

    bool send(const char *data, int len);

private:
    Spi m_spi;
    QMutex m_mutex;

    void little_to_big(quint32 *data, int n);
};

#endif // __PHASCAN_FPGA_H__
