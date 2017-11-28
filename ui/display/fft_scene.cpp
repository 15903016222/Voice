#include "fft_scene.h"

FFTScene::FFTScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void FFTScene::set_size(const QSize &size)
{
    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());
}
