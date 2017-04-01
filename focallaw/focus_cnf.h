/**
 * @file focus_cnf.h
 * @brief 聚焦点配置类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __FOCUS_CNF_H__
#define __FOCUS_CNF_H__

#include "focallaw_global.h"

#include <QSharedPointer>

namespace DplFocallaw {

class FOCALLAWSHARED_EXPORT FocusCnf
{
public:
    explicit FocusCnf() {}

    enum Mode {
        HALF_PATH,  /* 半声程 */
        TRUE_DEPTH, /* 真实深度 */
        PROJECTION, /* 投影 */
        FOCAL_PLANE,/* 任意面 */
        DDF         /* 动态聚焦 */
    };

    /**
     * @brief mode  获取聚焦模式
     * @return      聚焦模式
     */
    virtual Mode mode() const = 0;

private:
    Q_DISABLE_COPY(FocusCnf)
};

typedef QSharedPointer<FocusCnf> FocusCnfPointer;

}

#endif // __FOCUS_CNF_H__
