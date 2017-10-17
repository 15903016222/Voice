#ifndef __C_SCAN_TIME_IMAGE_ITEM_H__
#define __C_SCAN_TIME_IMAGE_ITEM_H__

#include "time_image_item.h"
#include "c_scan_data.h"

class CscanTimeImageItem : public TimeImageItem
{

public:
    explicit CscanTimeImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseImageItem::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);

private:

    TestStub::C_SCAN_SOURCE     m_source;
    CScanDataPointer            m_cscanDataPointer;
    TestStub::THICKNESS_SOURCE  m_thicknessSource;

    bool gate_info_changed();
};

#endif // __C_SCAN_TIME_IMAGE_ITEM_H__
