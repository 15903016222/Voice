#include "b_scan_scene.h"
#include <QImage>
#include <QPainter>
#include <QDebug>

BscanScene::BscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent) : QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette),
    m_currentIndex(0),
    m_pixPerBeamRatio(1.0),
    m_direction(VERTICAL)
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
        m_image = new QImage(m_size, QImage::Format_Indexed8);
        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);

    } else {

        delete m_image;

        m_image = new QImage(m_size, QImage::Format_Indexed8);
        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);
        m_currentIndex = 0;

    }

    setSceneRect(-m_size.width()/2, -m_size.height()/2,
                 m_size.width(), m_size.height());
    update();
}


void BscanScene::show_wave(DplSource::BeamPointer beamPointer)
{
    m_beamPointer = beamPointer;

    if(m_image == NULL || m_beamPointer.isNull()) {
        qDebug("[%s] value is NULL.", __FUNCTION__);
        return;
    }

    draw_beams();
    update();
}


void BscanScene::reset()
{
    if(NULL != m_image) {

        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);
        m_currentIndex = 0;
    }
}

bool BscanScene::set_pix_per_beam(double ratio)
{
    if(ratio < 0.0) {
        return false;
    }

    m_pixPerBeamRatio = ratio;
    return true;
}

void BscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(m_image != NULL) {
        painter->drawImage(rect, *m_image);
    }
}


void BscanScene::draw_beams()
{
    if(COMPRESS_TYPE == (int)m_pixPerBeamRatio) {
        /* 压缩显示 */
        /* TODO */
        qDebug() << "[" << __FUNCTION__ << "]" << " todo COMPRESS_TYPE...";

    } else {

        int height;
        int width;

        if(m_direction == VERTICAL) {
            height  = m_size.height();
            width   =  m_size.width();
        } else {
            width  = m_size.height();
            height =  m_size.width();
        }

        float ratio = m_beamPointer->get_wave().size() / 1.0 / height; /* 一个像素点代表多少个point */
        int pixCount = (int)(m_pixPerBeamRatio + 0.5);
        int maxIndex = width / (int)(m_pixPerBeamRatio + 0.5);

        int align = width % (int)(m_pixPerBeamRatio + 0.5);
        if(align != 0) {
            ++maxIndex;
        }

        if(m_direction == VERTICAL) {
            draw_vertical_beam(ratio, pixCount, maxIndex, align);
        } else {
            draw_horizontal_beam(ratio, pixCount, maxIndex, align);
        }
    }
}

void BscanScene::draw_vertical_beam(float ratio, int pixCount, int maxIndex, int align)
{
    if(m_currentIndex  < maxIndex) {

        if((m_currentIndex + 1) == maxIndex && align != 0) {

            /* 非对齐最后一个 */
            QImage tmp = m_image->copy();
            int offset =  pixCount - align;
            for(int i = 0; i < m_size.height(); ++i) {

                quint8 *line    = (quint8*) m_image->scanLine(i);
                quint8 *tmpline = (quint8*) tmp.scanLine(i);

                memcpy(line, tmpline + offset, pixCount * (m_currentIndex) - offset);

                for(int j = 0; j < pixCount; ++j) {
                    line[m_size.width() - j - 1] = m_beamPointer->get_wave().at((int)(i * ratio));
                }
            }

        } else {

            for (int i = 0; i < m_size.height(); ++i) {

                quint8 *line = (quint8*) m_image->scanLine(i);

                for(int j = 0; j < pixCount; ++j) {

                    line[m_currentIndex * pixCount + j] = m_beamPointer->get_wave().at((int)(i * ratio));
                }
            }
        }

        ++m_currentIndex;

    } else {

        /* 整个显示区域画满beam，开始滚动显示后续的beam */
        QImage tmp = m_image->copy();
        for(int i = 0; i < m_size.height(); ++i) {

            quint8 *line = (quint8*) m_image->scanLine(i);
            quint8 *tmpline = (quint8*) tmp.scanLine(i);

            memcpy(line, tmpline + pixCount, m_image->width() - 1);

            for(int j = 0; j < pixCount; ++j) {

                line[m_image->width() - j - 1] = m_beamPointer->get_wave().at((int)(i * ratio));
            }
        }
        emit one_beam_show_successed();
    }
}


void BscanScene::draw_horizontal_beam(float ratio, int pixCount, int maxIndex, int align)
{
    if(m_currentIndex  < maxIndex) {

        if((m_currentIndex + 1) == maxIndex && align != 0) {

            /* 非对齐最后一个 */
            int offset =  pixCount - align;
            int row = m_currentIndex * pixCount;

            for(int i = 0; i < row; ++i) {

                quint8 *sourceLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i - offset);
                quint8 *targetLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i);

                memcpy(targetLine, sourceLine, m_size.width());
            }

            for(int i = 0; i < pixCount; ++i) {
                quint8 *targetLine = (quint8*) m_image->scanLine(i);
                for(int j = 0; j < m_size.width(); ++j) {
                    targetLine[j] = m_beamPointer->get_wave().at((int)(j * ratio));
                }
            }
        } else {

            for (int i = 0; i < pixCount; ++i) {

                quint8 *line = (quint8*) m_image->scanLine(m_size.height() - m_currentIndex * pixCount - i -1);

                for(int j = 0; j < m_size.width(); ++j) {

                    line[j] = m_beamPointer->get_wave().at((int)(j * ratio));
                }
            }
        }

        ++m_currentIndex;

    } else {

         int row = m_size.height() - pixCount;

         for(int i = 0; i < row; ++i) {

             quint8 *sourceLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i - pixCount);
             quint8 *targetLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i);

             memcpy(targetLine, sourceLine, m_size.width());
         }

         for(int i = 0; i < pixCount; ++i) {
             quint8 *targetLine = (quint8*) m_image->scanLine(i);
             for(int j = 0; j < m_size.width(); ++j) {
                 targetLine[j] = m_beamPointer->get_wave().at((int)(j * ratio));
             }
         }

        emit one_beam_show_successed();
    }
}


