#ifndef __B_SCAN_ENCODER_SCENE_H__
#define __B_SCAN_ENCODER_SCENE_H__

#include <ui/display/encoder_scene.h>

class BscanEncoderScene : public EncoderScene
{

public:
    explicit BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

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
                                         const DplSource::BeamsPointer &beamsPointer);
};

#endif // __B_SCAN_ENCODER_SCENE_H__
