#include "b_scan_scene.h"
#include <QImage>
#include <QPainter>

BscanScene::BscanScene(QObject *parent) : QGraphicsScene(parent)
{

}


void BscanScene::set_size(const QSize &size)
{
    if((size.height() == m_size.height())
            && (size.width() == m_size.width())
            && (m_image != NULL))  {
        return;
    }

    m_size = size;

    if(m_image == NULL) {
        m_image = new QImage(size, QImage::Format_Indexed8);
    } else {
        delete m_image;
        m_image = new QImage(size, QImage::Format_Indexed8);
    }

    update();
}


void BscanScene::show_wave(const DplSource::BeamsPointer &beams)
{
    m_beams = beams;
    update();
}

void BscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (m_image) {
        painter->drawImage(rect, *m_image);
    }
}


