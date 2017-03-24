#ifndef __POINT_H__
#define __POINT_H__

#include <qmath.h>
#include <QDebug>

namespace DplFocallaw {

template <typename T>
class Point
{
public:
    Point(T x=0, T y=0, T z=0) : m_x(x), m_y(y), m_z(z) {;}

    T x() const { return m_x; }
    T y() const { return m_y; }
    T z() const { return m_z; }

    void set_x(T x) { m_x = x; }
    void set_y(T y) { m_y = y; }
    void set_z(T z) { m_z = z; }

    void set(const Point<T> &point)
    {
        m_x = point.m_x;
        m_y = point.m_y;
        m_z = point.m_z;
    }

    void set(T x) { set_x(x); }
    void set(T x, T y) { set(x); set_y(y); }
    void set(T x, T y, T z) { set(x, y); set_z(z); }

    T distance(const Point<T> &p) const { return qSqrt(qPow(m_x-p.x(), 2) + qPow(m_y-p.y(), 2) + qPow(m_z-p.z(), 2)); }

    void show(const char *msg = 0) const { qDebug("%s: (%g, %g, %g)", msg, m_x, m_y, m_z); }

private:
    T m_x;
    T m_y;
    T m_z;
};

}
#endif // __POINT_H__
