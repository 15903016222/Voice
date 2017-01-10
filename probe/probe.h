#ifndef __PROBE_H__
#define __PROBE_H__

#include <QObject>

namespace DplProbe {

class ProbePrivate;
class Probe : public QObject
{
    Q_OBJECT
public:
    enum Type {
        UNKNOWN     = 0,
        CUSTOM      = 1,    /* 自定义 */
        ANGLE_BEAM  = 3,    /* 斜探头 */
        CONTACT     = 5,    /* 接触式 */
        IMMERSION   = 6,    /* 水浸式 */
        CONVENTION  = 7     /* 常规 */
    };

    explicit Probe(QObject *parent = 0);
    ~Probe();

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
     * @brief element_qty   获取阵元数
     * @return              阵元数
     */
    int element_qty() const;

    /**
     * @brief set_element_qty   设置阵元数
     * @param qty               阵元数
     */
    void set_element_qty(int qty);

    /**
     * @brief pitch 获取阵元间距
     * @return      间距, 单位(um)
     */
    int pitch() const;

    /**
     * @brief set_pitch 设置阵元间距
     * @param val       间距，单位(um)
     */
    void set_pitch(int val);

    /**
     * @brief freq  获取频率
     * @return      频率(kHz)
     */
    int freq() const;

    /**
     * @brief set_freq  设置频率
     * @param val       频率(kHz)
     */
    void set_freq(int val);

    /**
     * @brief refpoint  获取参考点
     * @return          参考点，单位(um)
     */
    int refpoint() const;

    /**
     * @brief set_refpoint  设置参考点
     * @param val           参考点，单位(um)
     */
    void set_refpoint(int val);

    /**
     * @brief load  加载探头文件
     * @param file  探头文件
     */
    bool load(const QString &fileName);

    /**
     * @brief save  保存探头数据
     * @param file  保存文件
     */
    void save(const QString &fileName);

    /**
     * @brief show  显示探头信息
     * @return      探头信息
     */
    const QString show() const;

signals:

public slots:


private:
    Probe::Type m_type;
    QString m_model;
    QString m_serial;
    int m_elemQty;
    int m_freq;
    int m_pitch;
    int m_refPoint;

    void update_pa(const QByteArray &bytes);
    void update_ut(const QByteArray &bytes);
};

inline Probe::Type Probe::type() const
{
    return m_type;
}

inline void Probe::set_type(Probe::Type type)
{
    m_type = type;
}

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

inline int Probe::element_qty() const
{
    return m_elemQty;
}

inline void Probe::set_element_qty(int qty)
{
    m_elemQty = qty;
}

inline int Probe::pitch() const
{
    return m_pitch;
}

inline void Probe::set_pitch(int val)
{
    m_pitch = val;
}

inline int Probe::freq() const
{
    return m_freq;
}

inline void Probe::set_freq(int val)
{
    m_freq = val;
}

inline int Probe::refpoint() const
{
    return m_refPoint;
}

inline void Probe::set_refpoint(int val)
{
    m_refPoint = val;
}

}
#endif // PROBE_H
