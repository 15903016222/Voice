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

    /* variables */
    Group::UtUnitType m_utUnitType; /* Ut Unit */
    quint32 m_velocity;             /* 声速， 单位 m/s */
    double m_angle;                 /* 声速入射角度, 单位 度 */
    QReadWriteLock m_rwlock;
};

GroupPrivate::GroupPrivate()
{
    m_utUnitType = Group::SoundPath;
    m_angle = 30;
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

Group::UtUnitType Group::ut_unit()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_utUnitType;
}

void Group::set_ut_unit(Group::UtUnitType type)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_utUnitType = type;
}

quint32 Group::velocity()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_velocity;
}

void Group::set_velocity(quint32 value)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_velocity = value;
}


}
