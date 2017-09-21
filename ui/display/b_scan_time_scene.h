#ifndef __B_SCAN_TIME_SCENE_H__
#define __B_SCAN_TIME_SCENE_H__

#include <ui/display/b_scan_scene.h>

class BscanTimeScene : public BscanScene
{
public:
    explicit BscanTimeScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent = 0);
    virtual bool need_refresh();
protected:

    virtual void draw_vertical_beam();
    virtual void redraw_vertical_beam();
};

#endif // __B_SCAN_TIME_SCENE_H__
