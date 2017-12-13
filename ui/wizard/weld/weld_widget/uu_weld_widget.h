#ifndef __DPL_WELD_UU_WELD_WIDGET_H__
#define __DPL_WELD_UU_WELD_WIDGET_H__

#include "u_weld_widget.h"

namespace DplWeld {

class UUWeldInformation;

class UUWeldWidget : public UWeldWidget
{
public:
    UUWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);

protected:

    void paint_symbol();
    /**
     * @brief paintBottom    绘画UU底部
     * @param bottom    焊缝最底部的Y坐标值
     * @param painter   绘画类
     * @param point4    U型弧线与W2宽的垂直线交点
     * @param point8    最左侧底部交点
     * @return          无
     */
    virtual void paint_bottom(int bottom, QPainter &painter, QPointF &point4, QPointF &point8);

private:

    /**
     * @brief calculate_max_W3   根据焊缝属性进行UU最小W3计算
     * @param tmpW3     保存最大的W3值
     * @param point5    point5
     * @return          无
     */
    void calculate_max_W3(double &tmpW3, QPointF &point5);

    /**
     * @brief calculate_max_W2   根据焊缝属性进行UU最大W2计算
     * @param tmpW3     最大的W3值
     * @return          无
     */
    void calculate_max_W2(double tmpW3);

    /**
     * @brief calculate_min_H2   根据焊缝属性进行UU最小H2计算
     * @return          无
     */
    void calculate_min_H2();

    /**
     * @brief calculateMinR2UU   根据焊缝属性进行UU最小R2计算
     * @return          无
     */
    void calculate_min_R2();

    UUWeldInformation *m_pUUWeldInfo;
};

}

#endif // __DPL_WELD_UU_WELD_WIDGET_H__
