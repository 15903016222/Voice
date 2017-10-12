#ifndef __C_SCAN_ENCODER_SCENE_H__
#define __C_SCAN_ENCODER_SCENE_H__

#include "encoder_scene.h"
#include "c_scan_data.h"

class CscanEncoderScene : public EncoderScene
{
public:

    CscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseScanScene::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);
private:
    CScanDataPointer    m_cscanDataPointer;

};

#endif // __C_SCAN_ENCODER_SCENE_H__
