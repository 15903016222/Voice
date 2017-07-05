/**
 * @file a_scan_hwidget.cpp
 * @brief A扫横向显示
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#include "a_scan_hwidget.h"

#include <QPainter>

AscanHWidget::AscanHWidget(QWidget *parent) :
    AscanWidget(parent)
{

}

int AscanHWidget::x_axis_length() const
{
    return width();
}

int AscanHWidget::y_axis_length() const
{
    return height();
}

void AscanHWidget::paintEvent(QPaintEvent *e)
{
    qDebug("%s[%d]: ",__func__, __LINE__);

    QPainter painter(this);
    painter.translate(0, height());

    QTransform form = painter.transform();

    form.rotate(180, Qt::XAxis);

    painter.setTransform(form);

    painter.setPen( wave_color() );
    painter.drawPath( paint_wave() );
}