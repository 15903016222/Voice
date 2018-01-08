/**
 * @file projection_focus.h
 * @brief  任意面聚焦点类
 * @author Long Wen Zhi <longwenzhi@cndoppler.cn>
 * @date 2017-09-07
 */
#ifndef __FOCALPLANEFOCUS_H__
#define __FOCALPLANEFOCUS_H__

#include "focus.h"

namespace DplFocallaw {

class FocalPlaneFocusPrivate;
class FOCALLAWSHARED_EXPORT FocalPlaneFocus: public Focus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FocalPlaneFocus)
public:
    explicit FocalPlaneFocus(QObject *parent = 0);
    ~FocalPlaneFocus();

    /**
     * @brief mode  获取聚焦模式
     * @return      聚焦模式
     */
    Mode mode() const;

    /**
     * @brief begin_offset    获取离楔块前表面的开始偏移量
     * @return             开始偏移量(mm)
     */
    float begin_offset() const;

    /**
     * @brief set_begin_offset  设置离楔块前表面的开始偏移量
     * @param val               开始偏移量 (mm)
     * @return                  设置成功返回true,失败返回false
     */
    bool set_begin_offset(float val);

    /**
     * @brief end_offset    获取离楔块前表面的结束偏移量
     * @return              结束偏移量(mm)
     */
    float end_offset() const;

    /**
     * @brief set_end_offset    设置离楔块前表面的结束偏移量
     * @param val               结束偏移量(mm)
     * @return                  成功返回true,失败返回false
     */
    bool set_end_offset(float val);

    /**
     * @brief begin_depth   获取开始聚焦深度
     * @return              开始聚焦深度(mm)
     */
    float begin_depth() const;

    /**
     * @brief set_begin_depth   设置开始聚焦深度
     * @param val               开始聚焦深度(mm)
     * @return                  成功返回true,失败返回false
     */
    bool set_begin_depth(float val);

    /**
     * @brief end_depth 获取结束聚焦深度
     * @return          结束聚焦深度(mm)
     */
    float end_depth() const;

    /**
     * @brief set_end_depth 设置结束聚焦深度
     * @param val           结束聚焦深度(mm)
     * @return              成功返回true,失败返回false
     */
    bool set_end_depth(float val);

signals:
    void begin_offset_changed(float);
    void end_offset_changed(float);
    void begin_depth_changed(float);
    void end_depth_changed(float);

private:
    FocalPlaneFocusPrivate *d_ptr;
};

typedef QSharedPointer<FocalPlaneFocus> FocalPlaneFocusPointer;

}
#endif // FOCALPLANEFOCUS_H
