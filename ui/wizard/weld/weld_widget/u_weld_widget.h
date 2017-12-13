#ifndef __DPL_WELD_U_WELD_WIDGET_H__
#define __DPL_WELD_U_WELD_WIDGET_H__

#include "base_weld_widget.h"

namespace DplWeld {

class UWeldInformation;

class UWeldWidget : public BaseWeldWidget
{
public:
    UWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);

protected:
    void paint();
    void paint_symbol();

protected:
    /**
     * @brief calculate_max_W1   根据焊缝属性以及当前W1值进行UU最大W1计算
     * @param   W1数值
     * @param   point4
     * @return  无
     */
    void calculate_max_W1(double &tmpW1, QPointF &point4);

    /**
     * @brief calculate_max_W2   根据焊缝属性以及当前W1值进行UU最大W2计算
     * @param   W1数值
     * @return  无
     */
    void calculate_max_W2(double tmpW1);

    /**
     * @brief calculate_min_H1   根据焊缝属性进行UU最小H1计算
     * @return          无
     */
    void calculate_min_H1();

    /**
     * @brief calculate_min_R1   根据焊缝属性进行UU最小半径计算
     * @return          无
     */
    void calculate_min_R1();

    /**
     * @brief paint_bottom    绘画UU底部
     * @param bottom    焊缝最底部的Y坐标值
     * @param painter   绘画类
     * @param point4    U型弧线与W2宽的垂直线交点
     * @param point8    最左侧底部交点
     * @return          无
     */
    virtual void paint_bottom(int bottom, QPainter &painter, QPointF &point4, QPointF &point6);

private:

    /**
     * @brief paint_common    绘画U型公共部分
     * @param top       焊缝最顶部的Y坐标值
     * @param bottom    焊缝最底部的Y坐标值
     * @param painter   绘画类
     * @param point4    U型弧线与W2宽的垂直线交点
     * @param point6    最左侧底部交点
     * @return          无
     */
    void paint_common(int top, int bottom, QPainter &painter, QPointF &point4, QPointF &point6);
    UWeldInformation *m_pUWeldInfo;

};

}

#endif // __DPL_WELD_U_WELD_WIDGET_H__
