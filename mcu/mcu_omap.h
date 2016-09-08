#ifndef __MCU_OMAP_H__
#define __MCU_OMAP_H__

#include "mcu_p.h"

//#include <QSeri

class McuOmap
{
public:
    McuOmap* get_instance();
    void destroyed();

protected:
    McuOmap();
    ~McuOmap() {}

private:
    static McuOmap *m_mcuOmap;
};

inline McuOmap* McuOmap::get_instance()
{
    if (m_mcuOmap == NULL) {
        m_mcuOmap = new McuOmap();
    }
    return m_mcuOmap;
}

inline void McuOmap::destroyed()
{
    if (m_mcuOmap) {
        delete m_mcuOmap;
        m_mcuOmap = NULL;
    }
}


#endif
