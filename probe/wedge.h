#ifndef __WEDGE_H__
#define __WEDGE_H__

#include <QObject>
#include <QSharedPointer>

#include <QDebug>

namespace DplProbe {

class Wedge;
typedef QSharedPointer<Wedge> WedgePointer;

class Wedge : public QObject
{
    Q_OBJECT
public:
    explicit Wedge(QObject *parent=0);
    ~Wedge();

    /**
     * @brief delay 楔块延迟时间
     * @return      返回楔块延迟时间，单位(ns)
     */
    int delay() const;

    /**
     * @brief set_delay 设置楔块延迟时间
     * @param value     延迟时间，单位(ns)
     */
    void set_delay(int value);

signals:
    void delay_changed(int value);

private:
    int m_delay;        /* 延迟时间，单位(ns) */

};

inline int Wedge::delay() const
{
    return m_delay;
}

inline void Wedge::set_delay(int value)
{
    if (m_delay != value) {
        m_delay = value;
        emit delay_changed(value);
    }
}

}

#endif // __WEDGE_H__
