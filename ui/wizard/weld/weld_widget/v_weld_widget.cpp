#include "v_weld_widget.h"
#include "v_weld_information.h"

namespace DplWeld {


VWeldWidget::VWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo):BaseWeldWidget(weldInfo)
{

}

void VWeldWidget::paint()
{
    DplWeld::BaseWeldWidget::paint();

    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));        /* 设置画笔颜色 */

    int top     = this->height() * ((int)TopScale / 100.0);
    int bottom  = this->height() * (((int)TopScale + (int)WeldScale) / 100.0);

    VWeldInformation *tmpInfo = static_cast<VWeldInformation *> (m_weldInfo.data());

    /* point1 */
    QPoint point1(0, top);
    /* point2 */
    QPoint point2(this->width() / 2 - tmpInfo->get_W1() * tmpInfo->get_width_scale(), top);
    /* point3 */
    QPoint point3(this->width() / 2 - tmpInfo->get_W2() * tmpInfo->get_width_scale(),
                  top + tmpInfo->get_H1() * tmpInfo->get_height_scale());
    /* point4 */
    QPoint point4(this->width() / 2 - tmpInfo->get_W2() * tmpInfo->get_width_scale(), bottom);
    /* point5 */
    QPoint point5(0, bottom);

    QPolygon polygon;
    polygon.setPoints(5,
                      point1.x(), point1.y(),
                      point2.x(), point2.y(),
                      point3.x(), point3.y(),
                      point4.x(), point4.y(),
                      point5.x(), point5.y());
    painter.drawConvexPolygon(polygon);


    polygon.setPoints(5,
                      this->width() - point1.x(), point1.y(),
                      this->width() - point2.x() - 1, point2.y(),
                      this->width() - point3.x(), point3.y(),
                      this->width() - point4.x() - 1, point4.y(),
                      this->width() - point5.x() - 1, point5.y());
    painter.drawConvexPolygon(polygon);

}

void VWeldWidget::paint_symbol()
{

}

}
