/**
 * @file tcg.cpp
 * @brief The Time-Corrected Gain
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-12-07
 */
#include "tcg.h"
#include <fpga/tcg.h>
#include <qmath.h>

namespace DplSizing {

class TcgPrivate
{
public:
    TcgPrivate(int index) :
        m_refAmplitude(80),
        m_tcg(new DplFpga::Tcg(index))
    {}

    float m_refAmplitude;
    DplFpga::TcgPointer m_tcg;
};

Tcg::Tcg(int index) :
    d(new TcgPrivate(index))
{
    set_position(0, 20);
}

Tcg::~Tcg()
{
    delete d;
}

int Tcg::index() const
{
    return d->m_tcg->index();
}

int Tcg::position(int point) const
{
    return d->m_tcg->position(point);
}

float Tcg::gain(int point) const
{
    return d->m_tcg->gain(point);
}

float Tcg::amplitude(int point) const
{
    return d->m_refAmplitude -  d->m_refAmplitude / pow(10, d->m_tcg->gain(point)/20);
}

float Tcg::ref_amplitude() const
{
    return d->m_refAmplitude;
}

void Tcg::set_ref_amplitude(float refAmplitude) const
{
    d->m_refAmplitude = refAmplitude;
}

void Tcg::set_index(int index)
{
    d->m_tcg->set_index(index);
}

bool Tcg::set_position(int point, int val)
{
    if (!d->m_tcg->set_position(point, val)) {
        return false;
    }
    return d->m_tcg->deploy();
}

bool Tcg::set_gain(int point, float val)
{
    if ( !d->m_tcg->set_gain(point, val) ) {
        return false;
    }
    return d->m_tcg->deploy();
}

bool Tcg::deploy() const
{
    return d->m_tcg->deploy();
}


}
