
#include "mcu.h"

#ifdef PHASCAN_II
#include "mcu_imx.h"
#else
#include "mcu_omap.h"
#endif

QMutex Mcu::m_mutex;
Mcu* Mcu::m_mcu = NULL;

Mcu* Mcu::get_mcu()
{
    QMutexLocker locker(&m_mutex);
    if (m_mcu == NULL) {
#ifdef PHASCAN_II
        m_mcu = new McuImx();
#else
        m_mcu = new McuOmap();
#endif
    }
    return m_mcu;
}

void Mcu::destroyed()
{
    QMutexLocker locker(&m_mutex);
    if (m_mcu != NULL) {
        delete m_mcu;
        m_mcu = NULL;
    }
}
