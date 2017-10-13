#include "receiver.h"

namespace DplUt {

class ReceiverPrivate
{
public:
    ReceiverPrivate(const DplFpga::GroupPointer &fpgaGrp) :
        m_probeFreq(0),
        m_fpgaGrp(fpgaGrp)
    {}

    /* attributions */
    int m_probeFreq;
    DplFpga::GroupPointer m_fpgaGrp;
};

Receiver::Receiver(const DplFpga::GroupPointer &fpgaGrp) : QObject(),
    d(new ReceiverPrivate(fpgaGrp))
{

}

Receiver::~Receiver()
{
    delete d;
}

int Receiver::filter() const
{
    return d->m_probeFreq;
}

void Receiver::set_filter(int freq)
{
    if (d->m_probeFreq == freq) {
        return;
    }

    d->m_probeFreq = freq;

    if (freq == 0) {
        d->m_fpgaGrp->set_filter(0);
    } else if (freq <= 1250) {
        d->m_fpgaGrp->set_filter(1);
    } else if (freq <= 2750) {
        d->m_fpgaGrp->set_filter(2);
    } else if (freq <= 6250) {
        d->m_fpgaGrp->set_filter(3);
    } else if (freq <= 8750) {
        d->m_fpgaGrp->set_filter(4);
    } else {
        d->m_fpgaGrp->set_filter(5);
    }

    emit filter_changed(freq);
}

DplFpga::Group::Rectifier Receiver::rectifier() const
{
    return d->m_fpgaGrp->rectifier();
}

void Receiver::set_rectifier(DplFpga::Group::Rectifier val)
{
    if ( d->m_fpgaGrp->rectifier() != val) {
        d->m_fpgaGrp->set_rectifier(val);
        emit recitifier_changed(val);
    }
}

bool Receiver::video_filter() const
{
    return d->m_fpgaGrp->video_filter();
}

void Receiver::set_video_filter(bool flag)
{
    if (d->m_fpgaGrp->video_filter() != flag) {
        d->m_fpgaGrp->enable_video_filter(flag);
        emit video_filter_changed(flag);
    }
}

DplFpga::Group::Averaging Receiver::averaging() const
{
    return d->m_fpgaGrp->averaging();
}

void Receiver::set_averaging(DplFpga::Group::Averaging type)
{
    if (d->m_fpgaGrp->averaging() != type) {
        d->m_fpgaGrp->set_averaging(type);
    }
}

}
