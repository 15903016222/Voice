
#include "mcu.h"

#ifdef PHASCAN_II
#include "mcu_imx.h"
#elif PHASCAN
#include "mcu_omap.h"
#else
#include "mcu_pc.h"
#endif

Mcu* Mcu::get_mcu()
{
#ifdef PHASCAN_II
    Mcu* mcu = new McuImx();
#elif PHASCAN
    static Mcu* mcu = new McuOmap();
#else
    Mcu* mcu = new McuPc();
#endif
    return mcu;
}
