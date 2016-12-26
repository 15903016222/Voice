/**
 * @file group_config.cpp
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include "group.h"

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

    QReadWriteLock m_rwlock;
};

GroupPrivate::GroupPrivate()
{
    m_utUnit = Group::SoundPath;
    m_currentAngle = 30;
}

int GroupPrivate::max_beam_delay()
{
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

    set_sample_start(d->m_wedgeDelay + d->m_start, true);
    set_sample_range(d->m_wedgeDelay + d->m_start + d->m_range, true);
    set_rx_time(d->max_beam_delay() + d->m_wedgeDelay + d->m_start + d->m_range + 50, true);
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

    set_sample_start(d->m_wedgeDelay + d->m_start, true);
    set_sample_range(d->m_wedgeDelay + d->m_start + d->m_range, true);
    set_rx_time(d->max_beam_delay() + d->m_wedgeDelay + d->m_start + d->m_range + 50, true);
}

double Group::current_angle()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_currentAngle;
}

}
