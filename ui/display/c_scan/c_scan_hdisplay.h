#ifndef __C_SCAN_HDISPLAY_H__
#define __C_SCAN_HDISPLAY_H__

#include "c_scan_display.h"

class CscanHDisplay : public CscanDisplay
{
public:
    explicit CscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);

protected slots:
    void resize_event(const QSize &size);

private:
    ScanRuler *m_scanRuler;
    IndexRuler *m_indexRuler;
};

#endif // __C_SCAN_HDISPLAY_H__
