#include "battery_label.h"
#include <QPainter>

#include <QDebug>

BatteryLabel::BatteryLabel(QWidget *parent)
    : QLabel(parent),
      m_status(Mcu::BATTERY_NO_WORK),
      m_quantity(0)
{

}

void BatteryLabel::set_status(Mcu::BatteryStatus status)
{
    m_status = status;
    QString image;
    switch (m_status) {
    case Mcu::DISCHARGE:
        image.sprintf(":/file/resources/battery/b%d.png", m_quantity/10);
        break;
    case Mcu::CHARGE:
        image.sprintf(":/file/resources/battery/bc%d.png", m_quantity/10);
        break;
    case Mcu::BATTERY_FULL:
        image.append(":/file/resources/battery/b10.png");
        break;
    default:
        image.append(":/file/resources/battery/b_error.png");
        break;
    }
    setPixmap(QPixmap(image).scaled(40, 15));
}

void BatteryLabel::set_quantity(int value)
{
    m_quantity = value;
    update();
}

void BatteryLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);

    QFont font = painter.font();
    font.setPixelSize(8);
    painter.setFont(font);
    painter.setPen(Qt::SolidLine);
    painter.setPen(QColor(Qt::green));

    QRectF ff(0, 0, width(), height());
    painter.drawText(ff, Qt::AlignCenter|Qt::AlignHCenter, QString::number(m_quantity).append("%"));
}
