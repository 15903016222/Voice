#include "vv_weld_widget.h"
#include "vv_weld_information.h"
namespace DplWeld {

VVWeldWidget::VVWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo) : BaseWeldWidget(weldInfo)
{

}

void VVWeldWidget::paint()
{
    qDebug() << "[VVWeldWidget::paint]";

    DplWeld::BaseWeldWidget::paint();

    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));        /* 设置画笔颜色 */

    int top     = this->height() * ((int)TopScale / 100.0);
    int bottom  = this->height() * (((int)TopScale + (int)WeldScale) / 100.0);

    VVWeldInformation *tmpInfo = static_cast<VVWeldInformation *> (m_weldInfo.data());

    /* point1 */
    QPoint point1(0, top);
    /* point2 */
    QPoint point2(this->width() / 2 - tmpInfo->get_W1() * tmpInfo->get_width_scale(), top);
    /* point3 */
    QPoint point3(this->width() / 2 - tmpInfo->get_W2() * tmpInfo->get_width_scale(), top + tmpInfo->get_H1() * tmpInfo->get_height_scale());
    /* point4 */
    QPoint point4(this->width() / 2 - tmpInfo->get_W2() * tmpInfo->get_width_scale(), bottom - tmpInfo->get_H2() * tmpInfo->get_height_scale());
    /* point5 */
    QPoint point5(this->width() / 2 - tmpInfo->get_W3() * tmpInfo->get_width_scale(), bottom);
    /* point6 */
    QPoint point6(0, bottom);

    QPolygon polygon;
    polygon.setPoints(6,
                      point1.x(), point1.y(),
                      point2.x(), point2.y(),
                      point3.x(), point3.y(),
                      point4.x(), point4.y(),
                      point5.x(), point5.y(),
                      point6.x(), point6.y());
    painter.drawConvexPolygon(polygon);


    polygon.setPoints(6,
                      this->width() - point1.x(), point1.y(),
                      this->width() - point2.x() - 1, point2.y(),
                      this->width() - point3.x(), point3.y(),
                      this->width() - point4.x() - 1, point4.y(),
                      this->width() - point5.x() - 1, point5.y(),
                      this->width() - point6.x() - 1, point6.y());
    painter.drawConvexPolygon(polygon);
}


void VVWeldWidget::paint_symbol()
{

}


}
