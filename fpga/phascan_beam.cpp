#include "phascan_beam.h"

#include "fpga.h"

#define BEAM_REG_NUM    (80)

PhascanBeam::PhascanBeam(const int index = 0)
    : Beam(index), m_fpga(Fpga::get_fpga())
{
    d.addr = 0b0001;
    d.offset = BEAM_REG_NUM * index;
}
