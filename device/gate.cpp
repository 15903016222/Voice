#include "gate.h"

namespace DplDevice {

Gate::Gate(Type type, QObject *parent) :
    QObject(parent),
    m_type(type),
    m_start(0.0),
    m_width(5000),
    m_height(25)
{
    connect(this, SIGNAL(height_changed(int)),
            this, SIGNAL(changed()));
    connect(this, SIGNAL(start_changed(float)),
            this, SIGNAL(changed()));
}

Gate::~Gate()
{
}

}
