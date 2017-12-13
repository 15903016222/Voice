#ifndef __B_SCAN_VDISPLAY_H__
#define __B_SCAN_VDISPLAY_H__

#include "b_scan_display.h"

class BscanVDisplay : public BscanDisplay
{
public:
    BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

protected:
    void init_ruler();
};

#endif // __B_SCAN_VDISPLAY_H__