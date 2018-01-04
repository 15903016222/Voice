/**
 * @file half_path_focus.h
 * @brief 半声程聚焦点类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __HALF_PATH_FOCUS_H__
#define __HALF_PATH_FOCUS_H__

#include "focus.h"

namespace DplFocallaw {

class HalfPathFocusPrivate;
class FOCALLAWSHARED_EXPORT HalfPathFocus : public Focus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HalfPathFocus)
public:
    explicit HalfPathFocus(QObject *parent);
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
     * @return              成功返回true,失败返回false
     */
    bool set_radius(float radius);

signals:
    void radius_changed(float);

private:
    HalfPathFocusPrivate *d_ptr;
};

typedef QSharedPointer<HalfPathFocus> HalfPathFocusPointer;

}

#endif // __HALF_PATH_FOCUS_H__
