#ifndef __C_SCAN_TIME_SCENE_H__
#define __C_SCAN_TIME_SCENE_H__

#include "c_scan_scene.h"

class CscanTimeScene : public CscanScene
{

public:
    explicit CscanTimeScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

protected:
    /**
     * @brief draw_vertical_beam    C扫的垂直显示
     */
    virtual void draw_vertical_beam();

    /**
     * @redraw_horizontal_beam 当显示大小改变，重新画垂直C扫
     */
    virtual void redraw_vertical_beam();

};

#endif // __C_SCAN_TIME_SCENE_H__
