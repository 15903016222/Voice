#include "line.h"
#include <QStyleOption>
#include <QPainter>

Line::Line(Qt::Orientation orientation, QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    set_orientation(orientation);
}

Line::~Line()
{
}

void Line::set_orientation(Qt::Orientation orientation)
{
    if (orientation == Qt::Horizontal) {
        setMinimumHeight(3);
        setMaximumHeight(3);
    } else {
        setMinimumWidth(3);
        setMaximumWidth(3);
    }
}

void Line::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}
