#ifndef __C_SCAN_ENCODER_SCENE_H__
#define __C_SCAN_ENCODER_SCENE_H__

#include "c_scan_scene.h"

class CscanEncoderScene : public CscanScene
{
public:

    struct S_WAVE_INFO{
        int x;
        int y;
        QByteArray waveData;
    };

    CscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    inline double show_start() { return m_currentStart; }
    inline double show_end() { return m_currentEnd; }

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

    /**
     * @brief draw_vertical_beam    C扫的垂直显示
     */
    virtual void draw_vertical_beam();


    /**
     * @redraw_horizontal_beam 当显示大小改变，重新画垂直C扫
     */
    virtual bool redraw_vertical_beam();

    DplSource::Encoder           m_encoder;
    DplSource::Axis              m_axis;
    DplSource::EncoderPointer    m_encoderPointer;

    double      m_offsetX;          /* 相对扫查起始点的偏移值 */
    double      m_currentEnd;       /* 保存显示的开始值 */
    double      m_currentStart;     /* 保存显示的结束值 */
    double      m_currentX;         /* 当前显示的X */
    double      m_moveOffsetX;      /* m_currentX与最新X差值 */

    S_WAVE_INFO m_maxShowedWave;    /* 当前最大已显示的X */

    bool is_equal(double value1, double value2);

    void init_encoder_properties();
    void init_scan_properties();

    void set_driving(DplSource::Axis::Driving driving);

};

#endif // __C_SCAN_ENCODER_SCENE_H__
