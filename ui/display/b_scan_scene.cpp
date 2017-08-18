#include "b_scan_scene.h"
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QWriteLocker>

BscanScene::BscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent) : QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette),
    m_currentIndex(0),
    m_pixPerBeamRatio(1.0),
    m_direction(VERTICAL),
    m_releasing(false)
{
    m_waveVect.clear();
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()));

}

BscanScene::~BscanScene()
{
//    QWriteLocker locker(&m_releaseLock);
    m_releasing = true;

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

}


void BscanScene::show_wave(const DplSource::BeamsPointer &beamPointer)
{
//    QWriteLocker releaseLock(&m_releaseLock);
    if(m_releasing) {
        return;
    }

    QWriteLocker lock(&m_rwLock);
    m_beamsPointer = beamPointer;

    if(m_image == NULL || m_beamsPointer.isNull()) {
        qDebug() << "[" << __FUNCTION__ << "]" << m_image << m_beamsPointer.isNull();
        return;
    }

    draw_beams();

    emit image_changed();
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
    QWriteLocker lock(&m_rwLock);

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

        /* 添加到缓存 */
//        if(maxIndex > m_waveVect.count()) {
//            WaveIndex tmp;
//            tmp.index   = m_beamsPointer->index();
//            tmp.wave.append(m_beamsPointer->wave());
//            m_waveVect.append(tmp);

//        } else {
//            WaveIndex tmp;
//            tmp.index   = m_beamPointer->index();
//            tmp.wave.append(m_beamPointer->wave());
//            m_waveVect.append(tmp);
//            m_waveVect.remove(0);
//        }

        if(m_direction == VERTICAL) {
            draw_vertical_beam();
        } else {
            draw_horizontal_beam();
        }
    }
}

void BscanScene::draw_vertical_beam()
{
    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    const quint8 *waveData = (quint8 *) m_beamsPointer->raw_data();

    if(m_currentIndex  < maxIndex) {

        if((m_currentIndex + 1) == maxIndex && align != 0) {

            /* 非对齐,最后一条beam */
            QImage tmp = m_image->copy();
            int offset =  pixCount - align;
            for(int i = 0; i < m_size.height(); ++i) {

                quint8 *line    = (quint8*) m_image->scanLine(i);
                quint8 *tmpline = (quint8*) tmp.scanLine(i);

                memcpy(line, tmpline + offset, pixCount * (m_currentIndex) - offset);
                for(int j = 0; j < pixCount; ++j) {
                    line[m_size.width() - j - 1] = waveData[(int)(i * ratio)];
                }
            }

        } else {

            for (int i = 0; i < m_size.height(); ++i) {

                quint8 *line = (quint8*) m_image->scanLine(i);

                for(int j = 0; j < pixCount; ++j) {

                    line[(int)(m_currentIndex * pixCount + j)] = waveData[(int)(i * ratio)];
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

            memcpy(line, tmpline + (int)pixCount, m_image->width() - 1);

            for(int j = 0; j < pixCount; ++j) {

                line[m_image->width() - j - 1] = waveData[(int)(i * ratio)];
            }
        }
        emit one_beam_show_successed();
    }
}


void BscanScene::reset_show()
{
    if(m_waveVect.size() == 0) {
        return;
    }

    if(COMPRESS_TYPE == (int)m_pixPerBeamRatio) {
        /* 压缩显示 */
        /* TODO */
        qDebug() << "[" << __FUNCTION__ << "]" << " todo COMPRESS_TYPE...";

    } else {

        if(m_direction == VERTICAL) {
            redraw_vertical_beam();
        } else {
            redraw_horizontal_beam();
        }
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

    int beamSize = m_beamsPointer->size() / m_beamsPointer->beam_qty();
    ratio =  beamSize / (double)height; /* 一个像素点代表多少个point */
    pixCount = m_pixPerBeamRatio + 0.5;
    maxIndex = width / (int)(m_pixPerBeamRatio + 0.5);

    align = width % (int)(m_pixPerBeamRatio + 0.5);
    if(align != 0) {
         maxIndex += 1;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " beamSize = " << beamSize
             << " ratio = " << ratio
             << " pixCount = " << pixCount
             << " maxIndex = " << maxIndex
             << " align = " << align
             << " width = " << this->width()
             << " height = " << this->height();
}


void BscanScene::redraw_horizontal_beam()
{           
    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    int startIndex;
    if(maxIndex >= m_waveVect.count()){
        startIndex = 0;
    } else {
        startIndex =  m_waveVect.count() - maxIndex - 1;
    }

    /* 顺序显示 */
    m_currentIndex = 0;

    for(int resetIndex = startIndex; resetIndex < m_waveVect.count(); ++resetIndex) {

        if(m_currentIndex  < maxIndex) {

            if((m_currentIndex + 1) == maxIndex && align != 0) {

                /* 非对齐,最后一条beam */
                int offset =  pixCount - align;
                int row = m_currentIndex * pixCount;

                for(int i = 0; i < row; ++i) {

                    quint8 *sourceLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i - offset);
                    quint8 *targetLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i);

                    memcpy(targetLine, sourceLine, m_size.width());
                }

                for(int count = 0; count < pixCount; ++count) {
                    quint8 *targetLine = (quint8*) m_image->scanLine(count);
                    for(int j = 0; j < m_size.width(); ++j) {
                        targetLine[j] = m_waveVect.at(resetIndex).wave.at((int)(j * ratio));
                    }
                }

            } else {

                for (int count = 0; count < pixCount; ++count) {

                    quint8 *line = (quint8*) m_image->scanLine(m_size.height() - m_currentIndex * pixCount - count -1);

                    for(int j = 0; j < m_size.width(); ++j) {
                        line[j] = m_waveVect.at(resetIndex).wave.at((int)(j * ratio));
                    }
                }
            }

            ++m_currentIndex;
        }
    }
}

void BscanScene::redraw_vertical_beam()
{
    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    int startIndex;
    if(maxIndex >= m_waveVect.count()){
        startIndex = 0;
    } else {
        startIndex =  m_waveVect.count() - maxIndex - 1;
    }

    m_currentIndex = 0;

    for(int resetIndex = startIndex; resetIndex < m_waveVect.count(); ++resetIndex)
    {

        if(m_currentIndex  < maxIndex) {

            if((m_currentIndex + 1) == maxIndex && align != 0) {

                /* 非对齐,最后一条beam */
                QImage tmp = m_image->copy();
                int offset =  pixCount - align;

                for(int i = 0; i < m_size.height(); ++i) {

                    quint8 *line    = (quint8*) m_image->scanLine(i);
                    quint8 *tmpline = (quint8*) tmp.scanLine(i);

                    memcpy(line, tmpline + offset, pixCount * (m_currentIndex) - offset);

                    for(int j = 0; j < pixCount; ++j) {
                        line[m_size.width() - j - 1] = m_waveVect.at(resetIndex).wave.at((int)(i * ratio));
                    }
                }

            } else {

                for (int i = 0; i < m_size.height(); ++i) {

                    quint8 *line = (quint8*) m_image->scanLine(i);

                    for(int j = 0; j < pixCount; ++j) {
                        line[(int)(m_currentIndex * pixCount + j)] = m_waveVect.at(resetIndex).wave.at((int)(i * ratio));
                    }
                }
            }

            ++m_currentIndex;
        }
    }
}


void BscanScene::draw_horizontal_beam()
{

    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    const quint8 *waveData = (quint8*) m_beamsPointer->raw_data();
    if(m_currentIndex  < maxIndex) {

        if((m_currentIndex + 1) == maxIndex && align != 0) {

            /* 非对齐,最后一条beam */
            int offset =  pixCount - align;
            int row = m_currentIndex * pixCount + 0.5;

            for(int i = 0; i < row; ++i) {

                quint8 *sourceLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i - offset);
                quint8 *targetLine = (quint8*) m_image->scanLine(m_size.height() - 1 - i);

                memcpy(targetLine, sourceLine, m_size.width());
            }

            for(int i = 0; i < pixCount; ++i) {
                quint8 *targetLine = (quint8*) m_image->scanLine(i);
                for(int j = 0; j < m_size.width(); ++j) {
                    targetLine[j] = waveData[(int)(j * ratio)];
                }
            }

        } else {

            for (int i = 0; i < pixCount; ++i) {

                quint8 *line = (quint8*) m_image->scanLine(m_size.height() - m_currentIndex * pixCount - i -1);

                for(int j = 0; j < m_size.width(); ++j) {

                    line[j] = waveData[(int)(j * ratio)];
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
                 targetLine[j] = waveData[(int)(j * ratio)];
             }
         }

        emit one_beam_show_successed();
    }
}


