#ifndef __DPL_WELD_BASE_WELD_WIDGET_H__
#define __DPL_WELD_BASE_WELD_WIDGET_H__

#include "weldwidget_global.h"
#include "base_weld_information.h"

#include <QWidget>
#include <QDebug>
#include <QPainter>

namespace DplWeld {

#define EQ_VALUE  0.005 /* 当前取值精度为0.01mm；若两个double相减小于0.005则认为两者相等， */

class WELDWIDGETSHARED_EXPORT BaseWeldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo, QWidget *parent = 0);

    void update_weld_information(QSharedPointer<BaseWeldInformation> &weldInfo);

    int get_weld_type();

signals:
    /*  以下四个信号为U型焊缝所发送的
     */
    void max_W1(double value);
    void max_W2(double value);
    void min_H1(double value);
    void min_R1(double value);

    /* 双U */
    void max_W3(double value);
    void min_H2(double value);
    void min_R2(double value);

    /* TKY */
    void min_angle(double value);
    void max_angle(double value);
    void min_X1(double value);
    void min_X2(double value);
    void max_Y1(double value);
    void max_Y2(double value);

protected:
    void paintEvent(QPaintEvent *event);
    virtual void paint() = 0;
    virtual void paint_symbol() = 0;

    QSharedPointer<BaseWeldInformation> m_weldInfo;


};

}

#endif // __DPL_WELD_BASE_WELD_WIDGET_H__
