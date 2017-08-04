/**
 * @file display_widget.h
 * @brief A/B/C/S显示布局管理类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#ifndef __DISPLAY_WIDGET_H__
#define __DISPLAY_WIDGET_H__

#include <QWidget>
#include <device/group.h>
#include <display/display.h>

namespace DplUi {

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(const DplDisplay::DisplayPointer &display,
                           QWidget *parent = 0);

public slots:
    void set_layout(DplDisplay::Display::Layout mode, const QVector<int> &grps);

private:
    DplDisplay::DisplayPointer m_display;
};

}

#endif // __DISPLAY_WIDGET_H__
