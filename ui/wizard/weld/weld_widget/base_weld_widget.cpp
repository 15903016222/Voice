#include "base_weld_widget.h"

namespace DplWeld {

BaseWeldWidget::BaseWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo, QWidget *parent) : QWidget(parent),
  m_weldInfo(weldInfo)
{

}

void BaseWeldWidget::update_weld_information(QSharedPointer<BaseWeldInformation> &weldInfo)
{
    m_weldInfo = weldInfo;
    repaint();
}

int BaseWeldWidget::get_weld_type()
{
    return m_weldInfo->get_type();
}

void BaseWeldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paint();
    paint_symbol();

}

void BaseWeldWidget::paint()
{
    QPainter painter(this);
    /* 设置画笔颜色 */
    painter.setPen(QColor(0, 160, 230));

    QLine lineTop(QPoint(0, 0), QPoint(this->width(), 0));
    QLine lineBottom(QPoint(0, this->height() - 1), QPoint(this->width() - 1, this->height() - 1));
    QLine lineLeft(QPoint(0, 0), QPoint(0, this->height()));
    QLine lineRight(QPoint(this->width() - 1, 0), QPoint(this->width() - 1, this->height() - 1));

    painter.drawLine(lineTop);
    painter.drawLine(lineBottom);
    painter.drawLine(lineLeft);
    painter.drawLine(lineRight);

    painter.setPen(Qt::DashDotLine);
    painter.drawLine(this->width()/2, 0, this->width()/2, this->height());

}

}
