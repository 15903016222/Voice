#include "sample.h"

namespace DplUt {

const int Sample::MAX_SCALE_FACTOR;

class SamplePrivate
{
public:
    SamplePrivate(const DplFpga::GroupPointer &fpgaGrp) :
        m_fpgaGrp(fpgaGrp),
        m_dBRefFlag(false),
        m_dBRef(0)
    {}

    /* attributions */
    DplFpga::GroupPointer m_fpgaGrp;
    bool m_dBRefFlag;
    float m_dBRef;
};

Sample::Sample(const DplFpga::GroupPointer &fpgaGrp, float precision) :
    QObject(),
    m_precision(precision),
    m_start(0),
    m_range(57020),
    m_autoSetPointQty(true),
    m_pointQty(605),
    d(new SamplePrivate(fpgaGrp))
{
}

float Sample::gain() const
{
    return d->m_fpgaGrp->gain();
}

void Sample::set_gain(float gain)
{
    if (!qFuzzyCompare(gain, d->m_fpgaGrp->gain())) {
        d->m_fpgaGrp->set_gain(gain);
        emit gain_changed(gain);
    }
}

static int get_auto_point_qty(int maxPointQty)
{
    int widthPointQty = 640;

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

void Sample::set_range(float range)
{
    int maxPointQty = range / m_precision;
    int curPointQty = m_pointQty;

    if (m_autoSetPointQty) {
        curPointQty = get_auto_point_qty(maxPointQty);
    }

    if (maxPointQty%curPointQty) {
        /* 类似四舍五入 */
        maxPointQty = ((maxPointQty + curPointQty/2)/curPointQty)*curPointQty;
    }

    bool rangeEmitFlag = false;
    range = maxPointQty * m_precision;
    if ( !qFuzzyCompare(range, m_range) ) {
        m_range = range;
        rangeEmitFlag = true;
    }

    bool pointQtyEmitFlag = false;
    if (curPointQty != m_pointQty) {
        m_pointQty = curPointQty;
        pointQtyEmitFlag = true;
    }

    if (rangeEmitFlag) {
        emit range_changed(range);
    }

    if (pointQtyEmitFlag) {
        emit point_qty_changed(curPointQty);
    }

    if (rangeEmitFlag || pointQtyEmitFlag) {
        emit scale_factor_changed(maxPointQty/curPointQty);
    }
}
}
