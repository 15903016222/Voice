#ifndef __C_SCAN_SCENE_H__
#define __C_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <display/palette_color.h>
#include <source/axis.h>

class CscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent = 0);

    inline DplSource::Axis::Driving driving() { return m_driving; }

public slots:
    void set_size(const QSize &size);

protected:
    volatile DplSource::Axis::Driving        m_driving;

private:
    DplDisplay::PaletteColorPointer m_palette;
};

#endif // __C_SCAN_SCENE_H__
