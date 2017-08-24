#include "b_scan_time_scene.h"
#include <QDebug>

#include <source/source.h>
#include <device/device.h>
#include <source/beams.h>

BscanTimeScene::BscanTimeScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) :
    BscanScene(palette, group, parent)
{

}

void BscanTimeScene::draw_horizontal_beam()
{
    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    const quint8 *waveData = (quint8*) m_beamsPointer->raw_data();
    if(m_beamsShowedCount  < maxIndex) {

        if((m_beamsShowedCount + 1) == maxIndex && align != 0) {

            /* 非对齐,最后一条beam */
            int offset =  pixCount - align;
            int row = m_beamsShowedCount * pixCount + 0.5;

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

                quint8 *line = (quint8*) m_image->scanLine(m_size.height() - m_beamsShowedCount * pixCount - i -1);

                for(int j = 0; j < m_size.width(); ++j) {

                    line[j] = waveData[(int)(j * ratio)];
                }
            }
        }

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

    ++m_beamsShowedCount;

}


void BscanTimeScene::draw_vertical_beam()
{

    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    const quint8 *waveData = (quint8 *) m_beamsPointer->raw_data();

    if(m_beamsShowedCount  < maxIndex) {

        if((m_beamsShowedCount + 1) == maxIndex && align != 0) {

            /* 非对齐,最后一条beam */
            QImage tmp = m_image->copy();
            int offset =  pixCount - align;
            for(int i = 0; i < m_size.height(); ++i) {

                quint8 *line    = (quint8*) m_image->scanLine(i);
                quint8 *tmpline = (quint8*) tmp.scanLine(i);

                memcpy(line, tmpline + offset, pixCount * (m_beamsShowedCount) - offset);

                for(int j = 0; j < pixCount; ++j) {
                    line[m_size.width() - j - 1] = waveData[(int)(i * ratio)];
                }
            }

        } else {

            for (int i = 0; i < m_size.height(); ++i) {

                quint8 *line = (quint8*) m_image->scanLine(i);

                for(int j = 0; j < pixCount; ++j) {

                    line[(int)(m_beamsShowedCount * pixCount + j)] = waveData[(int)(i * ratio)];
                }
            }
        }

    } else {

        /* 整个显示区域画满beam，开始滚动显示后续的beam */
        QImage tmp = m_image->copy(pixCount, 0, m_image->width(), m_image->height());
        m_image->swap(tmp);

        for(int i = 0; i < m_size.height(); ++i) {
            quint8 *line = (quint8*) m_image->scanLine(i);
            for(int j = 0; j < pixCount; ++j) {
                line[m_image->width() - j - 1] = waveData[(int)(i * ratio)];
            }
        }

        emit one_beam_show_successed();
    }

    ++m_beamsShowedCount;

}


void BscanTimeScene::redraw_horizontal_beam()
{
#if 0
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
    m_beamsShowedCount = 0;

    for(int resetIndex = startIndex; resetIndex < m_waveVect.count(); ++resetIndex) {

        if(m_beamsShowedCount  < maxIndex) {

            if((m_beamsShowedCount + 1) == maxIndex && align != 0) {

                /* 非对齐,最后一条beam */
                int offset =  pixCount - align;
                int row = m_beamsShowedCount * pixCount;

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

                    quint8 *line = (quint8*) m_image->scanLine(m_size.height() - m_beamsShowedCount * pixCount - count -1);

                    for(int j = 0; j < m_size.width(); ++j) {
                        line[j] = m_waveVect.at(resetIndex).wave.at((int)(j * ratio));
                    }
                }
            }

            ++m_beamsShowedCount;
        }
    }

#endif
}


void BscanTimeScene::redraw_vertical_beam()
{

    if(!((m_beamsShowedCount > 0)
         && (!m_beamsPointer.isNull())
        && (m_image != NULL))) {
        return;
    }


    float   ratio;
    double  pixCount;
    int     maxIndex;
    int     align;

    calculate_properties(ratio, pixCount, maxIndex, align);

    qDebug() << " ratio = " << ratio
                << " pixCount = " << pixCount
                << " maxIndex = " << maxIndex
                << " align = " << align;

    /* index从0开始 */
    unsigned int frameIndex = m_beamsPointer->get(0)->index() / DplDevice::Device::instance()->total_beam_qty();

    qDebug() << " m_beamsPointer->get(0)->index() = " << m_beamsPointer->get(0)->index()
            << " total_beam_qty = " << DplDevice::Device::instance()->total_beam_qty()
             << " frameIndex = " << frameIndex;

    DplSource::BeamsPointer tmp;

    int totalFrameCount = 256 * 1024 * 1024 / m_beamsPointer->size();

    qDebug() << " beams size = " << m_beamsPointer->size()
             << " total frame count = " << totalFrameCount
             << " group = " << m_group;

    int redrawCount;
    if(m_beamsShowedCount < maxIndex) {
        /* 未滚动显示 */
        redrawCount = m_beamsShowedCount;
    } else {
        /* 滚动显示 */
        redrawCount = maxIndex;
    }

    int beginShowIndex = frameIndex - redrawCount + 1;

    qDebug() << "[" << __FUNCTION__ << "]" << " debug....1"
             << " redrawCount = " << redrawCount
             << " m_beamsShowedCount = " << m_beamsShowedCount;

    int tmpBeamsShowedCount = 0;

    for(int i = 0; i < redrawCount; ++i) {

        if(beginShowIndex >= 0) {
            /* 顺序显示beams */
                    qDebug() << "[" << __FUNCTION__ << "]" << " debug....2 "
                             << " i = " << i
                             << " beginShowIndex = " << beginShowIndex + i
                             << " tmpBeamsShowedCount = " << tmpBeamsShowedCount;
            tmp = DplSource::Source::instance()->beams(m_group, beginShowIndex + i);

        } else {
            /*
             * ________________________________________________________
             * |__0__|__1__|____|____|____|.....  |__20__|__21__|__22__|
             * 以上为例子：
             * 当前帧为：1
             * 已显示帧数为：5
             * 则显示帧数顺序为：20、21、22、0、1
             */

            /* 从倒数第（totalFrameCount - lastIndex）个开始显示 */


            if(i < abs(beginShowIndex)) {
                int index = totalFrameCount + beginShowIndex + i;
                qDebug() << "[" << __FUNCTION__ << "]" << " debug....3" << " get beams by index = " << index;
                tmp = DplSource::Source::instance()->beams(m_group, index);
            } else {
                                    qDebug() << "[" << __FUNCTION__ << "]" << " debug....4"
                                                << " get beams by index = " << i - abs(beginShowIndex);
                tmp = DplSource::Source::instance()->beams(m_group, i - abs(beginShowIndex));
            }
        }

        if(tmp.isNull()) {

            m_beamsShowedCount = redrawCount;
            qDebug() << "[" << __FUNCTION__ << "]" << " tmp is null; m_beamsShowedCount = " << m_beamsShowedCount;
            return;
        }

        const quint8 *waveData = (quint8 *) tmp->raw_data();

        if((tmpBeamsShowedCount + 1) == maxIndex && (align != 0)) {
                                qDebug() << "[" << __FUNCTION__ << "]" << " debug....5";
            /* 非对齐,最后一条beam */
            int offset =  pixCount - align;
            QImage tmp = m_image->copy(offset, 0, m_image->width(), m_image->height());
            m_image->swap(tmp);

            for(int i = 0; i < m_size.height(); ++i) {

                quint8 *line    = (quint8*) m_image->scanLine(i);

                for(int j = 0; j < pixCount; ++j) {
                    line[m_size.width() - j - 1] = waveData[(int)(i * ratio)];
                }
            }

        } else {

            qDebug() << "[" << __FUNCTION__ << "]" << " debug....6"
                     << " m_size.h = " << m_size.height();

            for(int lineNum = 0; lineNum < m_size.height(); ++lineNum) {

                quint8 *line    = (quint8*) m_image->scanLine(lineNum);

                for(int j = 0; j < pixCount; ++j) {

//                    qDebug() << "[" << __FUNCTION__ << "]" << " debug....8 i = " << i
//                             << " lineNum = " << lineNum
//                             << " line[] = " << (int)(tmpBeamsShowedCount * pixCount + j)
//                             << " waveData[] = " << (int)(lineNum * ratio);
                   // line[(int)(tmpBeamsShowedCount * pixCount + j)] = waveData[(int)(lineNum * ratio)];
                    line[(int)(tmpBeamsShowedCount * pixCount + j)] = 128;
                }
            }
        }

        ++tmpBeamsShowedCount;
        qDebug() << "[" << __FUNCTION__ << "]" << " debug....9 tmpBeamsShowedCount = " << tmpBeamsShowedCount;
    }

#if 0
    if(maxIndex >= m_waveVect.count()){
        startIndex = 0;
    } else {
        startIndex =  m_waveVect.count() - maxIndex - 1;
    }

    m_beamsShowedCount = 0;

    for(int resetIndex = startIndex; resetIndex < m_waveVect.count(); ++resetIndex)
    {

        if(m_beamsShowedCount  < maxIndex) {

            if((m_beamsShowedCount + 1) == maxIndex && align != 0) {

                /* 非对齐,最后一条beam */
                QImage tmp = m_image->copy();
                int offset =  pixCount - align;

                for(int i = 0; i < m_size.height(); ++i) {

                    quint8 *line    = (quint8*) m_image->scanLine(i);
                    quint8 *tmpline = (quint8*) tmp.scanLine(i);

                    memcpy(line, tmpline + offset, pixCount * (m_beamsShowedCount) - offset);

                    for(int j = 0; j < pixCount; ++j) {
                        line[m_size.width() - j - 1] = m_waveVect.at(resetIndex).wave.at((int)(i * ratio));
                    }
                }

            } else {

                for (int i = 0; i < m_size.height(); ++i) {

                    quint8 *line = (quint8*) m_image->scanLine(i);

                    for(int j = 0; j < pixCount; ++j) {
                        line[(int)(m_beamsShowedCount * pixCount + j)] = m_waveVect.at(resetIndex).wave.at((int)(i * ratio));
                    }
                }
            }

            ++m_beamsShowedCount;
        }
    }
#endif
}
