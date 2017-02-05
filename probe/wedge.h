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

    /**
     * @brief serial    获取系列号
     * @return          系列号
     */
    const QString &serial() const;

    /**
     * @brief set_serial    设置系列号
     * @param val           系列号
     */
    void set_serial(const QString &val);

    /**
     * @brief model 获取型号
     * @return      型号
     */
    const QString &model() const;

    /**
     * @brief set_model 设置型号
     * @param val       型号
     */
    void set_model(const QString &val);

    /**
     * @brief angel 获取角度
     * @return      角度值，单位(度)
     */
    float angle() const;

    /**
     * @brief set_angel 设置角度
     * @param val       角度值，单位(度)
     */
    void set_angle(float val);

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
    /**
     * @brief load      加载楔块文件
     * @param fileName  文件名
     * @return          成功返回true,失败返回false
     */
    bool load(const QString &fileName);

    /**
     * @brief save      保存楔块文件
     * @param fileName  文件名
     * @return          成功返回true，失败返回false
     */
    bool save(const QString &fileName) const;

    enum WaveType {
        Longitudinal,
        Transverse
    };

    /**
     * @brief wave_type 获取波类型
     * @return          类型
     */
    WaveType wave_type() const;

    /**
     * @brief set_wave_type
     * @param type
     */
    void set_wave_type(WaveType type);

    /**
     * @brief ref_point 获取参考点
     * @return          参考点值，单位(mm)
     */
    float ref_point() const;

    /**
     * @brief set_ref_point 设置参考点
     * @param val           参考点值，单位(mm)
     */
    void set_ref_point(float val);

    enum Orientation {
        Normal,
        Reversal
    };

    /**
     * @brief orientation   获取探头方向
     * @return              方向
     */
    Orientation orientation() const;

    /**
     * @brief set_orientation   设置探头方向
     * @param val               方向
     */
    void set_orientation(Orientation val);

    /**
     * @brief velocity  获取声速
     * @return          声速值，单位(m/s)
     */
    int velocity() const;

    /**
     * @brief set_velocity  设置声速
     * @param val           声速值,单位(m/s)
     */
    void set_velocity(int val);

    /**
     * @brief primary_offset    主轴偏置
     * @return                  偏置值，单位(mm)
     */
    float primary_offset()const;

    /**
     * @brief set_primary_offset    设置主轴偏置
     * @param val                   偏置值，单位(mm)
     */
    void set_primary_offset(float val);

    /**
     * @brief secondary_offset  次轴偏置
     * @return                  偏置，单位(mm)
     */
    float secondary_offset() const;

    /**
     * @brief set_secondary_offset  设置次轴偏置
     * @param val                   偏置，单位(mm)
     */
    void set_secondary_offset(float val);

    /**
     * @brief height    获取第一阵元高度
     * @return          高度，单位(mm)
     */
    float height() const;

    /**
     * @brief set_height    设置第一阵元高度
     * @param val           高度值，单位(mm)
     */
    void set_height(float val);

    /**
     * @brief length    获取长度
     * @return          长度，单位(mm)
     */
    float length() const;

    /**
     * @brief set_lenght    设置长度
     * @param val           长度值，单位(mm)
     */
    void set_length(float val);

signals:
    void delay_changed(int value);

private:
    QString m_serial;           /* 系列 */
    QString m_model;            /* 型号 */
    float m_angle;              /* 角度，单位(度) */
    int m_delay;                /* 延迟时间，单位(ns) */
    WaveType m_waveType;        /* 波类型 */
    Orientation m_orientation;  /* 方向 */
    int m_velocity;             /* 声速,(m/s) */
    float m_primaryOffset;      /* 主轴偏置,(mm) */
    float m_secondaryOffset;    /* 次轴偏置,(mm) */
    float m_height;             /* 高度，(mm) */
    float m_length;             /* 长度，(mm) */
    float m_refPoint;           /* 参考点，(mm) */
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

inline const QString &Wedge::serial() const
{
    return m_serial;
}

inline void Wedge::set_serial(const QString &val)
{
    m_serial = val;
}

inline const QString &Wedge::model() const
{
    return m_model;
}

inline void Wedge::set_model(const QString &val)
{
    m_model = val;
}

inline float Wedge::angle() const
{
    return m_angle;
}

inline void Wedge::set_angle(float val)
{
    m_angle = val;
}

inline Wedge::WaveType Wedge::wave_type() const
{
    return m_waveType;
}

inline void Wedge::set_wave_type(Wedge::WaveType type)
{
    m_waveType = type;
}

inline float Wedge::ref_point() const
{
    return m_refPoint;
}

inline void Wedge::set_ref_point(float val)
{
    m_refPoint = val;
}

inline Wedge::Orientation Wedge::orientation() const
{
    return m_orientation;
}

inline void Wedge::set_orientation(Wedge::Orientation val)
{
    m_orientation = val;
}

inline int Wedge::velocity() const
{
    return m_velocity;
}

inline void Wedge::set_velocity(int val)
{
    m_velocity = val;
}

inline float Wedge::primary_offset() const
{
    return m_primaryOffset;
}

inline void Wedge::set_primary_offset(float val)
{
    m_primaryOffset = val;
}

inline float Wedge::secondary_offset() const
{
    return m_secondaryOffset;
}

inline void Wedge::set_secondary_offset(float val)
{
    m_secondaryOffset = val;
}

inline float Wedge::height() const
{
    return m_height;
}

inline void Wedge::set_height(float val)
{
    m_height = val;
}

inline float Wedge::length() const
{
    return m_length;
}

inline void Wedge::set_length(float val)
{
    m_length = val;
}

}

#endif // __WEDGE_H__
