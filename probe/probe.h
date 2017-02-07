#ifndef __PROBE_H__
#define __PROBE_H__

#include <QObject>
#include <QSharedPointer>

namespace DplProbe {

class ProbePrivate;
class Probe;
typedef QSharedPointer<Probe> ProbePointer;

class Probe : public QObject
{
    Q_OBJECT
public:   
    explicit Probe(QObject *parent = 0);
    virtual ~Probe();

    /**
     * @brief load  加载探头文件
     * @param file  探头文件
     * @return      成功返回true， 否则false
     */
    virtual bool load(const QString &fileName);

    /**
     * @brief save  保存探头数据
     * @param file  保存文件
     * @return      成功返回true，否则false
     */
    virtual bool save(const QString &fileName);

    enum Type {
        CONTACT,    /* 直接接触式类型 */
        DELAY,      /* 延迟块式 */
        IMMERSION,  /* 水浸式 */
        ANGLE_BEAM, /* 角度声速类型 */
        DUAL,       /* 双晶探头，UT专有 */
        TOFD        /* Tofd探头，UT专有 */
    };

    /**
     * @brief is_pa_probe   判断是否为PA探头
     * @return              PA探头返回true，否则为false
     */
    virtual bool is_pa_probe() const { return false; }

    /**
     * @brief type  获取探头类型
     * @return      探头类型
     */
    Type type() const;

    /**
     * @brief set_type  设置探头类型
     * @param type      探头类型
     */
    void set_type(Type type);

    /**
     * @brief model 获取探头型号
     * @return      型号
     */
    const QString &model() const;

    /**
     * @brief set_model 设置探头型号
     * @param model     探头型号
     */
    void set_model(const QString &model);

    /**
     * @brief serial    获取探头系列号
     * @return          探头系列号
     */
    const QString &serial() const;

    /**
     * @brief set_serial    设置探头系列号
     * @param serial        探头系列号
     */
    void set_serial(const QString &serial);

    /**
     * @brief freq  获取频率
     * @return      频率(MHz)
     */
    double freq() const;

    /**
     * @brief set_freq  设置频率
     * @param val       频率(MHz)
     */
    void set_freq(double val);

    /**
     * @brief element_elevation 获取阵元高度
     * @return                  阵元高度(mm)
     */
    double element_elevation() const;

    /**
     * @brief set_element_elevation 设置阵元高度
     * @param val                   高度(mm)
     */
    void set_element_elevation(double val);

    /**
     * @brief refpoint  获取参考点
     * @return          参考点，单位(mm)
     */
    double refpoint() const;

    /**
     * @brief set_refpoint  设置参考点
     * @param val           参考点，单位(mm)
     */
    void set_refpoint(double val);

private:
    QString m_model;
    QString m_serial;
    Type m_type;
    double m_freq;          /* 频率(MHz) */
    double m_elemElevation; /* 阵元高度(mm) */
    double m_refPoint;      /* 参考点(mm) */
};

inline const QString &Probe::model() const
{
    return m_model;
}

inline void Probe::set_model(const QString &model)
{
    m_model = model;
}

inline const QString &Probe::serial() const
{
    return m_serial;
}

inline void Probe::set_serial(const QString &serial)
{
    m_serial = serial;
}

inline Probe::Type Probe::type() const
{
    return m_type;
}

inline void Probe::set_type(Probe::Type type)
{
    m_type = type;
}

inline double Probe::element_elevation() const
{
    return m_elemElevation;
}

inline void Probe::set_element_elevation(double val)
{
    m_elemElevation = val;
}

inline double Probe::freq() const
{
    return m_freq;
}

inline void Probe::set_freq(double val)
{
    m_freq = val;
}

inline double Probe::refpoint() const
{
    return m_refPoint;
}

inline void Probe::set_refpoint(double val)
{
    m_refPoint = val;
}

}
#endif // PROBE_H
