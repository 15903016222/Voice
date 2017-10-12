#ifndef __TIME_SCENE_H__
#define __TIME_SCENE_H__

#include "base_scan_scene.h"

class TimeScene : public BaseScanScene
{
public:
    explicit TimeScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

protected:

    /**
     * @brief draw_vertical_beam    垂直显示
     */
    virtual void draw_vertical_beam();

    /**
     * @redraw_horizontal_beam 当显示大小改变，重新画垂直扫
     */
    virtual bool redraw_vertical_beam();

    /**
     * @brief draw_vertical_image   设置时间垂直显示image数据
     * @param beamsShowedCount
     * @param commonProperties
     * @param waveData
     */
    void draw_vertical_image(int beamsShowedCount,
                        const BaseScanScene::S_CommonProperties &commonProperties,
                                         const DplSource::BeamsPointer &beamsPointer);

    /**
     * @brief scroll_vertical_image     时间扫的垂直滚动image滚动实现
     * @param commonProperties
     */
    void scroll_vertical_image(const BaseScanScene::S_CommonProperties &commonProperties,
                               const DplSource::BeamsPointer &beamsPointer);


    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseScanScene::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer) = 0;


    double      m_currentTimeCount;
    double      m_pendingTimeCount;

};

#endif // __TIME_SCENE_H__
