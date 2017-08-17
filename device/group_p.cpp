#include "group_p.h"

#include <source/source.h>

namespace DplDevice {

GroupPrivate::GroupPrivate(Group *parent) :
    QObject(),
    q_ptr(parent),
    m_mode(Group::PA),
    m_utUnit(Group::SoundPath),
    m_currentAngle(M_PI/6),
    m_source(DplSource::Source::instance())
{

}

void GroupPrivate::do_source_data_event()
{
    DplSource::BeamsPointer beams = m_source->current_beams(q_ptr->index());
    emit q_ptr->data_event(beams);
}

}
