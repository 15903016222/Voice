#include "ruler_widget.h"
#include <QPainter>
#include <QDebug>

RulerWidget::RulerWidget(QWidget *parent) : QWidget(parent)
{
    m_color = QColor("#ffff7f");
    m_start = 0;
    m_end = 100;
}

bool RulerWidget::set_range(double start, double end)
{
    if (start >= end) {
        return false;
    }

    m_start = start;
    m_end = end;

    update();

    return true;
}

void RulerWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    /* 设置背景 */
    painter.setBrush(m_color);
    painter.drawRect(this->rect());

    int markQty;
    int w = width();
    if (w >= 400) {
        markQty = 100;
    } else if ( w > 300 && w < 400 ) {
        markQty = 80;
    } else if ((w > 200) && (w < 300)) {
        markQty = 50;
    } else if ((w > 100) && ( w<200 )) {
        markQty = 40;
    } else {
        markQty = 20;
    }

    painter.setPen(QColor(Qt::black));

    double interval = (m_end - m_start) / markQty;
    double m_pixelPerUnit = width() / (m_end - m_start);

    qDebug()<<"pixelPerUnit"<<m_pixelPerUnit;

    if (interval < 0.01 ) {
        interval = 0.01;
    } else if ( 0.01 <=interval && interval < 0.1 ) {
        interval = ((int)(interval * 100)) / 100.0 ;
    } else if ( 0.1 <=interval  && interval < 1.0 ) {
        interval = ((int)(interval * 10)) / 10.0;
    } else if (interval >= 1.0 && interval <= 5.0 ) {
        interval = (int)  interval;
    } else if (interval > 5  && interval <= 10 ) {
        interval = 10;
    } else if (interval > 10 && interval < 50) {
        interval = 10 * (1 + (int)(interval / 10));
    } else if (interval >= 50 && interval <= 100) {
        interval = 100;
    } else if (interval > 100 && interval <= 200) {
        interval = 200;
    } else if (interval > 200) {
        interval = 100 * (1 + (int)(interval / 100));
    }
    markQty = (int)((m_end - m_start) / interval);

    qDebug()<<"markQty"<<markQty<<"s-e"<<m_start<<m_end;
    for(int i = 1; i <= markQty; ++i) {
        painter.drawLine((int)(i * interval * m_pixelPerUnit), 0, (int)(i * interval * m_pixelPerUnit), 3);
    }
    for(int i = 5; i < markQty; i += 10) {
        painter.drawLine((int)(i * interval * m_pixelPerUnit), 0, (int)(i * interval * m_pixelPerUnit), 6);
    }

    for(int i = 0; i <= markQty; i += 10) {
        painter.drawLine((int)(i * interval * m_pixelPerUnit), 0, (int)(i * interval * m_pixelPerUnit), 10);
        painter.drawText((int)(i * interval * m_pixelPerUnit)+2, 15, QString::number(i*interval+m_start));
    }
}
