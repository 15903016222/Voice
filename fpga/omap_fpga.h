#ifndef __OMAP_FPGA_H__
#define __OMAP_FPGA_H__

#include "fpga.h"

class OmapFpga : public Fpga
{
public:
    OmapFpga();
    bool reset();
};

#endif // __OMAP_FPGA_H__
