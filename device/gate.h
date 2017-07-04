#ifndef __GATE_H__
#define __GATE_H__

#include <QObject>
#include <QSharedPointer>

namespace DplDevice {

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

signals:
    /**
     * @brief height_changed    高度改变信号
     * @param val               高度值(%)
     */
    void height_changed(int val);

public slots:

private:
    Gate::Type m_type;
    float m_start;      // 起点(ns)
    float m_width;      // 宽度(ns)
    int m_height;       // 高度(%)
};

typedef QSharedPointer<Gate> GatePointer;

inline float Gate::start() const
{
    return m_start;
}

inline void Gate::set_start(float val)
{
    m_start = val;
}

inline float Gate::width() const
{
    return m_width;
}

inline void Gate::set_width(float val)
{
    m_width = val;
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

}
#endif // __GATE_H__
