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

protected:
    virtual void draw_horizontal_beam();
    virtual void draw_vertical_beam();

    virtual void redraw_horizontal_beam();
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

    /**
     * @brief set_vertical_image_data 设置编码器B扫的水平显示image数据
     * @param commonProperties
     */
    void set_horizontal_image_data(const BscanScene::S_CommonProperties &commonProperties);

private:
    QVector<S_WAVE_INFO>    m_waveVect;
    double                  m_offsetX;
    double                  m_currentX;

    bool is_equal(double value1, double value2);

};

#endif // __B_SCAN_ENCODER_SCENE_H__
