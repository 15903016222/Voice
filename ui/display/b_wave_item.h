#ifndef __B_WAVE_ITEM_H__
#define __B_WAVE_ITEM_H__

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include <QVector>
#include "device/group.h"

class ColorBar;
class QPixmap;
class QImage;
class QPaintDevice;


class BWaveItem : public QGraphicsWidget /* QGraphicsItem */
{
public:
    BWaveItem(ColorBar *colorBar, QGraphicsWidget *parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_size(const QSize &size);

    void set_wave(const DplSource::BeamsPointer &beams);


private:

    QSize           m_size;
    ColorBar        *m_colorBar;
    QImage          *m_image;

    DplSource::BeamsPointer m_beams;

};

#endif // __B_WAVE_ITEM_H__
