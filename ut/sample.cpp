#include "sample.h"
#include "sample_p.h"

namespace DplUt {

const int Sample::MAX_SCALE_FACTOR;

Sample::Sample(const DplFpga::GroupPointer &fpgaGrp) : QObject(),
    d(new SamplePrivate(fpgaGrp))
{
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

float Sample::start() const
{
    return d->m_fpgaGrp->sample_start() * DplFpga::Fpga::SAMPLE_PRECISION;
}

void Sample::set_start(float value)
{
    if (d->m_fpgaGrp->sample_start() != static_cast<int>(value/DplFpga::Fpga::SAMPLE_PRECISION)) {
        d->m_fpgaGrp->set_sample_start(value/DplFpga::Fpga::SAMPLE_PRECISION);
        emit start_changed(value);
    }
}

float Sample::range() const
{
    return d->m_fpgaGrp->sample_range() *DplFpga::Fpga::SAMPLE_PRECISION;
}

void Sample::set_range(float range)
{
    int maxPointQty = range / DplFpga::Fpga::SAMPLE_PRECISION;

    int curPointQty = d->m_fpgaGrp->point_qty();
    if (d->m_autoset) {
        curPointQty = d->auto_point_qty(maxPointQty);
    }

    if (maxPointQty%curPointQty) {
        /* 类似四舍五入 */
        maxPointQty = ((maxPointQty + curPointQty/2)/curPointQty)*curPointQty;
    }

    if ( d->m_fpgaGrp->sample_range() != maxPointQty) {
        d->m_fpgaGrp->set_sample_range(maxPointQty);
        emit range_changed(maxPointQty * DplFpga::Fpga::SAMPLE_PRECISION);
    }

    if (curPointQty != d->m_fpgaGrp->point_qty()) {
        d->m_fpgaGrp->set_point_qty(curPointQty);
        emit point_qty_changed(curPointQty);
    }

    d->m_fpgaGrp->set_scale_factor(maxPointQty/curPointQty);
    emit scale_factor_changed(maxPointQty/curPointQty);
}

int Sample::scale_factor() const
{
    return d->m_fpgaGrp->sample_range() / d->m_fpgaGrp->point_qty();
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
    return d->m_fpgaGrp->sample_range();
}

bool Sample::set_point_qty(int qty, bool autoset)
{
    d->m_autoset = autoset;
    if (autoset) {
        qty = d->auto_point_qty(d->m_fpgaGrp->sample_range());
    }

    if (qty != d->m_fpgaGrp->point_qty()) {
        d->m_fpgaGrp->set_point_qty(qty);
        set_range(d->m_fpgaGrp->sample_range()*DplFpga::Fpga::SAMPLE_PRECISION);
        emit point_qty_changed(qty);
    }

    return true;
}

}
