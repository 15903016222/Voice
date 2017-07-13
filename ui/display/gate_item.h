/**
 * @file gate_item.h
 * @brief 闸门项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#ifndef __GATE_ITEM_H__
#define __GATE_ITEM_H__

#include <QGraphicsItem>

class GateItem : public QGraphicsItem
{
public:
    GateItem(const QColor &color = Qt::red, QGraphicsItem *parent = 0);

    /**
     * @brief boundingRect  外边范围
     * @return              外边范围
     */
    QRectF boundingRect() const;

    /**
     * @brief paint     绘画
     * @param painter   QPainter
     * @param option    样式选项
     * @param widget    QWidget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_geometry(const QRectF &rect);

    /**
     * @brief set_color 设置闸门显示颜色
     * @param color     颜色
     */
    void set_color(const QColor &color);

    /**
     * @brief set_start 设置显示起点
     * @param start     起点
     */
    void set_start(qreal start);

    /**
     * @brief set_height    设置显示高度
     * @param height        高度(%)
     */
    void set_height(int height);

private:
    qreal m_width;      // 闸门宽度
    QColor m_color;
};

#endif // __GATE_ITEM_H__
