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
