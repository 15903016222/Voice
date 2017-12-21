#ifndef __C_SCAN_ITEM_H__
#define __C_SCAN_ITEM_H__

#include <QGraphicsItem>
#include <QMutex>

#include "c_scan_image.h"

#include <device/group.h>
#include <source/source.h>
#include <source/axis.h>

class CscanItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CscanItem(const DplDevice::GroupPointer &group, QGraphicsItem *parent = 0);
    ~CscanItem();

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
    void update_requested();

public slots:
    void update();
    void draw();
    void clear();

protected:
    void init_index();
    void draw_time();
    void draw_encoder();

private:
    QSize m_size;

    DplDevice::GroupPointer m_group;
    DplSource::Source *m_source;
    DplSource::AxisPointer m_scanAxis;

    QPixmap m_pixmap;
    CscanImage *m_image;
    int m_preIndex;
    int m_startIndex;
    int m_stopIndex;
    double m_ratio;
    QMutex m_mutex;
};

inline const QSize &CscanItem::size() const
{
    return m_size;
}

#endif // __C_SCAN_ITEM_H__
