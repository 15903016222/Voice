#include "uu_weld_widget.h"

#include <math.h>
#include "uu_weld_information.h"

namespace DplWeld {


UUWeldWidget::UUWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo) : UWeldWidget(weldInfo),
    m_pUUWeldInfo(NULL)
{

}



void UUWeldWidget::paint_symbol()
{

}


void UUWeldWidget::paint_bottom(int bottom, QPainter &painter, QPointF &point4, QPointF &point8)
{
    m_pUUWeldInfo = static_cast<UUWeldInformation *> (m_weldInfo.data());

    double width1   = m_pUUWeldInfo->get_W1();
    double width2   = m_pUUWeldInfo->get_W2();
    double width3   = m_pUUWeldInfo->get_W3();
    double radius1  = m_pUUWeldInfo->get_R1();
    double radius2  = m_pUUWeldInfo->get_R2();
    double height1  = m_pUUWeldInfo->get_H1();
    double height2  = m_pUUWeldInfo->get_H2();
    double wScale   = m_pUUWeldInfo->get_width_scale();
    double hScale   = m_pUUWeldInfo->get_height_scale();

    if(height1 <= 0.000001
            || width1 <= 0.000001
            || radius1 <= 0.000001
            || height2 <= 0.000001
            || width3 <= 0.000001
            || radius2 <= 0.000001) {
        return;
    }

    /*
     *.point1___.point2_____cl
     * |        \          |
     * |         \         |
     * |          \.point3 |
     * |          *        |H3
     * |          *        |
     * |          *        |
     * |           *       |
     * |      point4.* ____|_
     * |             |     |
     * |             |     |
     * |             |     |
     * |             |     |
     * |      point5.|_W2__|_
     * |             *     |
     * |            *      |
     * |           *       |
     * |           *       |H3
     * |     point6.*      |
     * |           /       |
     * |          /        |
     * |._______./____W3___|_
     * point8   point7
     * point(8—1——2——3——4）已在父类UWeldingLine描绘
     * 当前只需要描绘point(8——7——6——5——4)这部分即可。
     **/

    QPointF point5(point4.x(), bottom - height2 * hScale);

    /* 求圆心坐标 */
    /*
     *Point5 __W2_          _
     *      \    |          |
     *       \   |          |
     *      R1\  |height    |
     *         \ |          |
     *          \|          |H2
     *          圆心         |
     *                      |
     *                     _|_bottom
     **/
    double height = sqrt(pow(radius2, 2) - pow(width2, 2));

    QPointF circle(this->width() / 2.0, bottom - (height2 - height) * hScale);
    painter.drawEllipse(circle, 5, 1);

    /* 圆心与W3构成的直角三角形 */
    /*
    *
    *     圆心
    *       /|
    *      / |
    *     /  |
    *lenA/   |
    *   /    |H2 - height
    *  /     |
    * /___W3_|_
    * A角度
    */
    /* 求弧度A以及斜边 */
    double radianA = atan((height2 - height) / width3);
    double lenA = sqrt(pow(width3, 2) + pow(height2 - height, 2));

    /* 圆心与R2，lenA构成直角三角形
     *
     *___R2__.圆心
     *|     /
     *|lenB/
     *|   /
     *|  /-lenA
     *| /
     *|/
     *B角度
     */
    /* 求弧度B及直角边lenB */
    double radianB = asin(radius2 / lenA);
    double lenB    = sqrt(pow(lenA, 2) - pow(radius2, 2));

    /*
    *
    *       point6(x,y)
    *         /|
    *        / |
    *       /  |
    *      /   |targetHeight
    *     /    |
    *    /     |
    *   /      |
    *  /       |
    *_/_A+B弧度_|
    *  targetWidth
    *A+B弧度最大值90度
    */
    double targetRadian = radianA + radianB;
    double targetHeight = sin(targetRadian) * lenB;
    double targetWidth  = cos(targetRadian) * lenB;

    /* point6 */
    QPointF point6(this->width() / 2.0  - (width3 - targetWidth) * wScale, bottom - targetHeight * hScale);

    /* point7 */
    QPointF point7(this->width() / 2.0 - width3 * wScale, bottom);
    /* 4 to 5 line */
    painter.drawLine(point4, point5);
    /* 8 to 7 line */
    painter.drawLine(point8, point7);
    /* 7 to 6 line */
    painter.drawLine(point7, point6);

    /* 对称线条描绘 */
    painter.drawLine(this->width() - point4.x(), point4.y(),
                     this->width() - point5.x() - 0.5, point5.y());
    painter.drawLine(this->width() - point8.x() - 0.5, point8.y(),
                     this->width() - point7.x() - 0.5, point7.y());
    painter.drawLine(this->width() - point7.x() - 0.5, point7.y(),
                     this->width() - point6.x(), point6.y());

    /* 求point6点的角度 */
    /*
     * point6
     * .————————|——
     *  \       |
     *   \      |
     *    \R2   |
     *     \    |
     *      \弧度|
     *       \  |
     *        \ |
     *         \|.圆心
     */
    double radianValue = ((this->width() / 2.0 - point6.x()) / wScale) / radius2;

//    double tmp1 = this->width() / 2.0 - point6.x();
//    double tmp2 = tmp1 / wScale;
//    double tmp3 = tmp2 / radius1;

    double anglePoint6;
    if(radianValue < 1.0) {
        anglePoint6 = asin(radianValue) * (180 / M_PI);
    } else {
        /* 成九十度角 */
        anglePoint6 = 90.0;
    }

    /* 求point5点的角度 */
    double anglePoint5 = asin(width2 / radius2) * (180 / M_PI);
    double circleW = 2 * radius2 * wScale;
    double circleH = 2 * radius2 * hScale;

    double beginX = circle.x() - radius2 * wScale;
    double beginY = circle.y() - radius2 * hScale;

    QRectF beginRect(beginX, beginY, circleW, circleH);
    painter.drawArc(beginRect,
                    (90.0 + anglePoint5) * 16,
                    (anglePoint6 - anglePoint5) * 16);

    painter.drawArc(beginRect,
                    (90.0 - anglePoint6) * 16,
                    (anglePoint6 - anglePoint5) * 16);

    /* 计算当前各值的最大值、最小值 */
    if(width2 < 0.000001) {
        return;
    }

    double tmpW1;
    calculate_max_W3(tmpW1, point6);
    calculate_max_W2(tmpW1);
    calculate_min_H2();
    calculate_min_R2();
}


void UUWeldWidget::calculate_max_W3(double &tmpW3, QPointF &point5)
{
    int bottom  = this->height() * (((int)TopScale + (int)WeldScale) / 100.0);

    /* W3最大值为W3与H2、circle圆心点构成直角三角形 */
    /*W3
     *    point5\point6重合
     *__________.|____W2___
     *          /\ ∠A     |
     *         /  \       |
     *        /    \      |
     *       /      \     |
     *      /      R2\    |H2
     *     /          \   |
     *    /            \  |
     *   /              \ |
     * _/_______W3____∠A_\|
     *
     */
     /* 求∠A角度弧度 */
    double tmpRadian = atan(m_pUUWeldInfo->get_H2() / m_pUUWeldInfo->get_W2());
    /* 根据∠A角度弧度、R2为直角边求出斜边W3最大值 */
    tmpW3 = m_pUUWeldInfo->get_R2() / cos(tmpRadian);

    /*求W1最大值
     * ___W1-W2___W2__
     * |\    A |     |
     * | \     |     |
     * |  \    |     |
     * |   \   |     |H1
     * |    \  |    /|
     * |     \ | R/  |K
     * |______\|/____|
     *            W2
     *
     * R2与W2组成的直角三角形可得出K
     * （W3-W2）与H2构成直角三角形，其中斜边与H2的角度Ă与
     * R2与W2构成的角度ß相等
     * 故得1公式: (W3-W2) / H2 = K / W2
     *    2公式:  K = √(R2^2 - W2^2)
     *
     * 上图为求W1最大值示意图，与求W3成对称图形。
     *
     * 求W3最大值
     * ___________W2__
     * |      /|\ß   |
     * |     /Ă|  \  |K
     * |    /  | R2 \|
     * |   /   |     |H2
     * |  /    |     |
     * | /     |     |
     * |/______|_____|
     *   W3-W2    W2
     *
     * R2与W2组成的直角三角形可得出K
     * （W3-W2）与H2构成直角三角形，其中斜边与H2的角度Ă与
     * R2与W2构成的角度ß相等
     * 故得1公式: (W3-W2) / H2 = K / W2
     *    2公式:  K = √(R2^2 - W2^2)
     *
     */
    double height = sqrt(pow(m_pUUWeldInfo->get_R2(), 2) - pow(m_pUUWeldInfo->get_W2(), 2));
    double antherMaxW3 = (height * m_pUUWeldInfo->get_H2()) / m_pUUWeldInfo->get_W2() + m_pUUWeldInfo->get_W2();

    /* 根据求出的tmpW3值，求出当W3最大值时，所求的point6坐标是否大于point5，
     * 若大于，则使用antherMaxW3值作为最大值 */
    /* 求最大值时，point6的值 */
    /* 圆心与W3构成的直角三角形 */
    /*        __________
     *       |        | |K = height
     *       |.圆心____|_|
     *      /|        |
     *     / |        |
     *    /  |        |  H2 - height
     *   /   |        |
     * _/_∠A_|________|_
     *    W3
     *
     */
    /* 求∠A弧度以及斜边 */

    double tmpradianA = atan((m_pUUWeldInfo->get_H2() - height) / tmpW3);
    double tmplenA = sqrt(pow(tmpW3, 2) + pow(m_pUUWeldInfo->get_H2() - height, 2));

    /* 圆心与相切点、W3点构成直角三角形 */
    /*
     * ___R2_.圆心
     * |    /
     * |   /
     * |B‘/
     * | /
     * |/
     * W3
     */
    /* 求弧度B及直角边 */
    double tmpradianB = asin(m_pUUWeldInfo->get_R2() / tmplenA);
    double tmplenB    = sqrt(pow(tmplenA, 2) - pow(m_pUUWeldInfo->get_R2(), 2));

    /*
    *
    *       point6(x,y)
    *         /|
    *        / |
    *       /  |
    *      /   |targetHeight
    *     /    |
    *    /     |
    *   /      |
    *  /       |
    *_/_A+B弧度_|
    *  targetWidth
    *A+B弧度最大值90度
    */
    double tmpTargetRadian = tmpradianA + tmpradianB;
    double tmpTargetHeight = sin(tmpTargetRadian) * tmplenB;
    double tmpTtargetWidth  = cos(tmpTargetRadian) * tmplenB;

    QPointF tmppoint6(this->width() / 2.0 - (m_pUUWeldInfo->get_W3() - tmpTtargetWidth) * m_pUUWeldInfo->get_width_scale(),
                      bottom - tmpTargetHeight * m_pUUWeldInfo->get_height_scale());

    if(tmppoint6.x() > point5.x() || tmppoint6.y() < point5.y()) {

        if(tmpW3 > antherMaxW3) {
            tmpW3 = antherMaxW3;
        }
    }

    if(m_pUUWeldInfo->get_W3() < tmpW3) {
        emit max_W3(tmpW3);
    } else {
        qDebug() << "[" << __FUNCTION__ << "]" << " max W3 bigger than m_info.W3, so not change maximun.";
    }
}


void UUWeldWidget::calculate_max_W2(double tmpW3)
{
    /* 当W3为最大值时，W2当前值也为最大值，不可改变W2 */
    /* 相等 */
    if(fabs(tmpW3 - m_pUUWeldInfo->get_W3()) < EQ_VALUE) {
        emit max_W2(m_pUUWeldInfo->get_W2());
    } else {

        double radianAForBaseUWeld = atan(m_pUUWeldInfo->get_H1() / (m_pUUWeldInfo->get_W1() - m_pUUWeldInfo->get_W2()));
        double tmpMaxW2ForBaseUWeld = m_pUUWeldInfo->get_R1() * sin(radianAForBaseUWeld);

        double radianA = atan(m_pUUWeldInfo->get_H2() / (m_pUUWeldInfo->get_W3() - m_pUUWeldInfo->get_W2()));
        double tmpMaxW2 = m_pUUWeldInfo->get_R2() * sin(radianA);

        if(tmpMaxW2ForBaseUWeld < tmpMaxW2) {
            qDebug() << "[" << __FUNCTION__ << "]" << " max W2 for UU bigger than max W2 for base U, so ingore it.";
            return;
        }

        if(((m_pUUWeldInfo->get_W3() - 0.01) > tmpMaxW2) && (tmpMaxW2 > m_pUUWeldInfo->get_W2())) {
            emit max_W2(tmpMaxW2);
        }
    }
}


void UUWeldWidget::calculate_min_H2()
{
    /*
     * 求H2最小值
     * ___________W2__
     * |      /|\ß   |
     * |     /Ă|  \  |K
     * |    /  | R2 \|
     * |  C/   |     |H2
     * |  /    |     |
     * | /     |     |
     * |/______|_____|
     *   W3-W2    W2
     *上图三角形((W3-W2), H2, 斜边C)与（R2，W2，K）构成相似三角形
     * 故得出：W3-W2/sqrt(R2^2-W2^2) = H2/W2
     */

    /* 若R2等于W2，则不进行计算 */
    if(fabs(m_pUUWeldInfo->get_R2() - m_pUUWeldInfo->get_W2()) < 0.000001) {
        return;
    }

    double tmpminH2 = (m_pUUWeldInfo->get_W2() * (m_pUUWeldInfo->get_W3() - m_pUUWeldInfo->get_W2())) /
                        sqrt(pow(m_pUUWeldInfo->get_R2(), 2) - pow(m_pUUWeldInfo->get_W2(), 2));

    emit min_H2(tmpminH2);
}


void UUWeldWidget::calculate_min_R2()
{
    /* 最小值R2 */
    /*
     * 求R2最小值
     * ___________W2__
     * |      /|\    |
     * |     / |  \ ß|K
     * |    /  | R2 \|
     * |  C/   |     |H2
     * |  /    |     |
     * | /     |     |
     * |/Ă_____|_____|
     *   W3-W2    W2
     *
     *上图三角形((W3-W2), H2, 斜边C)与（K，W2，R2）构成相似三角形
     * 故得出：Ă弧度 = atan(H2 / (W3 - W2))弧度 = R2与K的ß弧度
     * sin(A弧度) = W2 / R2
     *
     */

    double radianA = atan(m_pUUWeldInfo->get_H2() / (m_pUUWeldInfo->get_W3() - m_pUUWeldInfo->get_W2()));
    double targetR2 = m_pUUWeldInfo->get_W2() / sin(radianA);
    emit min_R2(targetR2);
}

}
