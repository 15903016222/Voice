/**
 * @file transceiver.cpp
 * @brief 收发器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-28
 */
#include "transceiver.h"
#include "global_transceiver.h"
#include <fpga/fpga.h>

namespace DplUt {

class TransceiverPrivate
{
public:
    TransceiverPrivate(const DplFpga::GroupPointer &fpgaGrp) :
        m_mode(Transceiver::PE),
        m_pw(100),
        m_probeFreq(0),
        m_fpgaGrp(fpgaGrp)
    {}

public slots:
    /* attributions */
    Transceiver::Mode m_mode;
    float m_pw;
    int m_probeFreq;
    DplFpga::GroupPointer m_fpgaGrp;
};

Transceiver::Transceiver(const DplFpga::GroupPointer &fpgaGrp) : QObject(),
    d(new TransceiverPrivate(fpgaGrp))
{
    connect(static_cast<DplFpga::Group *>(fpgaGrp.data()),
            SIGNAL(work_time_changed()),
            this,
            SIGNAL(work_time_changed()));
}

Transceiver::~Transceiver()
{
    delete d;
}

Transceiver::Mode Transceiver::mode() const
{
    return d->m_mode;
}

void Transceiver::set_mode(Transceiver::Mode mode)
{
    if (d->m_mode == mode) {
        return;
    }

    if (d->m_mode == TOFD) {
        set_rectifier(DplFpga::Group::FULL_WAVE);
    }

    d->m_mode = mode;

    if (d->m_mode == PE) {
        if ( d->m_fpgaGrp->mode() == DplFpga::Group::UT1 ) {
            DplFpga::Fpga::instance()->set_ut1_twin(false);
        } else if ( d->m_fpgaGrp->mode() == DplFpga::Group::UT2 ) {
            DplFpga::Fpga::instance()->set_ut2_twin(false);
        }
    } else {
        if (d->m_mode == TOFD) {
            set_video_filter(false);
        }
        if (d->m_fpgaGrp->mode() == DplFpga::Group::UT1) {
            DplFpga::Fpga::instance()->set_ut1_twin(true);
        } else if (d->m_fpgaGrp->mode() == DplFpga::Group::UT2) {
            DplFpga::Fpga::instance()->set_ut2_twin(true);
        }
    }

    emit mode_changed(d->m_mode);

}

float Transceiver::pw() const
{
    return d->m_pw;
}

void Transceiver::set_pw(float w)
{
    if (qFuzzyIsNull(d->m_pw - w)) {
        return;
    }
    d->m_pw = w;
    d->m_fpgaGrp->set_tx_end(w/2.5, true);
    emit pw_changed(w);
}

int Transceiver::filter() const
{
    return d->m_probeFreq;
}

void Transceiver::set_filter(int freq)
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

DplFpga::Group::Rectifier Transceiver::rectifier() const
{
    return d->m_fpgaGrp->rectifier();
}

void Transceiver::set_rectifier(DplFpga::Group::Rectifier val)
{
    if ( d->m_fpgaGrp->rectifier() != val) {
        d->m_fpgaGrp->set_rectifier(val);
        emit recitifier_changed(val);
    }
}

bool Transceiver::video_filter() const
{
    return d->m_fpgaGrp->video_filter();
}

void Transceiver::set_video_filter(bool flag)
{
    if (d->m_fpgaGrp->video_filter() != flag) {
        d->m_fpgaGrp->enable_video_filter(flag);
        emit video_filter_changed(flag);
    }
}

DplFpga::Group::Averaging Transceiver::averaging() const
{
    return d->m_fpgaGrp->averaging();
}

void Transceiver::set_averaging(DplFpga::Group::Averaging type)
{
    if (d->m_fpgaGrp->averaging() != type) {
        d->m_fpgaGrp->set_averaging(type);
    }
}

int Transceiver::work_time() const
{
    return d->m_fpgaGrp->work_time();
}

}
