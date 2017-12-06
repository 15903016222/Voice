#ifndef __TCG_ITEM_H__
#define __TCG_ITEM_H__

#include <QGraphicsItem>
#include <sizing/tcgs.h>
#include <ut/sample.h>

class TcgItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TcgItem(const DplSizing::TcgsPointer &tcgs, const DplUt::SamplePointer &sample, QGraphicsItem *parent = 0);

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

signals:
    void painter_path_changed();

protected slots:
    void set_visible(bool flag);

private:
    DplSizing::TcgsPointer m_tcgs;
    DplUt::SamplePointer m_sample;
    QPainterPath m_path;
    QSize m_size;
};

inline const QSize &TcgItem::size() const
{
    return m_size;
}

inline void TcgItem::set_size(const QSize &size)
{
    m_size = size;
    update();
}

#endif // __TCG_ITEM_H__
