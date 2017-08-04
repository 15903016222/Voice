#include "display.h"

namespace DplDisplay {

Display::Display(QObject *parent) :
    QObject(parent),
    m_layout(A),
    m_grps(1, 0),
    m_ascan(new Ascan())
{

}

}
