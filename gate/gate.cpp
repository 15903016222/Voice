#include "gate.h"

namespace DplGate {

class GatePrivate
{
public:
    GatePrivate(const DplFpga::GroupPointer &fpgaGrp, DplFpga::Group::GateType type, const QColor &color) :
        m_fpgaGrp(fpgaGrp),
        m_type(type),
        m_start(0.0),
        m_width(5000),
        m_visible(false),
        m_color(color)
    {}

    /* attributions */
    DplFpga::GroupPointer m_fpgaGrp;
    DplFpga::Group::GateType m_type;
    float m_start;      // 起点(ns)
    float m_width;      // 宽度(ns)
    bool m_visible;     // 可视标志
    QColor m_color;     // 闸门显示颜色
};

Gate::Gate(const DplFpga::GroupPointer &fpgaGrp, DplFpga::Group::GateType type, const QColor &color) : QObject(),
    d(new GatePrivate(fpgaGrp, type, color))
{
}

Gate::~Gate()
{
    delete d;
}

DplFpga::Group::GateType Gate::type() const
{
    return d->m_type;
}

float Gate::start() const
{
    return d->m_start;
}

void Gate::set_start(float val)
{
    if (!qFuzzyCompare(val, d->m_start)) {
        d->m_start = val;
        emit start_changed(val);
    }
}

float Gate::width() const
{
    return d->m_width;
}

void Gate::set_width(float val)
{
    if (!qFuzzyCompare(val, d->m_width)) {
        d->m_width = val;
        emit width_changed(val);
    }
}

int Gate::height() const
{
    return d->m_fpgaGrp->gate_height(d->m_type);
}

void Gate::set_height(int val)
{
    if (val != d->m_fpgaGrp->gate_height(d->m_type)) {
        d->m_fpgaGrp->set_gate_height(d->m_type, val);
        emit height_changed(val);
    }
}

bool Gate::is_visible() const
{
    return d->m_visible;
}

void Gate::set_visible(bool visible)
{
    if (visible != d->m_visible) {
        d->m_visible = visible;
        emit visible_changed(visible);
    }
}

const QColor &Gate::color() const
{
    return d->m_color;
}

void Gate::set_color(const QColor &color)
{
    if (d->m_color != color) {
        d->m_color = color;
        emit color_changed(color);
    }
}

DplFpga::Group::MeasureMode Gate::measure_mode() const
{
    return d->m_fpgaGrp->gate_measure_mode(d->m_type);
}

void Gate::set_measure_mode(DplFpga::Group::MeasureMode mode)
{
    if (mode != d->m_fpgaGrp->gate_measure_mode(d->m_type)) {
        d->m_fpgaGrp->set_gate_measure_mode(d->m_type, mode);
        emit measure_mode_changed(mode);
    }
}

DplFpga::Group::SynchroMode Gate::synchro_mode() const
{
    return d->m_fpgaGrp->gate_synchro_mode(d->m_type);
}

void Gate::set_synchro_mode(DplFpga::Group::SynchroMode mode)
{
    if (mode != d->m_fpgaGrp->gate_synchro_mode(d->m_type)) {
        d->m_fpgaGrp->set_gate_synchro_mode(d->m_type, mode);
        emit synchro_mode_changed(mode);
    }
}

}
