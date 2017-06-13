/**
 * @file linear_scan_cnf.h
 * @brief 线性扫查类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __FOCALLAW_LINEAR_SCAN_CNF_H__
#define __FOCALLAW_LINEAR_SCAN_CNF_H__

#include "scan_cnf.h"

namespace DplFocallaw {

class LinearScanCnfPrivate;
class FOCALLAWSHARED_EXPORT LinearScanCnf : public ScanCnf
{
    Q_DECLARE_PRIVATE(LinearScanCnf)
    Q_OBJECT
public:
    explicit LinearScanCnf(uint elemQty, QObject *parent=0);
    ~LinearScanCnf();

    /**
     * @brief mode  获取扫描模式
     * @return      扫描模式
     */
    Mode mode() const;

    /**
     * @brief set_aperture  设置孔径
     * @param val           孔径
     * @return              设置成功返回true，失败返回false
     */
    bool set_aperture(uint val);

    /**
     * @brief set_first_element 设置起始阵元
     * @param pos               阵元号,从0算起
     * @return                  成功返回true，失败返回false
     */
    bool set_first_element(uint pos);

    /**
     * @brief last_element  获取结束阵元号
     * @return              阵元号,从0算起
     */
    uint last_element() const;

    /**
     * @brief set_last_element  设置结束阵元号
     * @param pos               阵元号，从0算起
     * @return                  成功返回true，失败返回false
     */
    bool set_last_element(uint pos);

    /**
     * @brief element_step  获取阵元步进
     * @return              步进
     */
    uint element_step();

    /**
     * @brief set_element_step  设置阵元步进
     * @param step              步进
     * @return                  成功返回true，否则false
     */
    bool set_element_step(uint step);

    /**
     * @brief angle 获取光束角度
     * @return      角度(°)
     */
    float angle() const;

    /**
     * @brief set_angle 设置光束角度
     * @param angle     角度(°)
     * @return          成功返回true，否则false
     */
    bool set_angle(float angle);

    /**
     * @brief set_element_qty   设置阵元总数
     * @param qty               数量
     */
    virtual void set_element_qty(uint qty);

private:
    LinearScanCnfPrivate *d_ptr;
};

typedef QSharedPointer<LinearScanCnf> LinearScanCnfPointer;

}

#endif // __FOCALLAW_LINEAR_SCAN_CNF_H__
