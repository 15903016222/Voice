#include "tky_weld_widget.h"
#include <math.h>
#include "tky_weld_information.h"

namespace DplWeld {

TKYWeldWidget::TKYWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo) : BaseWeldWidget(weldInfo),
    m_pTKYWeldInfo(NULL)
{

}


void TKYWeldWidget::paint()
{
    m_pTKYWeldInfo = static_cast<TKYWeldInformation *> (m_weldInfo.data());

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

    painter.setPen(QColor(0, 0, 0));        /* 设置画笔颜色 */

    double rectangleBottom = this->height() * (DplWeld::TKYTopScale / 100.0) + m_pTKYWeldInfo->get_T1() * m_pTKYWeldInfo->get_height_scale();

    QRectF rect(QPointF(this->width() * (DplWeld::TKYLeftScale / 100.0), this->height() * (DplWeld::TKYTopScale / 100.0)),
                QPointF(this->width() * ((100.0 - DplWeld::TKYRightScale) / 100.0) - 1, rectangleBottom));

    painter.drawRect(rect);

    if(fabs(m_pTKYWeldInfo->get_angle() - 90.0) < 0.001) {
        /* 等于90度角 */
        paint_right_angle(rectangleBottom, painter);
    } else {
        /* 小于90或大于180度 */
        paint_other_angle(rectangleBottom, painter);
    }
}


void TKYWeldWidget::paint_symbol()
{

}


void TKYWeldWidget::paint_right_angle(double rectangleBottom, QPainter &painter)
{
    painter.setPen(Qt::DashDotLine);
    /* 四分之一T1，开始画中心线 */
    double center = this->width() / 2.0;
    double bottom = this->height() * (100.0 - DplWeld::TKYBottomScale) / 100.0;
    painter.drawLine(center, 3 * rectangleBottom / 4, center, bottom);

    double tmpT2    = m_pTKYWeldInfo->get_T2();
    double wScale   = m_pTKYWeldInfo->get_width_scale();
    double hScale   = m_pTKYWeldInfo->get_height_scale();

    painter.setPen(Qt::SolidLine);
    /* 垂直部分 */
    /* 左边 */
    painter.drawLine(QPointF(center - (tmpT2 / 2.0) * wScale, rectangleBottom),
                     QPointF(center - (tmpT2 / 2.0) * wScale, bottom));
    /* 右边 */
    painter.drawLine(QPointF(center + (tmpT2 / 2.0) * wScale, rectangleBottom),
                     QPointF(center + (tmpT2 / 2.0) * wScale, bottom));
    /* 底部 */
    painter.drawLine(QPointF(center - (tmpT2 / 2.0) * wScale, bottom),
                     QPointF(center + (tmpT2/ 2.0) * wScale, bottom));

    /* XY两边新 */

    painter.drawLine(QPointF(center - (m_pTKYWeldInfo->get_X1() + tmpT2 / 2.0) * wScale, rectangleBottom),
                     QPointF(center - (tmpT2 / 2.0) * m_pTKYWeldInfo->get_width_scale(), rectangleBottom + m_pTKYWeldInfo->get_Y1() * hScale));

    painter.drawLine(QPointF(center + (m_pTKYWeldInfo->get_X2() + tmpT2 / 2.0) * wScale, rectangleBottom),
                     QPointF(center + (tmpT2 / 2.0) * wScale, rectangleBottom + m_pTKYWeldInfo->get_Y2() * hScale));

    /* cl圆心 */
    QPointF circle(center, rectangleBottom);
    painter.drawEllipse(circle, 2, 2);

}


void TKYWeldWidget::paint_other_angle(double rectangleBottom, QPainter &painter)
{
    /*
     *___________K1___T2_____K2___X2_____
     *      |\ \  |  \ a   \   |  /|
     *    Y1| \ \ |   \     \  |  /|
     *      |___\\|    \     \ | / |Y2
     *        X1  \     \     \|/__|
     *             \     \     \ X2
     *              \     \     \
     *               \     \     \
     */

    double tmpT1    = m_pTKYWeldInfo->get_T1();
    double tmpT2    = m_pTKYWeldInfo->get_T2();
    double wScale   = m_pTKYWeldInfo->get_width_scale();
    double hScale   = m_pTKYWeldInfo->get_height_scale();

    double radianA = (M_PI / 180.0) *  m_pTKYWeldInfo->get_angle();

    painter.setPen(Qt::DashDotLine);
    /* 四分之一T1，开始画中心线 */

    /* 中心 */
    double center = this->width() / 2.0;
    double height = this->height() * (100.0 - DplWeld::TKYTopScale - DplWeld::TKYBottomScale) / 100.0;
    double bottom = this->height() * (100.0 - DplWeld::TKYBottomScale) / 100.0;
    double botttomWidth = (height / hScale - tmpT1) / tan(radianA);
    double bottomCenter = center + botttomWidth * wScale;

    /*
     * 相似三角形tanA相等
     * (height - m_info.T1 * m_hPixelPerUnit) / (botttomWidth * m_wPixelPerUnit) =  (m_info.T1 * m_hPixelPerUnit / 4.0) / x
     *
     **/

    double x = (tmpT1 * hScale / 4.0) / ((height - tmpT1 * hScale) / (botttomWidth * wScale));
    painter.drawLine(QPointF(center - x , rectangleBottom - tmpT1 * hScale / 4.0),
                     QPointF(bottomCenter, bottom));

    painter.setPen(Qt::SolidLine);
    /* cl圆心 */
    QPointF circle(center, rectangleBottom);
    painter.drawEllipse(circle, 2, 2);

    /* 两条竖线宽度 */
    double width = (tmpT2 / 2.0) / sin(radianA);

    painter.drawLine(QPointF(center - width * wScale, rectangleBottom),
                     QPointF(bottomCenter - width * wScale, bottom));

    painter.drawLine(QPointF(center + width * wScale, rectangleBottom),
                     QPointF(bottomCenter + width * wScale, bottom));

    /* 底部 */
    painter.drawLine(QPointF(bottomCenter - width * wScale, bottom),
                     QPointF(bottomCenter + width * wScale, bottom));

    /* X1,Y1 */
    /* tan(a) = Y1 / K1 */

    double K1 = m_pTKYWeldInfo->get_Y1() / tan(radianA);

    QPointF point1(center - (width + (m_pTKYWeldInfo->get_X1() - K1)) * wScale, rectangleBottom);
    QPointF point2(center - width * wScale + K1 * wScale, rectangleBottom + m_pTKYWeldInfo->get_Y1() * hScale);

    painter.drawLine(point1, point2);

    /* X2,Y2 */
    /* tan(a) = Y2 / K2 */

    double K2 = m_pTKYWeldInfo->get_Y2() / tan(radianA);

    point1.setX(center + (width + K2 + m_pTKYWeldInfo->get_X2()) * wScale);
    point1.setY(rectangleBottom);

    point2.setX(center + (width + K2) * wScale);
    point2.setY(rectangleBottom + m_pTKYWeldInfo->get_Y2() * hScale);

    painter.drawLine(point1, point2);

    if(m_pTKYWeldInfo->get_angle() < 90.0) {

        /* 计算最小角度 */
        calculate_min_angle();
        /* 计算最小的X1：当X1、Y1构成的直角三角形的一角等于m_info.angle时，X1为最小值 */
        emit min_X1(K1);
        /* 计算最大的Y1 ：*/
        emit max_Y1(m_pTKYWeldInfo->get_X1() * tan(radianA));
        emit min_X2(0.0);
    } else {
        emit min_X1(0.0);
        /* 计算最大角度 */
        calculate_max_angle();
        /* 计算最小的Y2： */
        emit min_X2(fabs(K2));
        /* 计算最大的Y2： */
        emit max_Y2(m_pTKYWeldInfo->get_X2() * tan((M_PI / 180.0) * (180.0 - m_pTKYWeldInfo->get_angle())));
    }
}


void TKYWeldWidget::calculate_min_angle()
{
    double minRadian = atan(m_pTKYWeldInfo->get_Y1() / m_pTKYWeldInfo->get_X1());
    double angle = (180.0 / M_PI) * minRadian;
    emit min_angle(angle);
}


void TKYWeldWidget::calculate_max_angle()
{
    double maxRadian = atan(m_pTKYWeldInfo->get_X2() / m_pTKYWeldInfo->get_Y2());
    double angle = (180.0 / M_PI) * maxRadian + 90.0;
    emit max_angle(angle);
}

}
