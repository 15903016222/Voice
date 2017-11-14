#include "sample_p.h"
#include "global_transceiver.h"

namespace DplUt {

SamplePrivate::SamplePrivate(const DplFpga::GroupPointer &fpgaGrp)  : QObject(),
    m_fpgaGrp(fpgaGrp),
    m_dBRefFlag(false),
    m_dBRef(0),
    m_autoset(true)
{
    connect(DplUt::GlobalTransceiver::instance(),
            SIGNAL(prf_changed()),
            this,
            SLOT(do_prf_changed()));
}

int SamplePrivate::auto_point_qty(int maxPointQty) const
{
    const int widthPointQty = 640;

    if (maxPointQty <= widthPointQty) {
        return maxPointQty;
    } else {
        int scaleFactor = maxPointQty / widthPointQty;
        if (maxPointQty % widthPointQty) {
            ++scaleFactor;
        }
        return maxPointQty / scaleFactor;
    }
}

void SamplePrivate::do_prf_changed()
{
    m_fpgaGrp->set_sample_cycle(DplUt::GlobalTransceiver::instance()->beam_cycle()/DplFpga::Fpga::SAMPLE_PRECISION);
}

}
