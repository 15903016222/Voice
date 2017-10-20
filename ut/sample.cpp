#include "sample.h"
#include <fpga/fpga.h>

namespace DplUt {

const int Sample::MAX_SCALE_FACTOR;

class SamplePrivate
{
public:
    SamplePrivate(const DplFpga::GroupPointer &fpgaGrp) :
        m_fpgaGrp(fpgaGrp),
        m_dBRefFlag(false),
        m_dBRef(0),
        m_autoset(true)
    {}

    /**
     * @brief auto_point_qty    获取自动采样点数
     * @return                  采样点数
     */
    int auto_point_qty(float range) const;

    /* attributions */
    DplFpga::GroupPointer m_fpgaGrp;
    bool m_dBRefFlag;
    float m_dBRef;
    bool m_autoset;                     // 自动设置采样点标志
};

int SamplePrivate::auto_point_qty(float range) const
{
    const int maxPointQty = range / DplFpga::Fpga::SAMPLE_PRECISION;
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

Sample::Sample(const DplFpga::GroupPointer &fpgaGrp) : QObject(),
    m_start(0),
    m_range(57020),
    d(new SamplePrivate(fpgaGrp))
{
    connect(this,
            SIGNAL(scale_factor_changed(int)),
            static_cast<DplFpga::Group *>(d->m_fpgaGrp.data()),
            SLOT(set_scale_factor(int)));
}

float Sample::precision() const
{
    return DplFpga::Fpga::SAMPLE_PRECISION;
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

void Sample::set_range(float range)
{
    int maxPointQty = range / DplFpga::Fpga::SAMPLE_PRECISION;

    int curPointQty = d->m_fpgaGrp->point_qty();
    if (d->m_autoset) {
        curPointQty = d->auto_point_qty(range);
    }

    if (maxPointQty%curPointQty) {
        /* 类似四舍五入 */
        maxPointQty = ((maxPointQty + curPointQty/2)/curPointQty)*curPointQty;
    }

    bool rangeEmitFlag = false;
    range = maxPointQty * DplFpga::Fpga::SAMPLE_PRECISION;
    if ( !qFuzzyCompare(range, m_range) ) {
        m_range = range;
        rangeEmitFlag = true;
    }

    if (curPointQty != d->m_fpgaGrp->point_qty()) {
        d->m_fpgaGrp->set_point_qty(curPointQty);
        emit point_qty_changed(curPointQty);
    }

    if (rangeEmitFlag) {
        emit range_changed(range);
    }

    emit scale_factor_changed(maxPointQty/curPointQty);
}

int Sample::point_qty() const
{
    return d->m_fpgaGrp->point_qty();
}

bool Sample::is_auto_set_point_qty() const
{
    return d->m_autoset;
}

int Sample::max_point_qty() const
{
    return m_range / DplFpga::Fpga::SAMPLE_PRECISION;
}

bool Sample::set_point_qty(int qty, bool autoset)
{
    d->m_autoset = autoset;
    if (autoset) {
        qty = d->auto_point_qty(m_range);
    }

    if (qty != d->m_fpgaGrp->point_qty()) {
        d->m_fpgaGrp->set_point_qty(qty);
        set_range(m_range);
        emit point_qty_changed(qty);
    }

    return true;
}

}
