#include "color_bar.h"

#include <QPainter>

ColorBar::ColorBar(QWidget *parent) :
    QWidget(parent)
{

}

void ColorBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    if (m_palette.isNull() || m_palette->size() == 0) {
        return;
    }

    QLinearGradient l(width()/2, 0, width()/2, height());
    float step = 1.0 / m_palette->size();

    for (int i = 0; i < m_palette->size(); ++i) {
        l.setColorAt(step* (m_palette->size() - i - 1), m_palette->color(i));
    }

    QPainter painter(this);
    painter.setBrush(QBrush(l));
    painter.drawRect(rect());
}
