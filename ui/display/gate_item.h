/**
 * @file gate_item.h
 * @brief 闸门项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#ifndef __GATE_ITEM_H__
#define __GATE_ITEM_H__

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <ut/sample.h>
#include <gate/gate.h>

class GateItem :public QGraphicsObject
{
    Q_OBJECT
public:
    GateItem(const DplUt::SamplePointer &sample, const DplGate::GatePointer &gate, QGraphicsItem *parent = 0);

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
     * @brief ratio     获取画布与声程范围(ns)的比例系数
     * @return          系数
     */
    float ratio() const;

    /**
     * @brief is_moving 获取移动状态
     * @return          存于移动状态时返回true，否则为false
     */
    bool is_moving() const;

    /**
     * @brief set_offset    设置偏移位置
     * @param offset        偏移位置(ns)
     */
    void set_offset(qreal offset);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

protected slots:
    void do_visible_changed(bool flag);

    void update_pos();

private:
    DplUt::SamplePointer m_sample;
    DplGate::GatePointer m_gate;
    float m_ratio;
    bool m_movingFlag;
    qreal m_offset;
};

inline void GateItem::set_ratio(qreal ratio)
{
    m_ratio = ratio;
    update_pos();
}

inline float GateItem::ratio() const
{
    return m_ratio;
}

inline bool GateItem::is_moving() const
{
    return m_movingFlag;
}

#endif // __GATE_ITEM_H__
