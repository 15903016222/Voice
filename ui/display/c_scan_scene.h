#ifndef __C_SCAN_SCENE_H__
#define __C_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <display/palette_color.h>

class CscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent = 0);

public slots:
    void set_size(const QSize &size);

private:
    DplDisplay::PaletteColorPointer m_palette;
};

#endif // __C_SCAN_SCENE_H__
