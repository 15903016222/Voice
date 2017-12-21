#ifndef __C_SCAN_VDISPLAY_H__
#define __C_SCAN_VDISPLAY_H__

#include "c_scan_display.h"

class CscanVDisplay : public CscanDisplay
{
public:
    CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

protected slots:
    void resize_event(const QSize &size);

private:
    IndexRuler *m_indexRuler;
    ScanRuler *m_scanRuler;
};

#endif // __C_SCAN_VDISPLAY_H__
