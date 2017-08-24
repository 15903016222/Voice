#ifndef __B_SCAN_ENCODER_SCENE_H__
#define __B_SCAN_ENCODER_SCENE_H__

#include <ui/display/b_scan_scene.h>

class BscanEncoderScene : public BscanScene
{
public:
    explicit BscanEncoderScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent = 0);

protected:
    virtual void draw_horizontal_beam();
    virtual void draw_vertical_beam();
};

#endif // __B_SCAN_ENCODER_SCENE_H__
