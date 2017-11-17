#ifndef __B_SCAN_TIME_IMAGE_ITEM_H__
#define __B_SCAN_TIME_IMAGE_ITEM_H__

#include <ui/display/time_image_item.h>

class BscanTimeImageItem : public TimeImageItem
{
public:
    explicit BscanTimeImageItem(const DplDisplay::PaletteColorPointer &palette,
                                const DplDevice::GroupPointer &grp,
                                QGraphicsObject *parent = 0);

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseImageItem::S_CommonProperties &commonProperties,
                                         BaseImageItem::E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);
};

#endif // __B_SCAN_TIME_IMAGE_ITEM_H__
