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

private:
    Spi m_spi;
    QMutex m_mutex;
};

#endif // __PHASCAN_FPGA_H__
