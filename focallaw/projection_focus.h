/**
 * @file projection_focus.h
 * @brief  投影聚焦点类
 * @author Long Wen Zhi <longwenzhi@cndoppler.cn>
 * @date 2017-09-07
 */
#ifndef __PROJECTIONFOCUS_H__
#define __PROJECTIONFOCUS_H__

#include "focus_cnf.h"

namespace DplFocallaw {

class ProjectionFocusPrivate;
class FOCALLAWSHARED_EXPORT ProjectionFocus : public FocusCnf
{
    Q_DECLARE_PRIVATE(ProjectionFocus)
public:
    explicit  ProjectionFocus();
    ~ProjectionFocus();

    /**
     * @brief mode  获取聚焦模式
     * @return      聚焦模式
     */
    Mode mode() const;

    /**
     * @brief offset    获取离楔块前表面的偏移量
     * @return             偏移量(mm)
     */
    float offset() const;

    /**
     * @brief set_offset    设置离楔块前表面的偏移量
     * @param offset        偏移量(mm)
     */
    void set_offset(float offset);

private:
    ProjectionFocusPrivate *d_ptr;
};

typedef QSharedPointer<ProjectionFocus> ProjectionFocusPointer;

}
#endif // PROJECTIONFOCUS_H
