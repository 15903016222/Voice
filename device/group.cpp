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
#include <source/source.h>

#include <QReadWriteLock>
#include <qmath.h>
#include <QDebug>

namespace DplDevice {

class GroupPrivate
{
public:
    GroupPrivate();

    /**
     * @brief max_beam_delay    获取最大的BeamDelay
     * @return                  BeamDelay值，　单位(ns)
     */
    int max_beam_delay();

    /* variables */
    Group::Mode m_mode;         /* 组模式 */
    float m_precision;          /* 采样精度， 单位(ns) */
    double m_start;             /* 声程轴起始点,单位(ns) */
    double m_range;             /* 范围值, 单位(ns) */
    Group::UtUnit m_utUnit;     /* Ut Unit */

    double m_velocity;          /* 声速， 单位(m/s) */
    double m_currentAngle;      /* 声速入射角度, 单位(度) */

    Group::PointQtyMode m_pointQtyMode; /* 采样点模式 */

    QReadWriteLock m_rwlock;
};

GroupPrivate::GroupPrivate()
{
    m_precision = DplFpga::Fpga::get_instance()->sample_precision();

    m_mode = Group::PA;

    m_start = 0;
    m_range = 5702 * m_precision;
    m_utUnit = Group::SoundPath;
    m_velocity = 3240;
    m_currentAngle = M_PI/6;

    m_pointQtyMode = Group::PointQtyAuto;
}

int GroupPrivate::max_beam_delay()
{
    qDebug()<<__FILE__<<__func__<<"Unimplement";
    return 0;
}

/* Group */
Group::Group(int index) :
    DplFpga::Group(index),
    d(new GroupPrivate()),
    m_probePtr(new DplProbe::Probe()),
    m_wedgePtr(new DplProbe::Wedge())
{
    connect(static_cast<DplProbe::Wedge *>(m_wedgePtr.data()),
            SIGNAL(delay_changed(int)),
            this,
            SLOT(update_sample()));
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

double Group::start()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_start;
}

void Group::set_start(double value)
{
    {
        QWriteLocker l(&d->m_rwlock);
        if (value == d->m_start) {
            return;
        }
        d->m_start = value;

        update_sample();
    }
    emit start_changed(value);
}

double Group::range()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_range;
}

void Group::set_range(double value)
{
    {
        QWriteLocker l(&d->m_rwlock);

        int maxPointQty = value / d->m_precision;
        int curPointQty = point_qty();
        int widthPointQty = 640;

        if (PointQtyAuto == d->m_pointQtyMode) {
            if (maxPointQty <= widthPointQty) {
                curPointQty = maxPointQty;
            } else {
                int compressRate = maxPointQty / widthPointQty;
                if (maxPointQty%widthPointQty) {
                    ++compressRate;
                }
                curPointQty = maxPointQty / compressRate;
            }
        }

        if (maxPointQty%curPointQty) {
            /* 类似四舍五入 */
            maxPointQty = ((maxPointQty + curPointQty/2)/curPointQty)*curPointQty;
        }

        //    if (d->m_range == maxPointQty * d->m_precision) {
        //        return false;
        //    }

        d->m_range = maxPointQty * d->m_precision;

        set_point_qty(curPointQty);

        if (maxPointQty/curPointQty) {
            set_compress_ratio(maxPointQty/curPointQty);
        } else {
            set_compress_ratio(1);
        }
        update_sample();
    }
    emit range_changed(d->m_range);
}

double Group::velocity()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_velocity;
}

void Group::set_velocity(double value)
{
    {
        QWriteLocker l(&d->m_rwlock);
        if (d->m_velocity == value) {
            return;
        }
        d->m_velocity = value;
    }
    emit velocity_changed(value);
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

Group::PointQtyMode Group::point_qty_mode()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_pointQtyMode;
}

bool Group::set_point_qty_mode(Group::PointQtyMode mode)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_pointQtyMode = mode;
    return true;
}

int Group::beam_qty()
{
    qDebug()<<__FILE__<<__func__<<"unimplement";
    return 1;
}

double Group::max_sample_time()
{
    DplFpga::Fpga *fpga = DplFpga::Fpga::get_instance();
    int beamQty = Device::get_instance()->beam_qty();
    // prf为1即(1s)时，rx_time时间为最大
    // 1_000_000_000 / 4    idle_time + rx_time >= 4 * rx_time
    // one beam cycle = loading time +  beam delay + wedge delay + sample start + sample range + 50 /* 单位 ns */
    int beamCycle =  (250*1000*1000) / beamQty;
    double max = beamCycle
            - fpga->loading_time() * d->m_precision
            - d->max_beam_delay()
            - m_wedgePtr->delay()
            - 50;
    if(max > 1000*1000) {
        max = 1000*1000;
    }
    return max ;
}

void Group::update_sample()
{
    set_sample_start((m_wedgePtr->delay() + d->m_start)/d->m_precision, true);
    set_sample_range((m_wedgePtr->delay() + d->m_start + d->m_range)/d->m_precision, true);
    set_rx_time((d->max_beam_delay() + m_wedgePtr->delay() + d->m_start + d->m_range + 50)/d->m_precision, true);
}

}
