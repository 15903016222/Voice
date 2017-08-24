#ifndef __B_SCAN_HDISPLAY_H__
#define __B_SCAN_HDISPLAY_H__

#include "b_scan_display.h"

class BscanHDisplay : public BscanDisplay
{
public:
    BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

    virtual bool set_scan_type(BscanDisplay::E_SCAN_TYPE type);

protected:
    virtual void init_ruler();
};

#endif // __B_SCAN_HDISPLAY_H__
