#ifndef __S_SCAN_H__
#define __S_SCAN_H__

#include <QObject>
#include <focallaw/focallawer.h>
#include <ut/sample.h>

namespace DplDisplay {

class Sscan : public QObject
{
    Q_OBJECT
public:
    explicit Sscan(const DplFocallaw::FocallawerPointer &focallawer,
                   const DplUt::SamplePointer &sample);

    /**
     * @brief start_x   X轴开始值
     * @return          值(ns)
     */
    float start_x() const;

    /**
     * @brief stop_x    X轴结束值
     * @return          值(ns)
     */
    float stop_x() const;

    /**
     * @brief start_y   Y轴开始值
     * @return          值(ns)
     */
    float start_y() const;

    /**
     * @brief stop_y    Y轴结束值
     * @return          值(ns)
     */
    float stop_y() const;

    /**
     * @brief width X轴宽度
     * @return      值(ns)
     */
    float width() const;

    /**
     * @brief height    Y轴高度
     * @return          值(ns)
     */
    float height() const;

signals:
    void xy_changed();

public slots:
    void update_xy();

private:
    float m_startX;
    float m_stopX;
    float m_startY;
    float m_stopY;
    DplFocallaw::FocallawerPointer m_focallawer;
    DplUt::SamplePointer m_sample;
};

inline float Sscan::start_x() const
{
    return m_startX;
}

inline float Sscan::stop_x() const
{
    return m_stopX;
}

inline float Sscan::start_y() const
{
    return m_startY;
}

inline float Sscan::stop_y() const
{
    return m_stopY;
}

inline float Sscan::width() const
{
    return m_stopX - m_startX;
}

inline float Sscan::height() const
{
    return m_stopY - m_startY;
}

typedef QSharedPointer<Sscan> SscanPointer;

}
#endif // __S_SCAN_H__
