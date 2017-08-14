#ifndef __GROUP_P_H__
#define __GROUP_P_H__

#include "group.h"

namespace DplDevice {

class GroupPrivate : public QObject
{
    Q_OBJECT
public:
    explicit GroupPrivate(Group *parent);

    Group::Mode mode() const;

    void set_mode(Group::Mode mode);

    Group::UtUnit ut_unit() const;

    void set_ut_unit(Group::UtUnit unit);

    double current_angle() const;

    void set_current_angle(double angle);

    /**
     * @brief max_beam_delay    获取最大的Beam延迟时间
     * @return                  延迟时间(ns)
     */
    int max_beam_delay();

private:
    Group *q_ptr;
    Group::Mode m_mode;         // 组模式
    Group::UtUnit m_utUnit;     // Ut 显示单位
    double m_currentAngle;      // 声速射角度(度)
};

inline Group::Mode GroupPrivate::mode() const
{
    return m_mode;
}

inline void GroupPrivate::set_mode(Group::Mode mode)
{
    if (m_mode != mode) {
        m_mode = mode;
        emit q_ptr->mode_changed(mode);
    }
}

inline Group::UtUnit GroupPrivate::ut_unit() const
{
    return m_utUnit;
}

inline void GroupPrivate::set_ut_unit(Group::UtUnit unit)
{
    if (m_utUnit != unit) {
        m_utUnit = unit;
        emit q_ptr->ut_unit_changed(unit);
    }
}

inline double GroupPrivate::current_angle() const
{
    return m_currentAngle;
}

inline void GroupPrivate::set_current_angle(double angle)
{
    if (!qFuzzyCompare(m_currentAngle, angle)) {
        m_currentAngle = angle;
        emit q_ptr->current_angle_changed(angle);
    }
}

inline int GroupPrivate::max_beam_delay()
{
    qDebug()<<__FILE__<<__func__<<"Unimplement";
    return 0;
}

}
#endif // __GROUP_P_H__
