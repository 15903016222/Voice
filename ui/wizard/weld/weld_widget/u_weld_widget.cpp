#include "u_weld_widget.h"
#include <math.h>
#include "u_weld_information.h"


namespace DplWeld {

UWeldWidget::UWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo) : BaseWeldWidget(weldInfo),
    m_pUWeldInfo(NULL)
{

}


void UWeldWidget::paint()
{
    DplWeld::BaseWeldWidget::paint();

    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));        /* 设置画笔颜色 */

    int top     = this->height() * ((int)TopScale / 100.0);
    int bottom  = this->height() * (((int)TopScale + (int)WeldScale) / 100.0);

    /*
     *.point1___.point2_____cl
     * |        \          |
     * |         \         |
     * |          \.point3 |
     * |          *        |
     * |          *        |
     * |          *        |
     * |           *       |
     * |      point4.* ____|
     * |             |     |
     * |             |     |
     * |             |     |
     * |.____________|.____|
     * point6       point5
     **/
    QPointF point4;
    QPointF point6;

    m_pUWeldInfo = static_cast<UWeldInformation *> (m_weldInfo.data());

    paint_common(top, bottom, painter, point4, point6);

    paint_bottom(bottom, painter, point4, point6);
}


void UWeldWidget::paint_symbol()
{

}


void UWeldWidget::paint_bottom(int bottom, QPainter &painter, QPointF &point4, QPointF &point6)
{
    if(m_pUWeldInfo->get_H1() <= 0.000001
            || m_pUWeldInfo->get_W1() <= 0.000001
            || m_pUWeldInfo->get_R1() <= 0.000001 ) {
        return;
    }

    /* point5 */
    QPointF point5(this->width() / 2 - m_pUWeldInfo->get_W2() * m_pUWeldInfo->get_width_scale(), bottom);

    /* 4 to 5 line */
    painter.drawLine(point4, point5);
    /* 5 to 6 line */
    painter.drawLine(point5, point6);

    painter.drawLine(this->width() - point4.x() - 0.5, point4.y(),
                     this->width() - point5.x() - 0.5, point5.y());
    painter.drawLine(this->width() - point5.x() - 0.5, point5.y(),
                     this->width() - point6.x() - 0.5, point6.y());
}


void UWeldWidget::paint_common(int top, int bottom, QPainter &painter, QPointF &point4, QPointF &point6)
{
    double width1   = m_pUWeldInfo->get_W1();
    double width2   = m_pUWeldInfo->get_W2();
    double height1  = m_pUWeldInfo->get_H1();
    double radius1  = m_pUWeldInfo->get_R1();
    double wScale   = m_pUWeldInfo->get_width_scale();
    double hScale   = m_pUWeldInfo->get_height_scale();

    if(height1 <= 0.000001 || width1 <= 0.000001 || radius1 <= 0.000001 ) {
        return;
    }

    /*
     *.point1___.point2_____cl
     * |        \          |
     * |         \         |
     * |          \.point3 |
     * |          *        |
     * |          *        |
     * |          *        |
     * |           *       |
     * |      point4.* ____|
     * |             |     |
     * |             |     |
     * |             |     |
     * |.____________|.____|
     * point6       point5
     **/

    /* point1 */
    QPointF point1(0, top);

    /* point2 */
    QPointF point2(this->width() / 2.0 - width1 * wScale, top);

    /* point3 */
    /* 求圆心坐标 */

    double height = sqrt(pow(radius1, 2) - pow(width2, 2));
    QPointF circle(this->width() / 2.0, top + (height1 - height) * hScale);
    painter.drawEllipse(circle, 5, 1);

    /* 圆心与W1构成的直角三角形 */
    /*
    *___W1__
    * \@   |
    *  \   |
    *   \  |
    *    \ |
    *     \|圆心
    */
    /* 求弧度@以及斜边 */
    double radianA = atan((height1 - height) / width1);
    double lenA = sqrt(pow(width1, 2) + pow(height1 - height, 2));

    /* 圆心与相切点、W1点构成直角三角形 */
    /*
    *W1
    *|\
    *| \
    *|B'\
    *|   \
    *|____\圆心
    *  R1
    */
    /* 求弧度B及直角边 */
    double radianB = asin(radius1 / lenA);
    double lenB    = sqrt(pow(lenA, 2) - pow(radius1, 2));

    /*
    * targetWidth
    *_________
    * \A+B弧度|
    *  \     |
    *   \    |targetHeight
    *    \   |
    * lenB\  |
    *      \ |
    *       \|
    *       point3(x,y)
    */
    double targetRadian = radianA + radianB;
    double targetHeight = sin(targetRadian) * lenB;
    double targetWidth  = cos(targetRadian) * lenB;

    QPointF point3(this->width() / 2.0 - (width1 - targetWidth) * wScale,
                   top + targetHeight * hScale);

    /* point4 */
    point4.setX(this->width() / 2.0 - width2 * wScale);
    point4.setY(top + height1 * hScale);

    /* point5 */
    QPointF point5(this->width() / 2.0 - width2 * wScale, bottom);

    /* point6 */
    point6.setX(0);
    point6.setY(bottom);

    /* 1 to 2 line */
    painter.drawLine(point1, point2);
    /* 2 to 3 line */
    painter.drawLine(point2, point3);
    /* 6 to 1 line */
    painter.drawLine(point6, point1);

    /* 对称线条描绘 */
    painter.drawLine(this->width() - point1.x(), point1.y(),
                     this->width() - point2.x() + 0.5, point2.y());
    painter.drawLine(this->width() - point2.x() + 0.5, point2.y(),
                     this->width() - point3.x() + 0.5, point3.y());
    painter.drawLine(this->width() - point6.x() + 0.5, point6.y(),
                     this->width() - point1.x(), point1.y());


    /* 求point3点的角度 */
    double radianValue = ((this->width() / 2.0 - point3.x()) / wScale) / radius1;
//    double tmp1 = this->width() / 2.0 - point3.x();
//    double tmp2 = tmp1 / wScale;
//    double tmp3 = tmp2 / radius1;


    double anglePoint3;
    if(radianValue < 1.0) {
        anglePoint3 = asin(radianValue) * (180 / M_PI);
    } else {
        /* 成九十度角 */
        anglePoint3 = 90.0;
    }

    /* 求point4点的角度 */
    double anglePoint4 = asin(width2 / radius1) * (180 / M_PI);
    double circleW = 2 * radius1 * wScale;
    double circleH = 2 * radius1 * hScale;

    double beginX = circle.x() - radius1 * wScale;
    double beginY = circle.y() - radius1 * hScale;

    QRectF beginRect(beginX, beginY, circleW, circleH);

    painter.drawArc(beginRect,
                    (180.0 + (90.0 - anglePoint3)) * 16,
                    (anglePoint3 - anglePoint4) * 16);

    painter.drawArc(beginRect,
                    (270.0 + anglePoint4) * 16,
                    (anglePoint3 - anglePoint4) * 16);

    /* 计算当前各值的最大值、最小值 */
    if(width2 < 0.000001) {
        return;
    }

    double tmpW1;

    calculate_max_W1(tmpW1, point4);
    calculate_max_W2(tmpW1);
    calculate_min_H1();
    calculate_min_R1();
}


void UWeldWidget::calculate_max_W1(double &tmpW1, QPointF &point4)
{
    double width1   = m_pUWeldInfo->get_W1();
    double width2   = m_pUWeldInfo->get_W2();
    double height1  = m_pUWeldInfo->get_H1();
    double radius1  = m_pUWeldInfo->get_R1();
    double wScale   = m_pUWeldInfo->get_width_scale();
    double hScale   = m_pUWeldInfo->get_height_scale();

    int top     = this->height() * ((int)TopScale / 100.0);

    /* W1最大值为W1与H1、circle圆心点构成直角三角形 */
    /*W1
     * ___W1___
     * |    A /
     * |H1   /
     * |    /
     * |   /
     * |  /
     * | /
     * |/
     */
     /* 求A角度弧度 */

    double tmpRadian = atan(height1 / width2);
    /* 根据A角度弧度、R1为直角边求出斜边W1最大值 */
    tmpW1 = radius1 / cos(tmpRadian);

    /*W1
     * ___W1-W2___W2__
     * |\    A |     |
     * | \     |     |
     * |  \    |     |
     * |   \   |     |H1
     * |    \  |    /|
     * |     \ | R/  |K
     * |______\|/____|
     *            W2
     * R与W2组成的直角三角形可得出K
     * （W1-W2）与H1构成直角三角形，其中斜边与H1的角度Ă与
     * R与W2构成的角度ß相等
     * 故得1公式: (W1-W2) / H1 = K / W2
     *    2公式:  K = √(R^2 - W2^2)
     */
    double height = sqrt(pow(radius1, 2) - pow(width2, 2));
    double antherMaxW1 = (height * height1) / width2 + width2;

    /* 根据求出的tmpW1值，求出当W1最大值时，所求的point3坐标是否大于point4，
     * 若大于，则使用antherMaxW1值作为最大值 */

    /* 求最大值时，point3的值 */

    /* 圆心与W1构成的直角三角形 */
    /*
    *___W1__
    * \@   |
    *  \   |
    *   \  |
    *    \ |
    *     \|圆心
    */
    /* 求弧度@以及斜边 */

    double tmpradianA = atan((height1 - height) / tmpW1);
    double tmplenA = sqrt(pow(tmpW1, 2) + pow(height1 - height, 2));

    /* 圆心与相切点、W1点构成直角三角形 */
    /*
    *W1
    *|\
    *| \
    *|B'\
    *|   \
    *|____\圆心
    *  R1
    */
    /* 求弧度B及直角边 */
    double tmpradianB = asin(radius1 / tmplenA);
    double tmplenB    = sqrt(pow(tmplenA, 2) - pow(radius1, 2));

    /*
    * tmptargetWidth
    *_________
    * \A+B弧度|
    *  \     |
    *   \    |tmptargetHeight
    *    \   |
    * lenB\  |
    *      \ |
    *       \|
    *       tmppoint3(x,y)
    */
    double tmpTargetRadian = tmpradianA + tmpradianB;
    double tmpTargetHeight = sin(tmpTargetRadian) * tmplenB;
    double tmpTtargetWidth  = cos(tmpTargetRadian) * tmplenB;

    QPointF tmppoint3(this->width() / 2  - (width1 - tmpTtargetWidth) * wScale,
                      top + tmpTargetHeight * hScale);
    if(tmppoint3.x() > point4.x() || tmppoint3.y() > point4.y()) {

        if(tmpW1 > antherMaxW1) {
            tmpW1 = antherMaxW1;
        }
    }


    if(width1 < tmpW1) {
        emit max_W1(tmpW1);
    } else {
        qDebug() << "[" << __FUNCTION__ << "]" << " max W1 bigger than m_info.W1, so not change maximun.";
    }
}


void UWeldWidget::calculate_max_W2(double tmpW1)
{
    /* 当W1为最大值时，W2当前值也为最大值，不可改变W2 */
    if(fabs(tmpW1 - m_pUWeldInfo->get_W1()) < EQ_VALUE) {   /* 相等 */
        emit max_W2(m_pUWeldInfo->get_W2());
    } else {
        double radianA = atan(m_pUWeldInfo->get_H1() / (m_pUWeldInfo->get_W1() - m_pUWeldInfo->get_W2()));
        double tmpMaxW2 = m_pUWeldInfo->get_R1() * sin(radianA);

        if(((m_pUWeldInfo->get_W1() - 0.01) > tmpMaxW2)
                && (tmpMaxW2 > m_pUWeldInfo->get_W2())) {
            emit max_W2(tmpMaxW2);
        }
    }
}


void UWeldWidget::calculate_min_H1()
{
    /*
     * 求H1最小值
     *
     * ___W1-W2___W2__
     * |\    A |     |
     * | \     |     |
     * |  \    |     |
     * |  C\   |     |H1
     * |    \  |    /|
     * |     \ | R/  |K
     * |______\|/____|
     *            W2
     *上图三角形((W1-W2), H1, 斜边C)与（R，W2，K）构成相似三角形
     * 故得出：W1-W2/sqrt(R^2-W2^2) = H1/W2
     */

    /* 若R1等于W2，则不进行计算 */
    if(fabs(m_pUWeldInfo->get_R1() - m_pUWeldInfo->get_W2()) < 0.000001) {
        return;
    }

    double tmpminH1 = (m_pUWeldInfo->get_W2() * (m_pUWeldInfo->get_W1() - m_pUWeldInfo->get_W2())) /
                        sqrt(pow(m_pUWeldInfo->get_R1(), 2) - pow(m_pUWeldInfo->get_W2(), 2));
    emit min_H1(tmpminH1);
}


void UWeldWidget::calculate_min_R1()
{
    /* 最小值R1 */
    /*
     * 求R1最小值
     *
     * ___W1-W2___W2__
     * |\A     |     |
     * | \     |     |
     * |  \    |     |
     * |  C\   |     |H1
     * |    \  |    /|
     * |     \ |R1/  |K
     * |______\|/____|
     *            W2
     *上图三角形((W1-W2), H1, 斜边C)与（R1，W2，K）构成相似三角形
     * 故得出：A弧度 = atan(H1 / (W1 - W2))弧度 = R1与K的弧度
     * sin(A弧度) = W2 / R1
     *
     */

    double radianA = atan(m_pUWeldInfo->get_H1() / (m_pUWeldInfo->get_W1() - m_pUWeldInfo->get_W2()));
    double targetR1 = m_pUWeldInfo->get_W2() / sin(radianA);

    emit min_R1(targetR1);
}

}
