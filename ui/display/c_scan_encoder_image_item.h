#ifndef __C_SCAN_ENCODER_IMAGE_ITEM_H__
#define __C_SCAN_ENCODER_IMAGE_ITEM_H__

#include "encoder_image_item.h"
#include "c_scan_data.h"

class CscanEncoderImageItem : public EncoderImageItem
{
public:

    CscanEncoderImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseImageItem::S_CommonProperties &commonProperties,
                                         BaseImageItem::E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);
private:
    CScanDataPointer    m_cscanDataPointer;

};

#endif // __C_SCAN_ENCODER_IMAGE_ITEM_H__
