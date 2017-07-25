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

    /**
     * @brief set_ratio 设置画布宽度与声程范围(ns)的比例系数
     * @param ratio     系数
     */
    void set_ratio(qreal ratio);

    /**
     * @brief set_color 设置闸门显示颜色
     * @param color     颜色
     */
    void set_color(const QColor &color);

    /**
     * @brief set_start 设置显示起点
     * @param start     起点(ns)
     */
    void set_start(qreal start);

    /**
     * @brief set_width 设置宽度
     * @param width     宽度(ns)
     */
    void set_width(qreal width);

    /**
     * @brief set_height    设置显示高度
     * @param height        高度(%)
     */
    void set_height(int height);

private:
    qreal m_ratio;      // 比例系数
    qreal m_width;      // 闸门宽度(比例系数)
    QColor m_color;
};

inline void GateItem::set_ratio(qreal ratio)
{
    m_ratio = ratio;
}

inline void GateItem::set_width(qreal width)
{
    m_width = width * m_ratio;
}

#endif // __GATE_ITEM_H__
