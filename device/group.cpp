/**
 * @file group_config.cpp
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include "group_p.h"

#include "device.h"

#include <global.h>
#include <ut/global_pulser.h>
#include <fpga/fpga.h>

#include <QReadWriteLock>
#include <qmath.h>
#include <QDebug>

namespace DplDevice {

/* Group */
Group::Group(int index, QObject *parent) : QObject(parent),
    m_fpgaGroup(new DplFpga::Group(index)),
    m_focallawer(new DplFocallaw::Focallawer),
    m_sample(new DplUt::Sample(m_fpgaGroup)),
    m_pulser(new DplUt::Pulser(m_sample, m_focallawer)),
    m_receiver(new DplUt::Receiver(m_fpgaGroup)),
    m_gateA(new DplGate::Gate(m_fpgaGroup, DplFpga::Group::GATE_A)),
    m_gateB(new DplGate::Gate(m_fpgaGroup, DplFpga::Group::GATE_B, Qt::green)),
    m_gateI(new DplGate::Gate(m_fpgaGroup, DplFpga::Group::GATE_I, Qt::darkCyan)),
    d(new GroupPrivate(this))
{
    init_gates();

    init_sample();
    init_pulser();

    init_source();

    DplUt::GlobalPulser::instance()->connect_group(this);
}

Group::~Group()
{
    delete d;
}

Group::Mode Group::mode()
{
    return d->mode();
}

void Group::set_mode(Group::Mode mode)
{
    d->set_mode(mode);
}

Group::UtUnit Group::ut_unit()
{
    return d->ut_unit();
}

void Group::set_ut_unit(Group::UtUnit type)
{
    d->set_ut_unit(type);
}

double Group::current_angle()
{
    return d->current_angle();
}

void Group::set_current_angle(double angle)
{
    d->set_current_angle(angle);
}

double Group::max_sample_time()
{
    // prf为1即(1s)时，rx_time时间为最大
    // 1s/4,   idle_time + rx_time >= 4 * rx_time
    // one beam cycle = loading time + rx_time  + idle + 50, 单位ns
    // rx time = beam delay + wedge delay + sample start + sample range
    float rxTime =  (Dpl::s_to_ns(1.0)/4) / Device::instance()->beam_qty();
    double max = rxTime
            - DplFpga::Fpga::LOADING_TIME * DplFpga::Fpga::SAMPLE_PRECISION
            - m_focallawer->max_beam_delay()
            - m_focallawer->wedge()->delay()
            - 50;
    if(max > Dpl::ms_to_ns(1)) {
        max = Dpl::ms_to_ns(1);
    }
    return max ;
}

const DplGate::GatePointer &Group::gate(DplFpga::Group::GateType type) const
{
    if (type == DplFpga::Group::GATE_A) {
        return m_gateA;
    } else if (type == DplFpga::Group::GATE_B) {
        return m_gateB;
    } else {
        return m_gateI;
    }
}

const DplSource::BeamsPointer &Group::current_beams() const
{
    return d->beams();
}

const DplSource::BeamPointer &Group::current_beam() const
{
    return d->beam();
}

void Group::deploy_beams() const
{
    DplFpga::Beam fpgaBeam;
    int startRxChannel = 0;
    int startTxChannel = 0;
    int aperture = 0;
    int beamIndex = Device::instance()->first_beam_index(this);

//    DplFpga::Fpga::instance()->show_info();
//    m_fpgaGroup->show_info();

    fpgaBeam.set_total_beam_qty( Device::instance()->beam_qty() );
    fpgaBeam.set_group_id(index());
    fpgaBeam.set_gain_compensation(0);

    foreach (DplFocallaw::BeamPointer focallawerBeam, m_focallawer->beams()) {
        fpgaBeam.set_index(beamIndex++);
//            fpgaBeam.set_delay(focallawerBeams[j]->delay()/DplFpga::Fpga::SAMPLE_PRECISION);
        fpgaBeam.set_delay(0);
        fpgaBeam.set_gate_a(m_gateA->start() / DplFpga::Fpga::SAMPLE_PRECISION,
                            m_gateA->width() / DplFpga::Fpga::SAMPLE_PRECISION);
        fpgaBeam.set_gate_b(m_gateB->start() / DplFpga::Fpga::SAMPLE_PRECISION,
                            m_gateB->width() / DplFpga::Fpga::SAMPLE_PRECISION);
        fpgaBeam.set_gate_i(m_gateI->start() / DplFpga::Fpga::SAMPLE_PRECISION,
                            m_gateI->width() / DplFpga::Fpga::SAMPLE_PRECISION);

        startRxChannel = m_focallawer->probe()->pulser_index() + focallawerBeam->first_rx_element();
        startTxChannel = m_focallawer->probe()->receiver_index() + focallawerBeam->first_tx_element();

        aperture = focallawerBeam->aperture();

        fpgaBeam.set_tx_channel(startTxChannel, aperture);
        fpgaBeam.set_rx_channel(startRxChannel, aperture);

        for (int i = 0; i < aperture; ++i) {
            fpgaBeam.set_rx_delay(startRxChannel+i, focallawerBeam->rxdelay().at(i));
            fpgaBeam.set_tx_delay(startTxChannel+i, focallawerBeam->txdelay().at(i));
//            qDebug("%s[%d]: %d - delay(%d)",__func__, __LINE__, i, focallawerBeam->rxdelay().at(i));
//                fpgaBeam.set_rx_delay(startRxChannel+k, 0);
//                fpgaBeam.set_tx_delay(startTxChannel+k, 0);
//                qDebug("%s[%d]: enablet(0x%x) rx(%f) tx(%f)",__func__, __LINE__, (startRxChannel+i)&0x1f, focallawerBeamPtr->rxdelay().at(k), focallawerBeamPtr->txdelay().at(k));
        }

//        fpgaBeam.show_info();
        fpgaBeam.refresh();
    }
}

void Group::update_sample()
{
    m_fpgaGroup->set_sample_start((m_focallawer->wedge()->delay() + m_sample->start())/DplFpga::Fpga::SAMPLE_PRECISION);
    m_fpgaGroup->set_sample_range((m_focallawer->wedge()->delay() + m_sample->start() + m_sample->range())/DplFpga::Fpga::SAMPLE_PRECISION);
}

void Group::update_pulser()
{
    m_fpgaGroup->set_rx_time((m_pulser->txrx_time() + 50)/DplFpga::Fpga::SAMPLE_PRECISION);
    m_fpgaGroup->set_idle_time((DplUt::GlobalPulser::instance()->beam_cycle() - m_pulser->txrx_time())/DplFpga::Fpga::SAMPLE_PRECISION);
}

void Group::update_source()
{
    DplSource::Source::instance()->edit_group(m_fpgaGroup->index(),
                                              m_focallawer->beam_qty(),
                                              m_sample->point_qty());
}

void Group::init_gate(DplGate::Gate *gate)
{
    connect(gate, SIGNAL(start_changed(float)),
            this, SLOT(deploy_beams()));
    connect(gate, SIGNAL(width_changed(float)),
            this, SLOT(deploy_beams()));
}

void Group::init_gates()
{
    init_gate(m_gateA.data());
    init_gate(m_gateB.data());
    init_gate(m_gateI.data());
}

void Group::init_sample()
{
    DplUt::Sample *sample = m_sample.data();
    /* 关联FPGA */            
    m_fpgaGroup->set_point_qty(m_sample->point_qty());
    connect(sample,
            SIGNAL(point_qty_changed(int)),
            static_cast<DplFpga::Group *>(m_fpgaGroup.data()),
            SLOT(set_point_qty(int)));

    /* 关联Group */
    connect(sample,
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_sample()));

    connect(sample,
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_sample()));

    /* 关联Beams */
    connect(sample,
            SIGNAL(point_qty_changed(int)),
            this,
            SLOT(update_source()));

    /* Wedge */
    connect(static_cast<DplFocallaw::Wedge *>(m_focallawer->wedge().data()),
            SIGNAL(delay_changed(int)),
            this,
            SLOT(update_sample()));

    update_sample();
}

void Group::init_pulser()
{
    connect(static_cast<DplUt::Pulser *>(m_pulser.data()),
            SIGNAL(txrx_time_changed()),
            this,
            SLOT(update_pulser()));

    connect(DplUt::GlobalPulser::instance(),
            SIGNAL(prf_changed()),
            this,
            SLOT(update_pulser()));
}

void Group::init_source()
{
    DplSource::Source *source = DplSource::Source::instance();
    source->register_group(index(), m_focallawer->beam_qty(), m_sample->point_qty());
    connect(source, SIGNAL(data_event()),
            d, SLOT(do_source_data_event()),
            Qt::DirectConnection);

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(beam_qty_changed(int)),
            this, SLOT(update_source()));
}

}
