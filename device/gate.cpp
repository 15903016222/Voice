#include "gate.h"

namespace DplDevice {

Gate::Gate(Type type, QObject *parent) :
    QObject(parent),
    m_type(type),
    m_start(0.0),
    m_width(5000),
    m_height(25)
{

}

Gate::~Gate()
{
}

}
