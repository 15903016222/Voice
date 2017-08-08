#include "c_scan_scene.h"

CscanScene::CscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent) :
    QGraphicsScene(parent),
    m_palette(palette)
{

}

void CscanScene::set_size(const QSize &size)
{
    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());
}
