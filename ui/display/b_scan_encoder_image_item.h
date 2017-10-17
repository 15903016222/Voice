#ifndef __B_SCAN_ENCODER_IMAGE_ITEM_H__
#define __B_SCAN_ENCODER_IMAGE_ITEM_H__

#include <ui/display/encoder_image_item.h>

class BscanEncoderImageItem : public EncoderImageItem
{

public:
    explicit BscanEncoderImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

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
                                         const BaseImageItem::S_CommonProperties &commonProperties,
                                         BaseImageItem::E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);
};

#endif // __B_SCAN_ENCODER_IMAGE_ITEM_H__
