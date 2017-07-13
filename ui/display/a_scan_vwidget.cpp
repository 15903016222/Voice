#include "a_scan_vwidget.h"

#include <QPainter>

AscanVWidget::AscanVWidget(QWidget *parent) :
    AscanView(Qt::Vertical, parent)
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
