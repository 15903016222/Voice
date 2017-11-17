#ifndef __GROUP_P_H__
#define __GROUP_P_H__

#include "group.h"

#include "source/source.h"

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

    const DplSource::BeamsPointer &beams() const;

    const DplSource::BeamPointer &beam() const;

    void set_current_beam_index(int index);

    int current_beam_index() const;

protected slots:
    void do_source_data_event();

private:
    Group *q;
    Group::Mode m_mode;             // 组模式
    Group::UtUnit m_utUnit;         // Ut 显示单位
    double m_currentAngle;          // 声速射角度(度)
    DplSource::Source *m_source;    // 数据源
    DplSource::BeamsPointer m_beams;
    DplSource::BeamPointer m_beam;
    int m_index;                    // 当前beam号
};

inline Group::Mode GroupPrivate::mode() const
{
    return m_mode;
}

inline void GroupPrivate::set_mode(Group::Mode mode)
{
    if (m_mode != mode) {
        m_mode = mode;
        emit q->mode_changed(mode);
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
        emit q->ut_unit_changed(unit);
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
        emit q->current_angle_changed(angle);
    }
}

inline const DplSource::BeamsPointer &GroupPrivate::beams() const
{
    return m_beams;
}

inline const DplSource::BeamPointer &GroupPrivate::beam() const
{
    return m_beam;
}

inline void GroupPrivate::set_current_beam_index(int index)
{
    m_index = index;
}

inline int GroupPrivate::current_beam_index() const
{
    return m_index;
}

}
#endif // __GROUP_P_H__
