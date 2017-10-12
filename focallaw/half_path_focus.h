/**
 * @file half_path_focus.h
 * @brief 半声程聚焦点类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __HALF_PATH_FOCUS_H__
#define __HALF_PATH_FOCUS_H__

#include "focus_cnf.h"

namespace DplFocallaw {

class HalfPathFocusPrivate;
class FOCALLAWSHARED_EXPORT HalfPathFocus : public FocusCnf
{
    Q_DECLARE_PRIVATE(HalfPathFocus)
public:
    explicit HalfPathFocus();
    ~HalfPathFocus();

    /**
     * @brief mode  获取聚焦模式
     * @return      聚焦模式
     */
    Mode mode() const;

    /**
     * @brief radius    获取聚焦半径
     * @return          半径(mm)
     */
    float radius() const;

    /**
     * @brief set_radius    设置聚焦半径
     * @param radius        半径(mm)
     */
    void set_radius(float radius);

private:
    HalfPathFocusPrivate *d_ptr;
};

typedef QSharedPointer<HalfPathFocus> HalfPathFocusPointer;

}

#endif // __HALF_PATH_FOCUS_H__
