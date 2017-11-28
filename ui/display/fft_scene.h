#ifndef __FFT_SCENE_H__
#define __FFT_SCENE_H__

#include <QGraphicsScene>
#include <display/palette_color.h>

class FFTScene : public QGraphicsScene
{
public:
    FFTScene(QObject *parent = 0);

public slots:
    void set_size(const QSize &size);

};

#endif // __FFT_SCENE_H__
