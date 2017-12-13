#ifndef __BACKGROUND_ITEM_H__
#define __BACKGROUND_ITEM_H__

#include <QGraphicsItem>

class BackgroundItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit BackgroundItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief size  获取显示大小
     * @return      大小
     */
    const QSize &size() const;

    /**
     * @brief set_size  设置显示大小
     * @param size      大小
     */
    void set_size(const QSize &size);

    /**
     * @brief draw  画图
     * @param image 图
     */
    void draw(const QImage &image);

signals:
    void image_changed();

public slots:
    void update();

private:
    QSize m_size;
    QPixmap m_pixmap;
};

inline const QSize &BackgroundItem::size() const
{
    return m_size;
}

inline void BackgroundItem::set_size(const QSize &size)
{
    m_size = size;
    update();
}

#endif // __BACKGROUND_ITEM_H__
