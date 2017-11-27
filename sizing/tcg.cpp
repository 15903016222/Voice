#include "tcg.h"
#include <fpga/tcg.h>
#include <qmath.h>

namespace DplSizing {

class TcgPrivate
{
public:
    TcgPrivate(int index) :
        m_tcg(new DplFpga::Tcg(index))
    {}

    DplFpga::TcgPointer m_tcg;
};

Tcg::Tcg(int index) :
    d(new TcgPrivate(index))
{
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
    if (point == 0) {
        return 80000.0;
    }
    return (80000.0)/ qPow(10, d->m_tcg->gain(point)/20);
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

bool Tcg::set_gain(int point, int val)
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
