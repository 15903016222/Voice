#ifndef __DPL_TCGS_P_H__
#define __DPL_TCGS_P_H__

#include "tcgs.h"
#include <device/device.h>

namespace DplSizing {

class TcgsPrivate : public QObject
{
    Q_OBJECT
public:
    TcgsPrivate(Tcgs *parent, const DplFpga::GroupPointer &fpgaGroup, const DplFocallaw::FocallawerPointer &focallawer);

    /**
     * @brief deploy_all    下发所有TCG配置信息
     */
    bool deploy_all() const;

    /* attribution */
    DplFpga::GroupPointer m_fpgaGrp;
    DplFocallaw::FocallawerPointer m_focallawer;
    QVector<TcgPointer> m_tcgs;
    bool m_allFlag;
    int m_currentTcg;
    int m_currentPoint;
    int m_pointQty;

protected slots:
    void do_global_beam_qty_changed();
    void do_focallawed();

private:
    Tcgs *q;
    uint m_beamQty;
};

}

#endif // __DPL_TCGS_P_H__
