/**
 * @file vpa_item.h
 * @brief VPA项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#ifndef __VPA_ITEM_H__
#define __VPA_ITEM_H__

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <device/group.h>

class VpaItem :public QGraphicsObject
{
    Q_OBJECT
public:
    VpaItem(const DplDevice::GroupPointer &group);

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
     * @brief is_moving 获取移动状态
     * @return          存于移动状态时返回true，否则为false
     */
    bool is_moving() const;

public slots:
    void update_pos();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);


protected slots:
    void do_visible_changed(bool flag);


private:
    bool m_movingFlag;
    DplDevice::GroupPointer m_group;
};

inline bool VpaItem::is_moving() const
{
    return m_movingFlag;
}

#endif // __VPA_ITEM_H__
