#ifndef __WAVE_ITEM_H__
#define __WAVE_ITEM_H__

#include <QGraphicsItem>

class WaveItem : public QGraphicsItem
{
public:
    WaveItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_wave(const QByteArray &beam);

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
     * @brief color 获取波形颜色
     * @return      颜色
     */
    const QColor &color() const;

    /**
     * @brief set_color 设置波形
     * @param color
     */
    void set_color(const QColor &color);

protected:
    QPainterPath draw(const QByteArray &wave, int w, int h);

private:
    QColor m_color;
    QByteArray m_beam;
    QSize m_size;
};

inline void WaveItem::set_wave(const QByteArray &beam)
{
    if (! beam.isEmpty()) {
        m_beam.setRawData(beam.constData(), beam.size());
        update();
    }
}

inline const QSize &WaveItem::size() const
{
    return m_size;
}

inline void WaveItem::set_size(const QSize &size)
{
    m_size = size;
    update();
}

inline const QColor &WaveItem::color() const
{
    return m_color;
}

inline void WaveItem::set_color(const QColor &color)
{
    m_color = color;
}

#endif // __WAVE_ITEM_H__
