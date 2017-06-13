/**
 * @file scan_cnf.h
 * @brief 扫查配置基类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-28d
 */
#ifndef __FOCALLAW_SCAN_CNF_H__
#define __FOCALLAW_SCAN_CNF_H__

#include "focallaw_global.h"

#include <QSharedPointer>

namespace DplFocallaw {

class ScanCnfPrivate;
class FOCALLAWSHARED_EXPORT ScanCnf : public QObject
{
    Q_DECLARE_PRIVATE(ScanCnf)
    Q_OBJECT
public:
    explicit ScanCnf(uint elemQty, QObject *parent=0);
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
    virtual bool set_aperture(uint val);

    /**
     * @brief first_element 获取起始阵元
     * @return              阵元号，从0算起
     */
    uint first_element() const;

    /**
     * @brief set_first_element 设置起始阵元
     * @param pos               阵元号,从0算起
     * @return                  成功返回true，失败返回false
     */
    virtual bool set_first_element(uint pos);

    /**
     * @brief element_qty   获取阵元总数
     * @return              数量
     */
    uint element_qty() const;

    /**
     * @brief set_element_qty   设置阵元总数
     * @param qty               数量
     */
    virtual void set_element_qty(uint qty);

private:
    ScanCnfPrivate *d_ptr;
};

typedef QSharedPointer<ScanCnf> ScanCnfPointer;

}

#endif // __FOCALLAW_SCAN_CNF_H__
