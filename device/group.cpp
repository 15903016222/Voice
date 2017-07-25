/**
 * @file group_config.cpp
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include "group.h"
#include "device.h"

#include <fpga/fpga.h>

#include <QReadWriteLock>
#include <qmath.h>
#include <QDebug>

namespace DplDevice {

class GroupPrivate
{
public:
    GroupPrivate() :
        m_mode(Group::PA),
        m_utUnit(Group::SoundPath),
        m_currentAngle(M_PI/6)
    {}

    /**
     * @brief max_beam_delay    获取最大的BeamDelay
     * @return                  BeamDelay值，　单位(ns)
     */
    int max_beam_delay();

    /* Attribution */
    Group::Mode m_mode;         /* 组模式 */
    Group::UtUnit m_utUnit;     /* Ut Unit */

    double m_currentAngle;      /* 声速入射角度, 单位(度) */

    QReadWriteLock m_rwlock;
};

int GroupPrivate::max_beam_delay()
{
    qDebug()<<__FILE__<<__func__<<"Unimplement";
    return 0;
}

/* Group */
Group::Group(int index, QObject *parent):
    QObject(parent),
    d(new GroupPrivate()),
    m_sample(new DplUt::Sample(DplFpga::Fpga::SAMPLE_PRECISION, parent)),
    m_gateA(new DplGate::Gate(DplGate::Gate::A, parent)),
    m_gateB(new DplGate::Gate(DplGate::Gate::B, parent)),
    m_gateI(new DplGate::Gate(DplGate::Gate::I, parent)),
    m_beams(new DplSource::Beams),
    m_focallawer(new DplFocallaw::Focallawer),
    m_fpgaGroup(new DplFpga::Group(index, parent))
{
    DplFpga::Group *fpgaGroup = static_cast<DplFpga::Group *>(m_fpgaGroup.data());
//    m_fpgaGroup->show_info();

    /* 关联闸门 */
    connect(static_cast<DplGate::Gate *>(m_gateA.data()),
            SIGNAL(height_changed(int)),
            fpgaGroup, SLOT(set_gate_a_height(int)));
    connect(static_cast<DplGate::Gate *>(m_gateB.data()),
            SIGNAL(height_changed(int)),
            fpgaGroup, SLOT(set_gate_b_height(int)));
    connect(static_cast<DplGate::Gate *>(m_gateI.data()),
            SIGNAL(height_changed(int)),
            fpgaGroup, SLOT(set_gate_i_height(int)));

    init_sample();

    m_beams->set_beam_qty(m_focallawer->beam_qty());
    m_beams->set_point_qty(m_sample->point_qty());

    connect(static_cast<DplFocallaw::Wedge *>(m_focallawer->wedge().data()),
            SIGNAL(delay_changed(int)),
            this, SLOT(update_sample()));

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(beam_qty_changed(int)),
            static_cast<DplSource::Beams *>(m_beams.data()),
            SLOT(set_beam_qty(int)));

    update_sample();
}

Group::~Group()
{
    delete d;
}

Group::Mode Group::mode()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_mode;
}

void Group::set_mode(Group::Mode mode)
{
    {
        QWriteLocker l(&d->m_rwlock);
        if (d->m_mode == mode) {
            return;
        }
        d->m_mode = mode;
    }
    emit mode_changed(mode);
}

Group::UtUnit Group::ut_unit()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_utUnit;
}

void Group::set_ut_unit(Group::UtUnit type)
{
    {
        QWriteLocker l(&d->m_rwlock);
        if (d->m_utUnit == type) {
            return;
        }
        d->m_utUnit = type;
    }
    emit ut_unit_changed(type);
}

double Group::current_angle()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_currentAngle;
}

void Group::set_current_angle(double angle)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_currentAngle = angle;
}

double Group::max_sample_time()
{
    int beamQty = Device::instance()->total_beam_qty();
    // prf为1即(1s)时，rx_time时间为最大
    // 1_000_000_000 / 4    idle_time + rx_time >= 4 * rx_time
    // one beam cycle = loading time +  beam delay + wedge delay + sample start + sample range + 50 /* 单位 ns */
    int beamCycle =  (250*1000*1000) / beamQty;
    double max = beamCycle
            - DplFpga::Fpga::LOADING_TIME * DplFpga::Fpga::SAMPLE_PRECISION
            - d->max_beam_delay()
            - m_focallawer->wedge()->delay()
            - 50;
    if(max > 1000*1000) {
        max = 1000*1000;
    }
    return max ;
}

void Group::update_sample()
{
    m_fpgaGroup->set_sample_start((m_focallawer->wedge()->delay() + m_sample->start())/DplFpga::Fpga::SAMPLE_PRECISION);
    m_fpgaGroup->set_sample_range((m_focallawer->wedge()->delay() + m_sample->start() + m_sample->range())/DplFpga::Fpga::SAMPLE_PRECISION);
    m_fpgaGroup->set_rx_time((d->max_beam_delay() + m_focallawer->wedge()->delay() + m_sample->start() + m_sample->range() + 50)/DplFpga::Fpga::SAMPLE_PRECISION);

    //    m_fpgaGroup->show_info();
}

void Group::init_sample()
{
    DplUt::Sample *sample = m_sample.data();
    /* 关联FPGA */
    m_fpgaGroup->set_gain(m_sample->gain());
    connect(sample,
            SIGNAL(gain_changed(float)),
            static_cast<DplFpga::Group *>(m_fpgaGroup.data()),
            SLOT(set_gain(float)));

    m_fpgaGroup->set_scale_factor(m_sample->scale_factor());
    connect(sample,
            SIGNAL(scale_factor_changed(int)),
            static_cast<DplFpga::Group *>(m_fpgaGroup.data()),
            SLOT(set_scale_factor(int)));

    m_fpgaGroup->set_point_qty(m_sample->point_qty());
    connect(sample,
            SIGNAL(point_qty_changed(int)),
            static_cast<DplFpga::Group *>(m_fpgaGroup.data()),
            SLOT(set_point_qty(int)));

    /* 关联自己 */
    connect(sample,
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_sample()));

    connect(sample,
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_sample()));

    /* 关联Beams */
    m_beams->set_point_qty(m_sample->point_qty());
    connect(sample,
            SIGNAL(point_qty_changed(int)),
            static_cast<DplSource::Beams *>(m_beams.data()),
            SLOT(set_point_qty(int)));
}

}
