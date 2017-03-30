#ifndef __TRUE_DEPTH_FOCUS_H__
#define __TRUE_DEPTH_FOCUS_H__

#include "focus_cnf.h"

namespace DplFocallaw {

class TrueDepthFocusPrivate;
class FOCALLAWSHARED_EXPORT TrueDepthFocus : public FocusCnf
{
    Q_DECLARE_PRIVATE(TrueDepthFocus)
public:
    explicit TrueDepthFocus();
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
     */
    void set_depth(float depth);

private:
    TrueDepthFocusPrivate *d_ptr;
};

typedef QSharedPointer<TrueDepthFocus> TrueDepthFocusPointer;

}

#endif // __TRUE_DEPTH_FOCUS_H__
