#ifndef __B_SCAN_HDISPLAY_H__
#define __B_SCAN_HDISPLAY_H__

#include "b_scan_display.h"

class BscanHDisplay : public BscanDisplay
{
public:
    BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

protected slots:
   void resize_event(const QSize &size);

private:
   UtRuler *m_utRuler;
   ScanRuler *m_scanRuler;
};

#endif // __B_SCAN_HDISPLAY_H__
