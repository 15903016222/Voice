#include "tcgs_p.h"

namespace DplSizing {

TcgsPrivate::TcgsPrivate(Tcgs *parent, const DplFpga::GroupPointer &fpgaGroup, const DplFocallaw::FocallawerPointer &focallawer) :
    m_fpgaGrp(fpgaGroup),
    m_focallawer(focallawer),
    m_allFlag(true),
    m_currentTcg(0),
    m_currentPoint(0),
    m_pointQty(1),
    q(parent),
    m_beamQty(0)
{
    connect(DplDevice::Device::instance(),
            SIGNAL(beam_qty_changed()),
            this,
            SLOT(do_global_beam_qty_changed()));
    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(focallawed()),
            this,
            SLOT(do_focallawed()));
    do_focallawed();
}

bool TcgsPrivate::deploy_all() const
{
    int fstIndex = DplDevice::Device::instance()->first_beam_index(m_fpgaGrp->index());

    for (int i = 0; i < m_tcgs.count(); ++i) {
        m_tcgs[i]->set_index(i+fstIndex);
        if (!m_tcgs[i]->deploy()) {
            return false;
        }
    }

    return true;
}

void TcgsPrivate::do_global_beam_qty_changed()
{
    if (m_beamQty != m_focallawer->beam_qty()) {
        do_focallawed();
        return;
    }

    int fstIndex = DplDevice::Device::instance()->first_beam_index(m_fpgaGrp->index());
    for (uint i = 0; i < m_beamQty; ++i) {
        m_tcgs[i]->set_index(fstIndex+i);
        m_tcgs[i]->deploy();
    }
}

void TcgsPrivate::do_focallawed()
{
    m_currentPoint = 0;
    m_currentTcg = 0;

    if (m_beamQty == m_focallawer->beam_qty()) {
        return;
    }

    m_tcgs.clear();

    int fstIndex = DplDevice::Device::instance()->first_beam_index(m_fpgaGrp->index());
    m_beamQty = m_focallawer->beam_qty();

    for (uint i = 0; i < m_beamQty; ++i) {
        m_tcgs.append(TcgPointer(new Tcg(fstIndex+i)));
    }
}

}
