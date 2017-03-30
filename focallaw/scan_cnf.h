/**
 * @file scan_cnf.h
 * @brief 扫查配置基类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-28d
 */
#ifndef __FOCALLAW_SCAN_CNF_H__
#define __FOCALLAW_SCAN_CNF_H__

#include "focallaw_global.h"
#include "pa_probe.h"

namespace DplFocallaw {

class ScanCnfPrivate;
class FOCALLAWSHARED_EXPORT ScanCnf : public QObject
{
    Q_DECLARE_PRIVATE(ScanCnf)
    Q_OBJECT
public:
    explicit ScanCnf(QObject *parent=0);
    virtual ~ScanCnf();

    enum Mode {
        Linear,     // 线性扫查
        Sectorial   // 扇性扫查
    };

    /**
     * @brief mode  获取扫描模式
     * @return      扫描模式
     */
    virtual Mode mode() const = 0;

    /**
     * @brief aperture  获取孔径
     * @return          孔径
     */
    uint aperture() const;

    /**
     * @brief set_aperture  设置孔径
     * @param val           孔径
     * @return              设置成功返回true，失败返回false
     */
    bool set_aperture(uint val);

    /**
     * @brief first_element 获取起始阵元
     * @return              阵元号
     */
    uint first_element() const;

    /**
     * @brief set_first_element 设置起始阵元
     * @param pos               阵元号
     * @return                  成功返回true，失败返回false
     */
    bool set_first_element(uint pos);

    /**
     * @brief probe 获取探头
     * @return      探头对象
     */
    const PaProbePointer &probe() const;

    /**
     * @brief set_probe 设置探头
     * @param p         探头对象
     */
    bool set_probe(const PaProbePointer &p);

signals:
    void probe_changed(const PaProbePointer &p);

private:
    ScanCnfPrivate *d_ptr;
};

typedef QSharedPointer<ScanCnf> ScanCnfPointer;

}

#endif // __FOCALLAW_SCAN_CNF_H__
