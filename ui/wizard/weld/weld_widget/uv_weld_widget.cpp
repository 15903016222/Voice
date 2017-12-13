#include "uv_weld_widget.h"
#include "uv_weld_information.h"

namespace DplWeld {

UVWeldWidget::UVWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo) : UWeldWidget(weldInfo)
{

}

void UVWeldWidget::paint_symbol()
{

}


void UVWeldWidget::paint_bottom(int bottom, QPainter &painter, QPointF &point4, QPointF &point7)
{
    /*
     *.point1___.point2_____cl
     * |        \          |
     * |         \         |
     * |          \.point3 |
     * |          *        |H1
     * |          *        |
     * |          *        |
     * |           *       |
     * |      point4.* ____|_
     * |             |  W2 |
     * |            .|     |_
     * |      point5/      |
     * |           /       |H2
     * |          /        |
     * |.________/.____W3__|_
     * point7     point6
     **/

    UVWeldInformation *pUVWeldInfo = static_cast<UVWeldInformation *> (m_weldInfo.data());

    /* point5 */
    QPointF point5(this->width() / 2 - pUVWeldInfo->get_W2() * pUVWeldInfo->get_width_scale(), bottom - pUVWeldInfo->get_H2() * pUVWeldInfo->get_height_scale());
    /* point6 */
    QPointF point6(this->width() / 2 - pUVWeldInfo->get_W3() * pUVWeldInfo->get_width_scale(), bottom);

    painter.drawLine(point4, point5);
    painter.drawLine(point5, point6);
    painter.drawLine(point6.x(), point6.y(), point7.x(), point7.y());

    painter.drawLine(this->width() - point4.x() - 1, point4.y(), this->width() - point5.x() - 1, point5.y());
    painter.drawLine(this->width() - point5.x() - 1, point5.y(), this->width() - point6.x() - 1, point6.y());
    painter.drawLine(this->width() - point6.x() - 1, point6.y(), this->width() - point7.x() - 1, point7.y());
}

}
