#ifndef __ENCODER_SCENE_H__
#define __ENCODER_SCENE_H__

#include "base_scan_scene.h"

class EncoderScene : public BaseScanScene
{
public:
    explicit EncoderScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

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

    /**
     * @brief draw_vertical_image 设置编码器C扫的垂直显示image数据
     * @param commonProperties
     */
    void draw_vertical_image(const BaseScanScene::S_CommonProperties &commonProperties);


    /**
     * @brief set_one_vertical_beam   设置编码器C扫的一条beam垂直显示
     * @param x
     * @param commonProperties
     * @param waveData
     */
    void set_one_vertical_beam(double x,
                        const BaseScanScene::S_CommonProperties &commonProperties,
                        const DplSource::BeamsPointer &beamsPointer);

    /**
     * @brief set_scroll_env
     * @param commonProperties
     */
    void set_scroll_env(const BaseScanScene::S_CommonProperties &commonProperties);

    /**
     * @brief set_vertical_image_data   画指定帧的C扫
     * @param beamsShowedCount                  显示第几帧
     * @param commonProperties                  公共的参数
     * @param type                              beam的类型
     * @param beamsPointer                      当前帧数据
     */
    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseScanScene::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer) = 0;


    DplSource::Encoder           m_encoder;
    DplSource::Axis              m_axis;
    DplSource::EncoderPointer    m_encoderPointer;

    double      m_offsetX;          /* 相对扫查起始点的偏移值 */
    double      m_currentEnd;       /* 保存显示的开始值 */
    double      m_currentStart;     /* 保存显示的结束值 */
    double      m_currentX;         /* 当前显示的X */
    double      m_moveOffsetX;      /* m_currentX与最新X差值 */
    double      m_moveX;            /* 重画后，告诉标尺需要移动到哪里 */

    S_BEAM_INFO m_maxBeamInfo;     /* 当前最大已显示的X */

    bool is_equal(double value1, double value2);

    void init_encoder_properties();
    void init_scan_properties();

    void set_driving(DplSource::Axis::Driving driving);
    double  get_dealing_x(const DplSource::BeamsPointer &beamsPointer);
    void set_move_x(double moveX, double moveY);

};

#endif // __ENCODER_SCENE_H__
