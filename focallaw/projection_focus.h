/**
 * @file projection_focus.h
 * @brief  投影聚焦点类
 * @author Long Wen Zhi <longwenzhi@cndoppler.cn>
 * @date 2017-09-07
 */
#ifndef __PROJECTIONFOCUS_H__
#define __PROJECTIONFOCUS_H__

#include "focus.h"

namespace DplFocallaw {

class ProjectionFocusPrivate;
class FOCALLAWSHARED_EXPORT ProjectionFocus : public Focus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ProjectionFocus)
public:
    explicit  ProjectionFocus(QObject *parent = 0);
    ~ProjectionFocus();

    /**
     * @brief mode  获取聚焦模式
     * @return      聚焦模式
     */
    Mode mode() const;

    /**
     * @brief offset    获取离楔块前表面的偏移量
     * @return          偏移量(mm)
     */
    float offset() const;

    /**
     * @brief set_offset    设置离楔块前表面的偏移量
     * @param offset        偏移量(mm)
     * @return              设置成功返回true,失败返回false
     */
    bool set_offset(float offset);

signals:
    void offset_changed(float val);

private:
    ProjectionFocusPrivate *d_ptr;
};

typedef QSharedPointer<ProjectionFocus> ProjectionFocusPointer;

}
#endif // PROJECTIONFOCUS_H
