#ifndef __DPL_WELD_TKY_WELD_WIDGET_H__
#define __DPL_WELD_TKY_WELD_WIDGET_H__

#include "base_weld_widget.h"

namespace DplWeld {

class TKYWeldInformation;

class TKYWeldWidget : public BaseWeldWidget
{
public:
    TKYWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);

protected:
    void paint();
    void paint_symbol();

    /**
     * @brief paintRightAngle   当a等于90度时，根据焊缝属性进行TKY型焊缝下半部显示处理
     * @param rectangleBottom    TKY焊缝上半部矩形的底部Y坐标
     * @param painter   绘画类
     * @return          无
     */
    void paint_right_angle(double rectangleBottom, QPainter &painter);

    /**
     * @brief paintOtherAngle   当a不等于90度时，根据焊缝属性进行TKY型焊缝下半部显示处理
     * @param rectangleBottom    TKY焊缝上半部矩形的底部Y坐标
     * @param painter   绘画类
     * @return          无
     */
    void paint_other_angle(double rectangleBottom, QPainter &painter);

    /**
     * @brief calculateMinAngle   根据焊缝属性进行TKY最小角度计算
     * @return          无
     */
    void calculate_min_angle();

    /**
     * @brief calculateMinAngle   根据焊缝属性进行TKY最大角度计算
     * @return          无
     */
    void calculate_max_angle();

    TKYWeldInformation *m_pTKYWeldInfo;
};

}

#endif // __DPL_WELD_TKY_WELD_WIDGET_H__
