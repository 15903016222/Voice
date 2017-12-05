/**
 * @file tcgs.cpp
 * @brief Tcg组
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-11-20
 */
#include "tcgs_p.h"

namespace DplSizing {

Tcgs::Tcgs(const DplFpga::GroupPointer &fpgaGroup, const DplFocallaw::FocallawerPointer &focallawer) : QObject(),
    d(new TcgsPrivate(this, fpgaGroup, focallawer))
{
}

Tcgs::~Tcgs()
{
    delete d;
}

bool Tcgs::enable() const
{
    return d->m_fpgaGrp->tcg();
}

bool Tcgs::set_enable(bool flag)
{
    return d->m_fpgaGrp->enable_tcg(flag);
}

int Tcgs::count() const
{
    return d->m_tcgs.count();
}

TcgPointer Tcgs::tcg(int index) const
{
    return d->m_tcgs.value(index);
}

TcgPointer Tcgs::current_tcg() const
{
    return d->m_tcgs[d->m_currentTcg];
}

int Tcgs::point_count() const
{
    return d->m_pointQty;
}

bool Tcgs::add_point()
{
    if (d->m_pointQty >= 16) {
        return false;
    }

    int prePosition = d->m_tcgs[d->m_currentTcg]->position(d->m_pointQty-1);
    float preGain = d->m_tcgs[d->m_currentTcg]->gain(d->m_pointQty-1);

    d->m_pointQty += 1;
    if (! d->m_fpgaGrp->set_tcg_point_qty(d->m_pointQty)) {
        d->m_pointQty -= 1;
        return false;
    }

    d->m_currentPoint = d->m_pointQty-1;

    set_position(prePosition + 2000);
    set_gain(preGain);

    emit current_point_changed();
    return true;
}

bool Tcgs::delete_point()
{
    if (d->m_pointQty <= 1) {
        return false;
    }

    d->m_pointQty -= 1;
    if (! d->m_fpgaGrp->set_tcg_point_qty(d->m_pointQty)) {
        d->m_pointQty += 1;
        return false;
    }

    if (d->m_currentPoint >= d->m_pointQty) {
        d->m_currentPoint = d->m_pointQty - 1;
        emit current_point_changed();
    }

    return true;
}

bool Tcgs::set_current_tcg(int index)
{
    if (index < 0
            || index >= d->m_tcgs.count()
            || index == d->m_currentTcg) {
        return false;
    }
    d->m_currentTcg = index;
    emit current_point_changed();
    return true;
}

int Tcgs::current_point_index() const
{
    return d->m_currentPoint;
}

bool Tcgs::set_current_point(int index)
{
    if (index<0
            || index >= point_count()
            || index == d->m_currentPoint) {
        return false;
    }
    d->m_currentPoint = index;
    emit current_point_changed();
    return true;
}

void Tcgs::set_all(bool flag)
{
    d->m_allFlag = flag;
}

int Tcgs::position() const
{
    return d->m_tcgs[d->m_currentTcg]->position(d->m_currentPoint);
}

bool Tcgs::set_position(int val)
{
    if (d->m_allFlag) {
        foreach (DplSizing::TcgPointer tcg, d->m_tcgs) {
            if ( !tcg->set_position(d->m_currentPoint, val) ) {
                return false;
            }
        }
        return true;
    } else {
        return d->m_tcgs[d->m_currentTcg]->set_position(d->m_currentPoint, val);
    }
}

float Tcgs::gain() const
{
    return d->m_tcgs[d->m_currentTcg]->gain(d->m_currentPoint);
}

bool Tcgs::set_gain(float val)
{
    if (d->m_allFlag) {
        foreach (DplSizing::TcgPointer tcg, d->m_tcgs) {
            if (!tcg->set_gain(d->m_currentPoint, val)) {
                return false;
            }
        }
        return true;
    } else {
        return d->m_tcgs[d->m_currentTcg]->set_gain(d->m_currentPoint, val);
    }
}

float Tcgs::amplitude() const
{
    return d->m_tcgs[d->m_currentTcg]->amplitude(d->m_currentPoint);
}

}
