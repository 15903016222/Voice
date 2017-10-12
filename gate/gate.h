#ifndef __DPLGATE_GATE_H__
#define __DPLGATE_GATE_H__

#include <QObject>
#include <QColor>
#include <QSharedPointer>

namespace DplGate {

class Gate : public QObject
{
    Q_OBJECT
public:
    enum Type {
        A,
        B,
        I
    };

    explicit Gate(Type type, QObject *parent = 0);
    ~Gate();

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

private:
    Gate::Type m_type;
    float m_start;      // 起点(ns)
    float m_width;      // 宽度(ns)
    int m_height;       // 高度(%)
    bool m_visible;     // 可视标志
    QColor m_color;     // 闸门显示颜色
};

typedef QSharedPointer<Gate> GatePointer;

inline float Gate::start() const
{
    return m_start;
}

inline void Gate::set_start(float val)
{
    if (!qFuzzyCompare(val, m_start)) {
        m_start = val;
        emit start_changed(val);
    }
}

inline float Gate::width() const
{
    return m_width;
}

inline void Gate::set_width(float val)
{
    if (!qFuzzyCompare(val, m_width)) {
        m_width = val;
        emit width_changed(val);
    }
}

inline int Gate::height() const
{
    return m_height;
}

inline void Gate::set_height(int val)
{
    if (val != m_height) {
        m_height = val;
        emit height_changed(val);
    }
}

inline bool Gate::is_visible() const
{
    return m_visible;
}

inline void Gate::set_visible(bool visible)
{
    if (visible != m_visible) {
        m_visible = visible;
        emit visible_changed(visible);
    }
}

inline const QColor &Gate::color() const
{
    return m_color;
}

inline void Gate::set_color(const QColor &color)
{
    if (m_color != color) {
        m_color = color;
        emit color_changed(color);
    }
}

}
#endif // __DPLGATE_GATE_H__
