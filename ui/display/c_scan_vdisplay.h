#ifndef __C_SCAN_VDISPLAY_H__
#define __C_SCAN_VDISPLAY_H__

#include "c_scan_display.h"

class CscanVDisplay : public CscanDisplay
{
public:
    CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

protected:
    virtual void init_ruler();

};

#endif // __C_SCAN_VDISPLAY_H__
