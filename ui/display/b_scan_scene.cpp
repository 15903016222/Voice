#include "b_scan_scene.h"
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QWriteLocker>

BscanScene::BscanScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) : QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette),
    m_pixPerBeamRatio(1.0),
    m_direction(VERTICAL),
    m_beamsShowedCount(0),
    m_size(QSize(width(), height())),
    m_group(group)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()));

}

BscanScene::~BscanScene()
{
    QWriteLocker locker(&m_rwLock);

    if(NULL != m_image) {
        delete m_image;
    }
}


void BscanScene::set_size(const QSize &size)
{
    QWriteLocker lock(&m_rwLock);

    if((size.height() == m_size.height())
            && (size.width() == m_size.width())
            && (m_image != NULL))  {
        return;
    }

    m_size = size;

    if(m_image != NULL) {
        delete m_image;
        m_image = NULL;
    }

    m_image = new QImage(m_size, QImage::Format_Indexed8);
    m_image->setColorTable(m_palette->colors());
    m_image->fill(Qt::white);

    setSceneRect(-m_size.width()/2, -m_size.height()/2,
                                              m_size.width(), m_size.height());
    reset_show();

    update();
}


void BscanScene::show_wave(const DplSource::BeamsPointer &beamPointer)
{
    QWriteLocker lock(&m_rwLock);

    m_beamsPointer = beamPointer;

    if(m_beamsPointer.isNull()) {
        qDebug() << "[" << __FUNCTION__ << "]" << "m_beamsPointer is Null";
        return;
    }

    if(m_image == NULL) {

        qDebug() << "[" << __FUNCTION__ << "]" << "m_image is Null.";
        return;
    }

    draw_beams();

    emit image_changed();

}


void BscanScene::reset()
{
    QWriteLocker lock(&m_rwLock);

    if(NULL != m_image) {

        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);
        m_beamsShowedCount = 0;
        m_scrolling = false;
    }
}

bool BscanScene::set_pix_per_beam(double ratio)
{
    QWriteLocker lock(&m_rwLock);

    if(ratio < 0.0) {
        return false;
    }

    m_pixPerBeamRatio = ratio;

    return true;
}

bool BscanScene::set_current_beam(unsigned int index)
{
    m_currentIndex = index;
}


void BscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QWriteLocker lock(&m_rwLock);

    if(m_image != NULL) {
        painter->drawImage(rect, *m_image);
    }
}


void BscanScene::draw_beams()
{
    preproccess_beam();

    if(m_direction == VERTICAL) {
        draw_vertical_beam();
    } else {
        draw_horizontal_beam();
    }
}


void BscanScene::preproccess_beam()
{
    /* 计算当前beam是否到显示区最后一条beam */
    int width;
    int height;

    if(m_direction == HORIZONTAL) {
        width  = this->width();
        height = this->height();
    } else {
        width  = this->height();
        height = this->width();
    }

    /* 计算填满显示区域所需beam数 */
}


void BscanScene::reset_show()
{
    if(m_direction == VERTICAL) {
        redraw_vertical_beam();
    } else {
        redraw_horizontal_beam();
    }
}

void BscanScene::calculate_properties(float &ratio, double &pixCount, int &maxIndex, int &align)
{
    int height;
    int width;

    if(m_direction == HORIZONTAL) {
        height =  m_size.width();
        width  = m_size.height();
    } else {
        height =  m_size.height();
        width  = m_size.width();
    }

    ratio =  m_beamsPointer->point_qty() / (double)height; /* 一个像素点代表多少个point */
    pixCount = m_pixPerBeamRatio;//+ 0.5;
    maxIndex = width / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */

    align = width % (int)(m_pixPerBeamRatio + 0.5);
    if(align != 0) {
         maxIndex += 1;
    }
}


void BscanScene::redraw_horizontal_beam()
{           

}


void BscanScene::redraw_vertical_beam()
{

}

void BscanScene::draw_horizontal_beam()
{

}


void BscanScene::draw_vertical_beam()
{

}





