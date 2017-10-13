#ifndef __B_SCAN_TIME_SCENE_H__
#define __B_SCAN_TIME_SCENE_H__

//#include <ui/display/b_scan_scene.h>
#include <ui/display/time_scene.h>

class BscanTimeScene : public TimeScene//BscanScene
{
public:
    explicit BscanTimeScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);
    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:

    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseScanScene::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);
};

#endif // __B_SCAN_TIME_SCENE_H__
