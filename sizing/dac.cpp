/**
 * @file dac.cpp
 * @brief DAC(Distance Amplitude Correction) 距离幅度校准
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-12-07
 */

#include "dac.h"

namespace DplSizing {

class DacPrivate
{
public:
    DacPrivate()
    {
        ::memset(m_pos, 0, sizeof(m_pos));
        ::memset(m_amplitude, 0, sizeof(m_amplitude));
    }

    float m_pos[Dac::MAX_POINT_QTY];
    float m_amplitude[Dac::MAX_POINT_QTY];
};

Dac::Dac() : QObject(0),
    d(new DacPrivate)
{

}

float Dac::position(int point)
{
    if (point >= MAX_POINT_QTY) {
        return 0.0;
    }
    return d->m_pos[point];
}

bool Dac::set_position(int point, float pos)
{
    if (point >= MAX_POINT_QTY
            || qFuzzyCompare(d->m_pos[point], pos)) {
        return false;
    }
    d->m_pos[point] = pos;
    return true;
}

float Dac::amplitude(int point) const
{
    if (point >= MAX_POINT_QTY) {
        return 0.0;
    }
    return d->m_amplitude[point];
}

bool Dac::set_amplitude(int point, float val)
{
    if (point >= MAX_POINT_QTY
            || qFuzzyCompare(d->m_amplitude[point], val)) {
        return false;
    }
    d->m_amplitude[point] = val;
    return true;
}

}
