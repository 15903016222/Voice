#include "group_p.h"

#include <source/source.h>

namespace DplDevice {

GroupPrivate::GroupPrivate(Group *parent) :
    QObject(),
    q(parent),
    m_mode(Group::PA),
    m_utUnit(Group::SoundPath),
    m_currentAngle(M_PI/6),
    m_source(DplSource::Source::instance()),
    m_index(0)
{

}

void GroupPrivate::do_source_data_event()
{
    m_beams = m_source->current_beams(q->index());
    m_beam = m_beams->get(m_index);
    emit q->data_event(m_beams);
}

}
