/**
 * @file gate_item.h
 * @brief 闸门项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#ifndef __GATE_ITEM_H__
#define __GATE_ITEM_H__

#include <QGraphicsItem>

class GateItem :public QGraphicsObject
{
    Q_OBJECT
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
     * @brief start 获取显示起点
     * @return      起点值(ns)
     */
    qreal start() const;

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
     * @brief height    获取显示高度
     * @return          高度值(%)
     */
    int height() const;

    /**
     * @brief set_height    设置显示高度
     * @param height        高度(%)
     */
    void set_height(int height);

    /**
     * @brief is_moving 获取移动状态
     * @return          存于移动状态时返回true，否则为false
     */
    bool is_moving() const;

signals:
    void pos_changed();

protected:
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    void update_pos();

private:
    qreal m_ratio;      // 比例系数
    qreal m_start;      // 闸门起点（比例系数）
    qreal m_width;      // 闸门宽度（比例系数）
    int m_height;       // 高度(%)
    QColor m_color;
    bool m_movingFlag;
};

inline void GateItem::set_ratio(qreal ratio)
{
    m_start *= (ratio/m_ratio);
    m_width *= (ratio/m_ratio);
    m_ratio = ratio;
    update_pos();
}

inline void GateItem::set_color(const QColor &color)
{
    m_color = color;
}

inline qreal GateItem::start() const
{
    return m_start / m_ratio;
}

inline void GateItem::set_start(qreal start)
{
    m_start = start * m_ratio;
    update_pos();
}

inline void GateItem::set_width(qreal width)
{
    m_width = width * m_ratio;
}

inline int GateItem::height() const
{
    return m_height;
}

inline void GateItem::set_height(int height)
{
    m_height = height;
    update_pos();
}

inline bool GateItem::is_moving() const
{
    return m_movingFlag;
}

#endif // __GATE_ITEM_H__
