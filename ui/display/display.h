/**
 * @file display.h
 * @brief A/B/C/S显示布局管理类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <device/group.h>
#include "scan_layout.h"

namespace DplUi {

class Display : public QWidget
{
    Q_OBJECT
public:
    static Display *get_instance();

public slots:
    void set_layout(ScanLayout *scanlayout);

protected:
    explicit Display(QWidget *parent = 0);

private:
    ScanLayout *m_scanLayout;
};

}

#endif // __DISPLAY_H__
