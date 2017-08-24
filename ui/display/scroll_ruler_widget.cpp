#include "ui/display/scroll_ruler_widget.h"
#include <QPainter>
#include <QDebug>
#include <QScrollBar>

ScrollRulerWidget::ScrollRulerWidget(QWidget *parent) :
    RulerWidget(parent),
    m_stepUnit(0),
    m_offsetPix(0),
    m_unitNum(0),
    m_moveTotalUnit(0.0)
{

}

void ScrollRulerWidget::move_encoder_x(unsigned int step)
{

}


void ScrollRulerWidget::move_unit(unsigned int msec)
{
    m_moveTotalUnit += (msec / 1000.0);
    int movePix = m_moveTotalUnit * (y_axis_length() / (m_end - m_start)) + 0.5;    /* 要偏移的像素点*/
    m_unitNum = movePix / m_stepUnit;             /* 要偏移多少个10 * m_pixelPerUnit */
    m_offsetPix = movePix % m_stepUnit;           /* 画标尺时真正偏移的像素点 */

//    qDebug() << "m_moveTotalUnit = " << m_moveTotalUnit
//             << " movePix = " << movePix
//             << " m_unitNum = " << m_unitNum
//             << " m_offsetPix = " << m_offsetPix
//             << " m_stepUnit = " << m_stepUnit;
}

void ScrollRulerWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    double interval = 0.0;                              // 单位/刻度
    int markQty = 0;                                    // 刻度数
    int length = y_axis_length();                       // 标尺像素长度
    float m_pixelPerUnit = length/(m_end - m_start);    // 像素/单位

    if (length >= 400) {
        markQty = 100;
    } else if ( length > 300 && length < 400 ) {
        markQty = 80;
    } else if ((length > 200) && (length < 300)) {
        markQty = 50;
    } else if ((length > 100) && ( length<200 )) {
        markQty = 40;
    } else {
        markQty = 20;
    }

    interval = (m_end - m_start) / markQty;

    if (interval < 0.01 ) {
        interval = 0.01;
    } else if ( 0.01 <=interval && interval < 0.1 ) {
        interval = ((int)(interval * 100)) / 100.0 ;
    } else if ( 0.1 <=interval  && interval < 1.0 ) {
        interval = ((int)(interval * 10)) / 10.0;
    } else if (interval >= 1.0 && interval <= 5.0 ) {
        interval = (int)  interval;
    } else if (interval > 5  && interval <= 10 ) {
        interval = 10;
    } else if (interval > 10 && interval < 50) {
        interval = 10 * (1 + (int)(interval / 10));
    } else if (interval >= 50 && interval <= 100) {
        interval = 100;
    } else if (interval > 100 && interval <= 200) {
        interval = 200;
    } else if (interval > 200) {
        interval = 100 * (1 + (int)(interval / 100));
    }
    markQty = (int)((m_end - m_start) / interval + 0.5);

    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    painter.setBrush(this->m_bgColor);
    painter.drawRect(this->rect());

    if (RulerWidget::LEFT == m_type) {
        painter.rotate(90);
        painter.translate(0, -20);
    } else if (RulerWidget::RIGHT == m_type) {
        QTransform form = painter.transform();
        form.rotate(90);
        form.rotate(180, Qt::XAxis);
        painter.setTransform(form);
    }

    painter.setPen(QColor(Qt::black));

    painter.drawText(length/2, 19, m_unitName);

    /* 最大步进 */
    m_stepUnit = (int)(10 * interval * m_pixelPerUnit + 0.5);

    if (RulerWidget::Down == m_direction) {
        for(int i = 0; i < markQty; ++i) {
            int targetX = length - (int)(i * interval * m_pixelPerUnit + 0.5) + m_offsetPix;
            if(length < targetX) {
                targetX = length - (int)((markQty + i) * interval * m_pixelPerUnit + 0.5) + m_offsetPix;
            }

            painter.drawLine(targetX, 0, targetX, 3);
        }

        for(int i = 5; i < markQty; i += 10) {

            int targetX = length - (int)(i * interval * m_pixelPerUnit + 0.5) + m_offsetPix;

            if(length < targetX) {

                int markQtyEnd = markQty - (markQty - 5) % 10;
                targetX = length - (int)((markQtyEnd + i + 5) * interval * m_pixelPerUnit + 0.5) + m_offsetPix;
            }

            painter.drawLine(targetX, 0, targetX, 7);
        }


        for(int i = 0; i < markQty; i += 10) {

            int targetX = length - (int)(i * interval * m_pixelPerUnit + 0.5) + m_offsetPix;

            if(length < targetX) {

                int align = markQty % 10;
                /* align == 0，则偏移一个单位画数值 */
                if(align == 0) {
                    targetX = length - (int)((markQty - align + i) * interval * m_pixelPerUnit + 0.5) + m_offsetPix;
                    painter.drawText(targetX + 2, 12, QString::number(((markQty / 10  + m_unitNum) * 10) * interval + m_start, 'f', 1));
                }

            } else {
                painter.drawText(targetX - 15, 12, QString::number((i + m_unitNum * 10) * interval + m_start));
            }

            painter.drawLine(targetX, 0, targetX, 13);
        }

    } else {

        for(int i = 0; i < markQty; ++i) {
            int targetX = (int)(i * interval * m_pixelPerUnit + 0.5) - m_offsetPix;
            if(targetX < 0) {
                targetX = (int)((markQty + i) * interval * m_pixelPerUnit + 0.5) - m_offsetPix;
            }
            painter.drawLine(targetX, 0, targetX, 3);
        }

        for(int i = 5; i < markQty; i += 10) {
            int targetX = (int)(i * interval * m_pixelPerUnit + 0.5) - m_offsetPix;

            if(targetX < 0) {
                int markQtyEnd = markQty - (markQty - 5) % 10;
                targetX = (int)((markQtyEnd + i + 5) * interval * m_pixelPerUnit + 0.5) - m_offsetPix;
            }

            painter.drawLine(targetX, 0, targetX, 7);
        }

        for(int i = 0; i < markQty; i += 10) {

            int targetX = (int)(i * interval * m_pixelPerUnit + 0.5) - m_offsetPix;

            if(targetX < 0) {
                int align = markQty % 10;
                /* align == 0，则不偏移一个单位，若不等于1，则偏移一个单位 */
                //if((interval * 10.0) >= 1.0) {
                if(align == 0) {
                    targetX = (int)((markQty - align + i) * interval * m_pixelPerUnit + 0.5) - m_offsetPix;
                    painter.drawText(targetX + 2, 12, QString::number(((markQty / 10  + m_unitNum) * 10) * interval + m_start, 'f', 1));
                } else {
                    targetX = (int)((markQty - align + i + 10) * interval * m_pixelPerUnit + 0.5) - m_offsetPix;
                    painter.drawText(targetX + 2, 12, QString::number(((markQty / 10 + 1 + m_unitNum) * 10) * interval + m_start, 'f', 1));
                }

            } else {

                painter.drawText(targetX + 2, 12, QString::number((i + m_unitNum * 10) * interval + m_start, 'f', 1));
            }

            painter.drawLine(targetX, 0, targetX, 13);
        }
    }
}

void ScrollRulerWidget::resizeEvent(QResizeEvent *event)
{
    if(m_moveTotalUnit > 0.01) {

        /* 计算旧size与新size间差值，得出时间差值 */
        double differentValue;
        if (RulerWidget::BOTTOM == m_type) {
            differentValue = (event->oldSize().width() - event->size().width()) * ((m_end - m_start) / (double)y_axis_length());
        } else {
            differentValue = (event->oldSize().height() - event->size().height()) * ((m_end - m_start) / (double)y_axis_length());
        }

        m_moveTotalUnit += differentValue;

        qDebug() << "[" << this->objectName() << "]" << " event old size = " << event->oldSize() << " new size = " << event->size();
    }
}
