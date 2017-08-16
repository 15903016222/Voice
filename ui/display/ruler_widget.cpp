#include "ruler_widget.h"
#include <QPainter>
#include <QDebug>
#include <QScrollBar>

RulerWidget::RulerWidget(QWidget *parent) :
    QWidget(parent),
    m_bgColor("#ff88ff"),
    m_start(0),
    m_end(100),
    m_unitName("(mm)"),
    m_type(BOTTOM),
    m_direction(Up),
    m_move(0),
    m_step(0),
    m_offset(0),
    m_moveUnit(0),
    m_totalMove(0)
{
//    QScrollBar bar;
//    bar.setOrientation(Qt::Orientation);
}

bool RulerWidget::set_range(double start, double end)
{
    if (start >= end) {
        return false;
    }

    m_start = start;
    m_end = end;

    return true;
}

void RulerWidget::move_pix(unsigned int step)
{
    m_totalMove +=(step / 1000.0);
    m_move = -m_totalMove * (y_axis_length() / (m_end - m_start) + 0.5);    /* 偏移多少个像素*/
    m_moveUnit = abs(m_move) / m_step;
    m_offset = abs(m_move) % m_step * (-1) - 1;

}

void RulerWidget::paintEvent(QPaintEvent *e)
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

    painter.setBrush(m_bgColor);
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
    m_step = (int)(10 * interval * m_pixelPerUnit + 0.5);

    if (RulerWidget::Down == m_direction) {
        for(int i = 0; i < markQty; ++i) {
            int targetX = length - (int)(i * interval * m_pixelPerUnit + 0.5) + m_move;

            if(targetX < 0) {
                targetX = length - (int)((markQty + i) * interval * m_pixelPerUnit + 0.5) + m_move;
            }

            painter.drawLine(targetX, 0, targetX, 3);
        }

        for(int i = 5; i < markQty; i += 10) {
            int targetX = length - (int)(i * interval * m_pixelPerUnit + 0.5) + m_move;
            if(targetX < 0) {
                targetX = length - (int)((markQty + i) * interval * m_pixelPerUnit + 0.5) + m_move;
            }

            painter.drawLine(targetX, 0, targetX, 7);
        }

        for(int i = 0; i < markQty; i += 10) {

            int targetX = length - (int)(i * interval * m_pixelPerUnit + 0.5) + m_move;
            if(targetX < 0) {
                targetX = length - (int)((markQty + i) * interval * m_pixelPerUnit + 0.5) + m_move;
                painter.drawText(targetX - 15, 12, QString::number((markQty + i) * interval + m_start));
            } else {
                painter.drawText(targetX - 15, 12, QString::number(i * interval + m_start));
            }

            painter.drawLine(targetX, 0, targetX, 13);
        }
    } else {

        for(int i = 0; i < markQty; ++i) {
            int targetX = (int)(i * interval * m_pixelPerUnit + 0.5) + m_offset;
            if(targetX < 0) {
                targetX = (int)((markQty + i) * interval * m_pixelPerUnit + 0.5) + m_offset;
            }
            painter.drawLine(targetX, 0, targetX, 3);
        }

        for(int i = 5; i < markQty; i += 10) {
            int targetX = (int)(i * interval * m_pixelPerUnit + 0.5) + m_offset;

            if(targetX < 0) {
                int markQtyEnd = markQty - (markQty - 5) % 10;
                targetX = (int)((markQtyEnd + i + 5) * interval * m_pixelPerUnit + 0.5) + m_offset;
            }

            painter.drawLine(targetX, 0, targetX, 7);
        }

        for(int i = 0; i < markQty; i += 10) {
            int targetX = (int)(i * interval * m_pixelPerUnit + 0.5) + m_offset;
            if(targetX < 0) {
                int align = markQty % 10;
                targetX = (int)((markQty - align + i + 10) * interval * m_pixelPerUnit + 0.5) + m_offset;
                painter.drawLine(targetX, 0, targetX, 13);
                painter.drawText(targetX + 2, 12, QString::number(((markQty / 10 + 1 + m_moveUnit) * 10) * interval + m_start, 'f', 1));
            } else {
                painter.drawLine(targetX, 0, (int)(i * interval * m_pixelPerUnit + 0.5)  + m_offset, 13);
                painter.drawText(targetX + 2, 12, QString::number((i + m_moveUnit * 10) * interval + m_start, 'f', 1));
            }
        }
    }
}
