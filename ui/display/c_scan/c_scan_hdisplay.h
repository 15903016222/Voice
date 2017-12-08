#ifndef __C_SCAN_HDISPLAY_H__
#define __C_SCAN_HDISPLAY_H__

#include "c_scan_display.h"

class CscanHDisplay : public CscanDisplay
{
public:
    explicit CscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

protected:
    void init_ruler();

};

#endif // __C_SCAN_HDISPLAY_H__
