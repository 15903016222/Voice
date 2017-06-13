/**
 * @file pa_probe.h
 * @brief PA探头
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __PA_PROBE_H__
#define __PA_PROBE_H__

#include "probe.h"
#include "linear_scan_cnf.h"
#include "sectorial_scan_cnf.h"

namespace DplFocallaw {

class PaProbePrivate;
class PaProbe : public Probe
{
    Q_DECLARE_PRIVATE(PaProbe)
    Q_OBJECT
public:
    explicit PaProbe(QObject *parent = 0);
    ~PaProbe();

    bool is_pa() const { return true; }

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
    bool save(const QString &fileName);

    enum ArrayMode {
        CURVED,         /* 曲型 */
        DUAL_LINEAR,    /* 双线性，一发一收 */
        DUAL_MATRIX,    /* 双矩阵，一发一收 */
        LINEAR,         /* 线性，自发自收 */
        MATRIX          /* 矩阵，自发自收 */
    };

    /**
     * @brief array_mode    获取阵元模式
     * @return              阵元类型
     */
    ArrayMode array_mode() const;

    /**
     * @brief set_array_mode    设置阵元类型
     * @param mode              阵元类型
     */
    void set_array_mode(ArrayMode mode);

    /**
     * @brief primary_element_qty   获取主轴阵元数
     * @return                      数量
     */
    uint primary_element_qty() const;

    /**
     * @brief set_primary_element_qty   设置主轴阵元数
     * @param qty                       数量
     */
    void set_primary_element_qty(uint qty);

    /**
     * @brief secondary_element_qty 获取次轴阵元数
     * @return                      数量
     */
    uint secondary_element_qty() const;

    /**
     * @brief set_secondary_element_qty 设置次轴阵元数
     * @param qty                       数量
     */
    void set_secondary_element_qty(uint qty);

    /**
     * @brief element_qty   获取总阵元数
     * @return              数量
     */
    uint element_qty() const;

    /**
     * @brief primary_pitch 获取主轴pitch
     * @return              pitch值
     */
    float primary_pitch() const;

    /**
     * @brief set_primary_pitch 设置主轴pitch
     * @param pitch             pitch值
     *
     */
    void set_primary_pitch(float pitch);

    /**
     * @brief secondary_pitch   获取次轴pitch
     * @return                  pitch值
     */
    float secondary_pitch() const;

    /**
     * @brief set_secondary_pitch   设置次pitch
     * @param pitch                 pitch值
     */
    void set_secondary_pitch(float pitch);

    /**
     * @brief scan_configure    获取扫查配置对象
     * @return                  扫查配置对象指针
     */
    const ScanCnfPointer &scan_configure() const;

    /**
     * @brief set_scan_configure    设置扫查配置对象
     * @param cnf                   扫查配置对象指针
     */
    void set_scan_configure(const ScanCnfPointer &cnf);

private:
    PaProbePrivate *d_ptr;
};

typedef QSharedPointer<PaProbe> PaProbePointer;

}

#endif // __PA_PROBE_H__
