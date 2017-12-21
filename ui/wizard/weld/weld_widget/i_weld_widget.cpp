#include "i_weld_widget.h"
#include "i_weld_information.h"

namespace DplWeld {


IWeldWidget::IWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo):BaseWeldWidget(weldInfo)
{

}

IWeldWidget::~IWeldWidget()
{
}

void IWeldWidget::paint()
{
    DplWeld::BaseWeldWidget::paint();

    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));        /* 设置画笔颜色 */

    int top     = this->height() * ((int)DplWeld::TopScale / 100.0);
    int bottom  = this->height() * (((int)DplWeld::TopScale + (int)DplWeld::WeldScale) / 100.0);

    IWeldInformation *tmpInfo = static_cast<IWeldInformation *> (m_weldInfo.data());

    int topLeft  = this->width()/2 - tmpInfo->get_W1() * tmpInfo->get_width_scale();
    int topRight = this->width()/2 + tmpInfo->get_W1() * tmpInfo->get_width_scale();

    if(topLeft >= 0 && topRight <= this->width()) {

        painter.drawRect(0, top, topLeft, bottom - top);

        QPolygon polygon;
        polygon.setPoints(4,
                          topRight, top,
                          this->width() - 1, top,
                          this->width() - 1, bottom,
                          topRight, bottom);

        painter.drawConvexPolygon(polygon);
    }
}

void IWeldWidget::paint_symbol()
{

}

}

