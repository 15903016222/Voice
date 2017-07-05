#include "sample.h"

namespace DplDevice {

const int Sample::MAX_SCALE_FACTOR;

Sample::Sample(float precision, QObject *parent) :
    QObject(parent),
    m_precision(precision),
    m_gain(20.0),
    m_start(0),
    m_velocity(3240),
    m_scaleFactor(9),
    m_pointQty(605)
{
    connect(this, SIGNAL(scale_factor_changed(int)),
            this, SIGNAL(range_changed()));
    connect(this, SIGNAL(point_qty_changed(int)),
            this, SIGNAL(range_changed()));
}

}
