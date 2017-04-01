/**
 * @file sectorial_scan_cnf.h
 * @brief 扇扫配置类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __SECTORIAL_SCAN_CNF_H__
#define __SECTORIAL_SCAN_CNF_H__

#include "scan_cnf.h"

namespace DplFocallaw {

class SectorialScanCnfPrivate;
class FOCALLAWSHARED_EXPORT SectorialScanCnf : public ScanCnf
{
    Q_DECLARE_PRIVATE(SectorialScanCnf)
    Q_OBJECT
public:
    explicit SectorialScanCnf(QObject *parent=0);
    ~SectorialScanCnf();

    /**
     * @brief mode  获取扫描模式
     * @return      扫描模式
     */
    Mode mode() const;

    /**
     * @brief first_angle   获取开始角度
     * @return              角度(°)
     */
    float first_angle() const;

    /**
     * @brief set_first_angle   设置开始角度
     * @param angle             角度(°)
     * @return                  成功返回true，否则false
     */
    bool set_first_angle(float angle);

    /**
     * @brief last_angle    获取结束角度
     * @return              角度(°)
     */
    float last_angle() const;

    /**
     * @brief set_last_angle    设置结束角度
     * @param angle             角度(°)
     * @return                  成功返回true，否则false
     */
    bool set_last_angle(float angle);

    /**
     * @brief angle_step    获取角度步进
     * @return              步进值(°)
     */
    float angle_step() const;

    /**
     * @brief set_angle_step    设置角度步进
     * @param step              步进值(°)
     * @return                  成功返回true，否则false
     */
    bool set_angle_step(float step);

private:
    SectorialScanCnfPrivate *d_ptr;
};

typedef QSharedPointer<SectorialScanCnf> SectorialScanCnfPointer;

}

#endif // __SECTORIAL_SCAN_CNF_H__
