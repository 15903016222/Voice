
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
#else /* PHASCAN */
        m_fpga = new OmapFpga();
#endif
    }

    return m_fpga;
}
