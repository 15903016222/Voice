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

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_geometry(const QRectF &rect);

    void set_color(const QColor &color);

private:
    qreal m_width;      // 闸门宽度
    QColor m_color;
};

#endif // __GATE_ITEM_H__
