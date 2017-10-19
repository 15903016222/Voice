#ifndef __DPLGATE_GATE_H__
#define __DPLGATE_GATE_H__

#include <QObject>
#include <QColor>
#include <QSharedPointer>
#include <fpga/group.h>

namespace DplGate {

class GatePrivate;
class Gate : public QObject
{
    Q_OBJECT
public:
    explicit Gate(const DplFpga::GroupPointer &fpgaGrp, DplFpga::Group::GateType type, const QColor &color=Qt::red);
    ~Gate();

    /**
     * @brief type  获取闸门类型
     * @return      闸门类型
     */
    DplFpga::Group::GateType type() const;

    /**
     * @brief start 获取闸门起点
     * @return      起点(ns)
     */
    float start() const;

    /**
     * @brief set_start 设置闸门起点
     * @param val       值(ns)
     */
    void set_start(float val);

    /**
     * @brief width 获取闸门宽度
     * @return      宽度(ns)
     */
    float width() const;

    /**
     * @brief set_width 设置闸门宽度
     * @param val       值(ns)
     */
    void set_width(float val);

    /**
     * @brief height    获取闸门高度
     * @return          高度(%)
     */
    int height() const;

    /**
     * @brief set_height    设置闸门高度
     * @param val           值(%)
     */
    void set_height(int val);

    /**
     * @brief is_visible    获取可视状态
     * @return              可显示返回true，否则为false
     */
    bool is_visible() const;

    /**
     * @brief set_visible   设置可视状态
     * @param visible       ture为可视，false为隐藏
     */
    void set_visible(bool visible);

    /**
     * @brief color 获取闸门显示颜色
     * @return      颜色值
     */
    const QColor &color() const;

    /**
     * @brief set_color 设置闸门显示颜色
     * @param color     颜色
     */
    void set_color(const QColor &color);

    /**
     * @brief measure_mode  获取测量模式
     * @return              测量模式
     */
    DplFpga::Group::MeasureMode measure_mode() const;

    /**
     * @brief set_measure_mode  设置测量模式
     * @param mode              测量模式
     */
    void set_measure_mode(DplFpga::Group::MeasureMode mode);

    /**
     * @brief synchro_mode  获取闸门同步模式
     * @return              同步模式
     */
    DplFpga::Group::SynchroMode synchro_mode() const;

    /**
     * @brief set_synchro_mode  设置闸门同步模式
     * @param mode              同步模式
     */
    void set_synchro_mode(DplFpga::Group::SynchroMode mode);

signals:
    /**
     * @brief height_changed    高度改变信号
     * @param val               高度值(%)
     */
    void height_changed(int val);

    /**
     * @brief start_changed 起点改变信号
     * @param val           起点值(ns)
     */
    void start_changed(float val);

    /**
     * @brief width_changed 宽度改变信号
     * @param val           宽度值(ns)
     */
    void width_changed(float val);

    /**
     * @brief visible_changed   可视状态改变信号
     * @param visible           状态
     */
    void visible_changed(bool visible);

    /**
     * @brief color_changed 颜色改变信号
     * @param color         改变后的颜色
     */
    void color_changed(const QColor &color);

    /**
     * @brief measure_mode_changed  测量模式信号
     * @param mode                  测量模式
     */
    void measure_mode_changed(DplFpga::Group::MeasureMode mode);

    /**
     * @brief synchro_mode_changed  同步模式信号
     * @param mode                  同步模式
     */
    void synchro_mode_changed(DplFpga::Group::SynchroMode mode);

private:
    GatePrivate *d;
};

typedef QSharedPointer<Gate> GatePointer;

}
#endif // __DPLGATE_GATE_H__
