#ifndef __PA_PROBE_H__
#define __PA_PROBE_H__

#include "probe.h"

namespace DplProbe {

class PaProbe;
typedef QSharedPointer<PaProbe> PaProbePointer;

class PaProbe : public Probe
{
    Q_OBJECT
public:
    PaProbe(QObject *parent = 0);

    bool is_pa_probe() const { return true; }

    /**
     * @brief load  加载探头文件
     * @param file  探头文件
     * @return      成功返回true， 否则false
     */
    bool load(const QString &fileName);

    /**
     * @brief save  保存探头数据
     * @param file  保存文件
     * @return      成功返回true，否则false
     */
    bool save(const QString &fileName) const;

    enum ArrayType {
        CURVED,         /* 曲型 */
        DUAL_LINEAR,    /* 双线性，一发一收 */
        DUAL_MATRIX,    /* 双矩阵，一发一收 */
        LINEAR,         /* 线性，自发自收 */
        MATRIX          /* 矩阵，自发自收 */
    };

    /**
     * @brief array_type    获取阵元类型
     * @return              阵元类型
     */
    ArrayType array_type() const;

    /**
     * @brief set_array_type    设置阵元类型
     * @param type              阵元类型
     */
    void set_array_type(ArrayType type);

    /**
     * @brief principal_axis_element_qty    获取主轴阵元数
     * @return                              阵元数
     */
    int principal_axis_element_qty() const;

    /**
     * @brief set_principal_axis_element_qty    设置主轴阵元数
     * @param val                               阵元数
     */
    void set_principal_axis_element_qty(int val);

    /**
     * @brief secondary_axis_element_qty    获取副轴阵元数
     * @return                              阵元数
     */
    int secondary_axis_element_qty() const;

    /**
     * @brief set_secondary_axis_element_qty    设置副轴阵元数
     * @param val                               阵元数
     */
    void set_secondary_axis_element_qty(int val);

    /**
     * @brief element_qty   获取总阵元数
     * @return              阵元数
     */
    int element_qty() const;

    /**
     * @brief principal_axis_pitch  获取主轴阵元间距
     * @return                      间距值(mm)
     */
    double principal_axis_pitch() const;

    /**
     * @brief set_principa_axis_pitch   设置主轴阵元间距
     * @param val                       间距(mm)
     */
    void set_principa_axis_pitch(double val);

    /**
     * @brief secondary_axis_pitch  获取副轴阵元间距
     * @return                      间距值(mm)
     */
    double secondary_axis_pitch() const;

    /**
     * @brief set_secondary_axis_pitch  设置副轴阵元间距
     * @param val                       间距(mm)
     */
    void set_secondary_axis_pitch(double val);

    enum WaveType {
        Longitudinal,   /* 纵波 */
        Transverse      /* 横波 */
    };

    /**
     * @brief rx_wave   获取接收波类型
     * @return          波类型
     */
    WaveType rx_wave() const;

    /**
     * @brief set_rx_wave   设置接收波类型
     * @param type          波类型
     */
    void set_rx_wave(WaveType type);

    /**
     * @brief tx_wave   获取发送波类型
     * @return          波类型
     */
    WaveType tx_wave() const;

    /**
     * @brief set_tx_wave   设置发送波类型
     * @param type          波类型
     */
    void set_tx_wave(WaveType type);

private:
    ArrayType m_arrayType;
    int m_priElemQty;       /* 主轴阵元数 */
    int m_secElemQty;       /* 副轴阵元数 */
    double m_priPitch;      /* 主轴阵元间距(mm) */
    double m_secPitch;      /* 副轴阵元间距(mm) */
    WaveType m_rxWave;      /* 接收波类型 */
    WaveType m_txWave;      /* 发送波类型 */
};

inline PaProbe::ArrayType PaProbe::array_type() const
{
    return m_arrayType;
}

inline void PaProbe::set_array_type(PaProbe::ArrayType type)
{
    m_arrayType = type;
}

inline int PaProbe::principal_axis_element_qty() const
{
    return m_priElemQty;
}

inline void PaProbe::set_principal_axis_element_qty(int val)
{
    m_priElemQty = val;
}

inline int PaProbe::secondary_axis_element_qty() const
{
    return m_secElemQty;
}

inline void PaProbe::set_secondary_axis_element_qty(int val)
{
    m_secElemQty = val;
}

inline int PaProbe::element_qty() const
{
    return m_priElemQty * m_secElemQty;
}

inline double PaProbe::principal_axis_pitch() const
{
    return m_priPitch;
}

inline void PaProbe::set_principa_axis_pitch(double val)
{
    m_priPitch = val;
}

inline double PaProbe::secondary_axis_pitch() const
{
    return m_secPitch;
}

inline void PaProbe::set_secondary_axis_pitch(double val)
{
    m_secPitch = val;
}

inline PaProbe::WaveType PaProbe::rx_wave() const
{
    return m_rxWave;
}

inline void PaProbe::set_rx_wave(WaveType type)
{
    m_rxWave = type;
}

inline PaProbe::WaveType PaProbe::tx_wave() const
{
    return m_txWave;
}

inline void PaProbe::set_tx_wave(WaveType type)
{
    m_txWave = type;
}

}

#endif // PAPROBE_H
