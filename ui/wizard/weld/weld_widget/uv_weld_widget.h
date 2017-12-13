#ifndef __DPL_WELD_UV_WELD_WIDGET_H__
#define __DPL_WELD_UV_WELD_WIDGET_H__

#include "u_weld_widget.h"

namespace DplWeld {

class UVWeldWidget : public UWeldWidget
{
public:
    UVWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);

protected:
    void paint_symbol();

    /**
     * @brief paint_bottom    绘画UV底部
     * @param bottom    焊缝最底部的Y坐标值
     * @param painter   绘画类
     * @param point4    U型弧线与W2宽的垂直线交点
     * @param point8    最左侧底部交点
     * @return          无
     */
    void paint_bottom(int bottom, QPainter &painter, QPointF &point4, QPointF &point7);
};

}

#endif // __DPL_WELD_UV_WELD_WIDGET_H__
