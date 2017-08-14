#ifndef __B_SCAN_SCENE_H__
#define __B_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <QMutex>

#include <display/palette_color.h>
#include <source/beams.h>

class BscanScene : public QGraphicsScene
{
    Q_OBJECT

public:

    enum E_BscanDirection{
        HORIZONTAL,
        VERTICAL
    };


    explicit BscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent = 0);
    void show_wave(DplSource::BeamPointer beamPointer);
    void reset();
    bool set_pix_per_beam(double ratio);
    inline void set_direction(E_BscanDirection direction) { m_direction = direction; }
    inline E_BscanDirection direction() { return m_direction; }

signals:
    void one_beam_show_successed();

public slots:
    void set_size(const QSize &size);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void draw_beams();

    QImage                          *m_image;
    DplDisplay::PaletteColorPointer m_palette;
    DplSource::BeamPointer          m_beamPointer;
    QSize                           m_size;
    int                             m_currentIndex;
    double                          m_pixPerBeamRatio;
    static const int COMPRESS_TYPE = 0;
    E_BscanDirection                m_direction;

private:
    void draw_horizontal_beam(float ratio, int pixCount, int maxIndex, int align);
    void draw_vertical_beam(float ratio, int pixCount, int maxIndex, int align);

};

#endif // __B_SCAN_SCENE_H__
