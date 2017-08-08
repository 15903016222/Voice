#ifndef __WAVE_ITEM_H__
#define __WAVE_ITEM_H__

#include <QGraphicsItem>
#include <display/a_scan.h>

class WaveItem : public QGraphicsItem
{
public:
    explicit WaveItem(const DplDisplay::AscanPointer &ascan, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief show_wave 显示波形
     * @param beam      波形数据
     */
    void show_wave(const QByteArray &beam);

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

protected:
    QPainterPath draw(const QByteArray &wave, int w, int h);

private:
    DplDisplay::AscanPointer m_ascan;
    QByteArray m_beam;
    QSize m_size;
};

inline void WaveItem::show_wave(const QByteArray &beam)
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

#endif // __WAVE_ITEM_H__
