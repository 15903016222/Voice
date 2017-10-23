#ifndef __BASE_CURSOR_ITEM_H__
#define __BASE_CURSOR_ITEM_H__

#include <QGraphicsItem>



class BaseCursorItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BaseCursorItem(Qt::Orientation orientation, Qt::Orientation innerOrientation, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void set_size(const QSize size) { m_size = size; }

protected slots:
    void do_visible_changed(bool flag);

protected:

    QSize   m_size;
    QColor  m_color;
    Qt::Orientation m_orientation;
    Qt::Orientation m_innerOrientation;

    volatile bool m_movingFlag;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // __BASE_CURSOR_ITEM_H__
