/**
 * @file group_config.cpp
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include "group.h"
#include "device.h"

#include <QReadWriteLock>

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
    int m_start;                /* 声程轴起始点,单位(ns) */
    int m_range;                /* 范围值, 单位(ns) */
    int m_wedgeDelay;           /* 楔块延迟时间，单位(ns) */
    Group::UtUnit m_utUnit;     /* Ut Unit */

    double m_velocity;          /* 声速， 单位(m/s) */
    double m_currentAngle;      /* 声速入射角度, 单位(度) */

    Group::PointQtyMode m_pointQtyMode; /* 采样点模式 */

    QReadWriteLock m_rwlock;
};

GroupPrivate::GroupPrivate()
{
    m_utUnit = Group::SoundPath;
    m_currentAngle = 30;
}

int GroupPrivate::max_beam_delay()
{
    qDebug()<<__FILE__<<__func__<<"Unimplement";
    return 0;
}

/* Group */
Group::Group(int index) :
    DplFpga::Group(index),
    d(new GroupPrivate())
{

}

Group::~Group()
{
    delete d;
}

Group::UtUnit Group::ut_unit()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_utUnit;
}

void Group::set_ut_unit(Group::UtUnit type)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_utUnit = type;
}

int Group::start()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_start;
}

void Group::set_start(int value)
{
    QWriteLocker l(&d->m_rwlock);
    if (value == d->m_start) {
        return;
    }
    d->m_start = value;

    update_sample();
}

int Group::range()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_range;
}

void Group::set_range(int value)
{
    QWriteLocker l(&d->m_rwlock);
    int range = value;
    int pointQty = point_qty();

    if (PointQtyAuto == d->m_pointQtyMode) {
        if (range <= 6400) {
            pointQty = range;
        } else {
            int compressRate = range / 6400 ;
            if (range%6400) {
                ++compressRate;
            }
            pointQty = range / compressRate;
        }
    }

    range = ((range + pointQty/2)/pointQty)*pointQty;

    if (range == d->m_range) {
        return;
    }
    d->m_range = range;

    set_point_qty(pointQty);
    if (d->m_range/pointQty) {
        set_compress_rato(d->m_range/pointQty, true);
    } else {
        set_compress_rato(1, true);
    }
    update_sample();
}

double Group::velocity()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_velocity;
}

void Group::set_velocity(double value)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_velocity = value;
}

int Group::wedge_delay()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_wedgeDelay;
}

void Group::set_wedge_delay(int value)
{
    QWriteLocker l(&d->m_rwlock);
    if (d->m_wedgeDelay == value) {
        return;
    }
    d->m_wedgeDelay = value;
    update_sample();
}

double Group::current_angle()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_currentAngle;
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
}

int Group::beam_qty()
{
    qDebug()<<__FILE__<<__func__<<"unimplement";
    return 1;
}

int Group::max_rx_time()
{
    int beamQty = Device::get_instance()->beam_qty();
    int maxDelay = d->max_beam_delay();
    int ret;
    // 1_000_000_000 / 4    idle_time + rx_time >= 4 * rx_time
    // one beam cycle = 20480(loading time) +  beam delay + wedge delay + sample start + sample range + 50
    ret =  (250*1000*1000) / beamQty - 20480  - maxDelay - wedge_delay() - 50;
    if(ret > 1000*1000) {
        ret = 1000*1000;
    }
    return ret ;
}

void Group::update_sample()
{
    set_sample_start(d->m_wedgeDelay + d->m_start, true);
    set_sample_range(d->m_wedgeDelay + d->m_start + d->m_range, true);
    set_rx_time(d->max_beam_delay() + d->m_wedgeDelay + d->m_start + d->m_range + 50, true);
}

}
