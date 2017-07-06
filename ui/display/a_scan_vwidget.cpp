#include "a_scan_vwidget.h"

#include <QPainter>

AscanVWidget::AscanVWidget(QWidget *parent) :
    AscanWidget(parent)
{

}

int AscanVWidget::x_axis_length() const
{
    return height();
}

int AscanVWidget::y_axis_length() const
{
    return width();
}

void AscanVWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    QTransform form = painter.transform();
    form.rotate(90);
    form.rotate(180, Qt::XAxis);
    painter.setTransform(form);

    draw(painter);
}
