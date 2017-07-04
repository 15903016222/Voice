/**
 * @file a_scan_widget.cpp
 * @brief 画A扫
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#include "a_scan_widget.h"

#include <QPainter>
#include <QDebug>

AscanWidget::AscanWidget(QWidget *parent):
    QWidget(parent),
    m_color("#ffff77")
{
}

void AscanWidget::show(const QByteArray &b)
{
    if (b.size() == 0) {
        return;
    }
    m_beam.setRawData(b.constData(), b.size());
    update();
}

QPainterPath AscanWidget::paint_wave()
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = y_axis_length() / 255.0;

    int drawPoints = 0;
    if ( m_beam.size() < x_axis_length()) {
        xRatio1 = x_axis_length() / 1.0 / m_beam.size();
        drawPoints = m_beam.size();
    } else {
        xRatio2 = m_beam.size() / 1.0 / x_axis_length();
        drawPoints = x_axis_length();
    }

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo( i*xRatio1,
                     ((quint8)(m_beam.at((int)(i*xRatio2)))) * yRatio + 0.5);
    }

    return path;
}

QPainterPath AscanWidget::paint_gate()
{
    QPainterPath path;

//    /* 计算闸门x轴起点与终点 */
//    xStartPos =


//    /* 计算闸门y轴高度 */

//    path.moveTo(xStartPos, yPos);
//    path.lineTo(xEndPos, yPos);
//    path.moveTo(xStartPos, yPos - 3);
//    path.lineTo(xStartPos, yPos + 3);
//    path.moveTo(xEndPos, yPos - 3);
//    path.lineTo(xEndPos, yPos + 3);

    return path;

//    if(GROUP_VAL_POS(grp , ut_unit)==UT_UNIT_TRUE_DEPTH)
//        {
//            sample_start *= cos(TMP(current_angle[grp]) );
//            sample_range *= cos(TMP(current_angle[grp]) );
//        }

//        if( GROUP_VAL_POS(grp ,gate[0].synchro) == 0 )/* A闸门 pulse 时 */
//        {
//            draw_start  +=  (int)((gate_start - sample_start) / sample_range * w + 20 );
//            draw_end    +=  (int)((gate_start - sample_start + gate_width )/ sample_range * w + 20);
//        }
//        else if( GROUP_VAL_POS(grp , gate[0].synchro) == 1 )/* A闸门 I/ 时 */
//        {
//            _nCurrentBeamDelay = GROUP_VAL_POS(grp , beam_delay[_nBeamNo])  + GROUP_VAL_POS(grp , wedge_delay);
//            _nGatePosition    = (double)(((TMP(measure_data[index][3])) & 0xfffff) - _nCurrentBeamDelay / 10);
//            _nGatePosition    = _nGatePosition * cos(TMP(current_angle[grp])) / 100 ;
//            draw_start  += (int)((_nGatePosition + gate_start - sample_start) / sample_range * w + 20);
//            draw_end    += (int)((_nGatePosition + gate_start - sample_start + gate_width )/ sample_range * w + 20);
//        }

//        if(GROUP_VAL_POS(grp , rectifier1))
//        {
//            draw_height = (1 - gate_height / 100.0)* h ;
//        }
//        else
//        {
//            draw_height = h * gate_height / 200.0 ;
//            h /= 2.0 ;
//            draw_height = h - draw_height ;
//        }
//        cairo_set_line_width(cr, 2);
//        cairo_move_to(cr, draw_start , draw_height );
//        cairo_line_to(cr, draw_end   , draw_height );
//        cairo_stroke(cr);
//        cairo_set_line_width(cr, 1);
//        cairo_move_to(cr, draw_start , draw_height - 3 );
//        cairo_line_to(cr, draw_start , draw_height + 3 );
//        cairo_move_to(cr,  draw_end  , draw_height - 3 );
//        cairo_line_to(cr,  draw_end  , draw_height + 3 );
//        cairo_stroke(cr);
//        prule->scanEx.gateDataA.height = draw_height;
//        prule->scanEx.gateDataA.start = draw_start - 20;
//        prule->scanEx.gateDataA.end = draw_end - 20;
//        break ;


}
