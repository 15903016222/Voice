#ifndef __BASE_CURSOR_ITEM_H__
#define __BASE_CURSOR_ITEM_H__

#include <QGraphicsItem>

static const int    DEFAULT_TOOLTIP_WIDTH  = 20;
static const int    DEFAULT_TOOLTIP_HEIGHT = 13;

class BaseCursorItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BaseCursorItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void set_size(const QSize size) { m_size = size; }

public slots:

protected:

    QSize   m_size;
    QColor  m_color;

    volatile bool m_movingFlag;
    double  m_position;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // __BASE_CURSOR_ITEM_H__
