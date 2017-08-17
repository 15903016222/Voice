/**
 * @file group_config.h
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#ifndef __DEVICE_GROUP_H__
#define __DEVICE_GROUP_H__

#include <fpga/group.h>
#include <focallaw/focallawer.h>
#include <ut/sample.h>
#include <gate/gate.h>
#include <source/beams.h>

namespace DplDevice {

class GroupPrivate;

class Group : public QObject
{
    Q_OBJECT
    friend class GroupPrivate;
public:
    explicit Group(int index, QObject *parent = 0);
    ~Group();

    int index() const;

    enum Mode {
        UT,
        PA,
        UT1,
        UT2
    };
    /**
     * @brief mode  获取组模式
     * @return      组模式
     */
    Mode mode();

    /**
     * @brief set_mode  设置组模式
     * @param mode      组模式
     */
    void set_mode(Mode mode);

    enum UtUnit {
        Time,           // 时间
        SoundPath,      // 声程
        TruePath        // 真实深度
    };

    /**
     * @brief ut_unit   获取显示类型
     * @return          显示类型
     */
    UtUnit ut_unit();

    /**
     * @brief set_ut_unit   设置显示类型
     * @param type          显示类型
     */
    void set_ut_unit(UtUnit type);

    /**
     * @brief current_angle 获取当前入射角度
     * @return              角度值，单位(MI_P)
     */
    double current_angle();

    /**
     * @brief set_current_angle 设置当前入射角度
     * @param angle             角度，单位(MI_P)
     */
    void set_current_angle(double angle);

    /**
     * @brief max_sample_time   获取最大Start+Range时间
     * @return              返回最大Start+Range时间，单位(ns)
     */
    double max_sample_time();

    /**
     * @brief max_start 获取最大的start时间
     * @return          时间，单位(ns)
     */
    double max_start();

    /**
     * @brief max_range 获取最大的range时间
     * @return          时间，单位(ns)
     */
    double max_range();

    /**
     * @brief sample    获取采样对象指针
     * @return          对象指针
     */
    const DplUt::SamplePointer &sample() const;

    /**
     * @brief gate  获取闸门对象指针
     * @param type  闸门类型
     * @return      闸门对象指针
     */
    const DplGate::GatePointer &gate(DplGate::Gate::Type type) const;

    /**
     * @brief current_beams 获取数据源当前Beam组
     * @return              返回数据源Beam组
     */
    DplSource::BeamsPointer current_beams() const;

    /**
     * @brief current_beam  获取数据源的当前Beam
     * @return              Beam
     */
    DplSource::BeamPointer current_beam() const;

    /**
     * @brief get_focallawer    获取聚焦法则计算器
     * @return                  聚焦法则计算器
     */
    const DplFocallaw::FocallawerPointer &focallawer() const;

signals:
    void mode_changed(DplDevice::Group::Mode mode);
    void velocity_changed(double val);
    void ut_unit_changed(DplDevice::Group::UtUnit type);
    void current_angle_changed(double val);
    void probe_changed(DplFocallaw::ProbePointer probePtr);

public slots:
    /**
     * @brief deploy_beams  下发组Beams的配置信息
     */
    void deploy_beams() const;

private slots:
    void update_sample();
    void update_source();

private:
    DplUt::SamplePointer m_sample;
    DplGate::GatePointer m_gateA;
    DplGate::GatePointer m_gateB;
    DplGate::GatePointer m_gateI;
    DplFocallaw::FocallawerPointer m_focallawer; // 聚焦法则计算器
    DplFpga::GroupPointer m_fpgaGroup;
    GroupPrivate *d;

private:
    void init_gate(DplGate::Gate *gate);
    void init_gates();
    void init_sample();
};

typedef QSharedPointer<Group> GroupPointer;

inline int Group::index() const
{
    return m_fpgaGroup->index();
}

inline double Group::max_start()
{
    return max_sample_time() - m_sample->range();
}

inline double Group::max_range()
{
    return max_sample_time() - m_sample->start();
}

inline const DplUt::SamplePointer &Group::sample() const
{
    return m_sample;
}

inline const DplGate::GatePointer &Group::gate(DplGate::Gate::Type type) const
{
    if (type == DplGate::Gate::A) {
        return m_gateA;
    } else if (type == DplGate::Gate::B) {
        return m_gateB;
    } else {
        return m_gateI;
    }
}

inline const DplFocallaw::FocallawerPointer &Group::focallawer() const
{
    return m_focallawer;
}

}
#endif // __DEVICE_GROUP_H__
