
#include "fpga.h"

#ifdef PHASCAN_II
#include "imx_fpga.h"
#else /* PHASCAN */
#include "omap_fpga.h"
#endif

#include <QDebug>

QMutex Fpga::m_mutex;
Fpga *Fpga::m_fpga = NULL;


Fpga *Fpga::get_fpga(void)
{
    QMutexLocker locker(&m_mutex);
    if (m_fpga == NULL) {
#ifdef PHASCAN_II
        m_fpga = new ImxFpga());
#elif PHASCAN
        m_fpga = new OmapFpga();
#else
#error("Not Specify Device")
#endif
    }

    return m_fpga;
}
