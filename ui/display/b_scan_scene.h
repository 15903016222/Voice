#ifndef __B_SCAN_SCENE_H__
#define __B_SCAN_SCENE_H__

#include <QGraphicsScene>

#include <display/palette_color.h>
#include <source/beams.h>

class BscanScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit BscanScene(QObject *parent = 0);
    void show_wave(const DplSource::BeamsPointer &beams);

public slots:
    void set_size(const QSize &size);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QImage                          *m_image;
    DplDisplay::PaletteColorPointer m_palette;
    DplSource::BeamsPointer         m_beams;
    QSize                           m_size;

};

#endif // __B_SCAN_SCENE_H__
