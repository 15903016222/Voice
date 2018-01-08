/**
 * @file true_depth_focus.h
 * @brief 真实深度聚焦点
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __TRUE_DEPTH_FOCUS_H__
#define __TRUE_DEPTH_FOCUS_H__

#include "focus.h"

namespace DplFocallaw {

class TrueDepthFocusPrivate;
class FOCALLAWSHARED_EXPORT TrueDepthFocus : public Focus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TrueDepthFocus)
public:
    explicit TrueDepthFocus(QObject *parent=0);
    ~TrueDepthFocus();

    /**
     * @brief mode  获取聚焦模式
     * @return      聚焦模式
     */
    Mode mode() const;

    /**
     * @brief depth 获取聚焦深度
     * @return      深度(mm)
     */
    float depth() const;

    /**
     * @brief set_depth 设置聚焦深度
     * @param depth     深度(mm)
     * @return          成功返回true, 失败返回false
     */
    bool set_depth(float depth);

signals:
    void depth_changed(float depth);

private:
    TrueDepthFocusPrivate *d_ptr;
};

typedef QSharedPointer<TrueDepthFocus> TrueDepthFocusPointer;

}

#endif // __TRUE_DEPTH_FOCUS_H__
