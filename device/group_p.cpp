#include "group_p.h"

namespace DplDevice {

GroupPrivate::GroupPrivate(Group *parent) :
    QObject(),
    q_ptr(parent),
    m_mode(Group::PA),
    m_utUnit(Group::SoundPath),
    m_currentAngle(M_PI/6)
{
}

}
