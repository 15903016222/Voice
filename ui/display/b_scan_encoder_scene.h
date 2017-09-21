#ifndef __B_SCAN_ENCODER_SCENE_H__
#define __B_SCAN_ENCODER_SCENE_H__

#include <ui/display/b_scan_scene.h>

class BscanEncoderScene : public BscanScene
{
public:

struct S_WAVE_INFO{
    int x;
    int y;
    QByteArray waveData;
};

    explicit BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent = 0);

    inline double move_x() { return m_moveX; }
    inline double show_start() { return m_currentStart;}
    inline double show_end() { return m_currentEnd;}

    virtual bool need_refresh();

protected:

    virtual void draw_vertical_beam();

    virtual void redraw_vertical_beam();

    /**
     * @brief set_vertical_image_data 设置编码器B扫的垂直显示image数据
     * @param commonProperties
     */
    void set_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties);


    /**
     * @brief set_vertical_beam_data   设置编码器B扫的一条beam垂直显示
     * @param x
     * @param commonProperties
     * @param waveData
     */
    void set_vertical_beam_data(double x,
                        const BscanScene::S_CommonProperties &commonProperties,
                        const quint8 *waveData);

    /**
     * @brief set_scroll_vertical_image_data
     * @param commonProperties
     */
    void set_scroll_vertical_image_data(const BscanScene::S_CommonProperties &commonProperties);

private:

    double      m_offsetX;          /* 相对扫查起始点的偏移值 */
    double      m_currentX;         /* 当前显示的X */
    S_WAVE_INFO m_maxShowedWave;    /* 当前最大已显示的X */

    double      m_moveOffsetX;      /* m_currentX与最新X差值 */

    DplSource::EncoderPointer           m_encoderPointer;

    double      m_moveX;            /* 重画后，告诉标尺需要移动到哪里 */
    double      m_currentEnd;       /* 保存显示的开始值 */
    double      m_currentStart;     /* 保存显示的结束值 */

    DplSource::Encoder           m_encoder;
    DplSource::Axis              m_axis;

    bool is_equal(double value1, double value2);
    double  get_dealing_x(const DplSource::BeamsPointer &beamsPointer);
    void set_driving(DplSource::Axis::Driving  driving);
    void setTmpX(double moveX, double moveY);

    void init_encoder_properties();
    void init_scan_properties();

};

#endif // __B_SCAN_ENCODER_SCENE_H__
