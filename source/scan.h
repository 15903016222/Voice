/**
 * @file scan.h
 * @brief 扫查配置类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-04-24
 */

#ifndef __DPLSOURCE_SCAN_H__
#define __DPLSOURCE_SCAN_H__

#include "axis.h"

namespace DplSource {

class ScanPrivate;
class SOURCESHARED_EXPORT Scan : public QObject
{    
    Q_DECLARE_PRIVATE(Scan)
    Q_OBJECT
public:
    static Scan *instance();

    enum Mode {
        ONELINE,    // 单线检测
        RASTER,     // 光栅检测
    };

    /**
     * @brief scan_axis 获取扫查轴
     * @return          扫查轴
     */
    Axis *scan_axis() const;

    /**
     * @brief index_axis    获取步进轴
     * @return              步进轴
     */
    Axis *index_axis() const;

    /**
     * @brief speed 获取扫查速度
     * @return      扫查速度(mm/s)
     */
    float speed() const;

    /**
     * @brief set_speed 设置扫查速度
     * @param val       扫查速度(mm/s)
     */
    void set_speed(float val);

protected:
    explicit Scan(QObject *parent = 0);
    ~Scan();

private:
    ScanPrivate *d_ptr;
};

}

#endif // __DPLSOURCE_SCAN_H__
