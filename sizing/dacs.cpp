/**
 * @file dacs.cpp
 * @brief DAC(Distance Amplitude Correction)组
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-12-07
 */
#include "dacs.h"
#include <QVector>

namespace DplSizing {

class DacsPrivate : public QObject
{
public:
    DacsPrivate() :
        m_enabled(false),
        m_curTcg(0),
        m_curPoint(0),
        m_pointQty(1),
        m_amplitude(80),
        m_gain(0)
    {}

    /* attributions */
    bool m_enabled;
    int m_curTcg;
    int m_curPoint;
    int m_pointQty;
    float m_amplitude;
    float m_gain;
    float m_step;

    QVector<DacPointer> m_dacs;
};

Dacs::Dacs(QObject *parent) : QObject(parent),
    d(new DacsPrivate())
{

}

Dacs::~Dacs()
{
    delete d;
}

bool Dacs::enabled() const
{
    return d->m_enabled;
}

void Dacs::set_enabled(bool flag)
{
    if (flag != d->m_enabled) {
        d->m_enabled = flag;
        emit enabled_changed(flag);
    }
}

float Dacs::reference_amplitude() const
{
    d->m_amplitude;
}

bool Dacs::set_reference_amplitude(float val)
{
    if (val > 100 || val < 0) {
        return false;
    }
    d->m_amplitude = val;
    return true;
}

float Dacs::reference_gain() const
{
    return d->m_gain;
}

bool Dacs::set_reference_gain(float gain)
{
    if (qFuzzyIsNull(d->m_gain - gain)) {
        return false;
    }

    d->m_gain = gain;
    return true;
}

float Dacs::step() const
{
    return d->m_step;
}

bool Dacs::set_step(float val) const
{
    if (qFuzzyIsNull(d->m_step - val)) {
        return false;
    }
    d->m_step = val;
    return true;
}

DacPointer Dacs::current_dac() const
{
    return d->m_dacs[d->m_curTcg];
}

int Dacs::current_dac_index() const
{
    return d->m_curTcg;
}

bool Dacs::set_current_dac(int index)
{
    if (index >= d->m_dacs.count()) {
        return false;
    }

    d->m_curTcg = index;

    return true;
}

int Dacs::current_point() const
{
    return d->m_curPoint;
}

float Dacs::current_position() const
{
    return d->m_dacs[d->m_curTcg]->position(d->m_curPoint);
}

bool Dacs::set_current_point(int index)
{
    if (index >= d->m_pointQty - 1) {
        return false;
    }

    d->m_curPoint = index;

    return true;
}

bool Dacs::add_point()
{
    if (d->m_pointQty >= Dac::MAX_POINT_QTY-1) {
        return false;
    }

    d->m_curPoint = d->m_pointQty;
    ++d->m_pointQty;

    return true;
}

bool Dacs::delete_point()
{
    if (d->m_pointQty <= 1) {
        return false;
    }

    --d->m_pointQty;

    if (d->m_curPoint >= d->m_pointQty) {
        d->m_curPoint = d->m_pointQty - 1;
    }

    return true;
}

}
