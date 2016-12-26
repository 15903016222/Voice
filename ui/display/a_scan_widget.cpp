#include "a_scan_widget.h"

#include <QPainter>
#include <QDebug>

AscanWidget::AscanWidget(QWidget *parent)
    : QWidget(parent)
{
    m_color = QColor("#ffff7f");
}

void AscanWidget::show(const QByteArray &b)
{
    if (b.size() == 0) {
        return;
    }
    m_beam.setRawData(b.constData(), b.size());
    update();
}

void AscanWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    painter.setBrush(Qt::black);
    painter.drawRect(this->rect());

    painter.setPen(m_color);

    painter.translate(0, height());

    QTransform form;
    form = painter.transform();
    form.rotate(180, Qt::XAxis);
    painter.setTransform(form);

    double yaxis = height()/255.0;

    double xaxis2 = 1;
    double xaxis1 = 1;
    int num = 0;
    if (m_beam.size() < width()) {
        num = m_beam.size();
        xaxis1 = width()/1.0/m_beam.size();
    } else {
        num = width();
        xaxis2 = m_beam.size()/1.0/width();
    }

    for (int i = 0; i < num-1; ++i) {
        painter.drawLine(i*xaxis1,
                         (int)((quint8)(m_beam.at((int)(i*xaxis2)))*yaxis) + 1,
                         (i+1)*xaxis1,
                         (int)((quint8)(m_beam.at((int)((i+1)*xaxis2)))*yaxis)+1);
    }
}
