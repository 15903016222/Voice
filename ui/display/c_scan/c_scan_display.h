#ifndef __C_SCAN_DISPLAY_H__
#define __C_SCAN_DISPLAY_H__

#include "../base/scan_display.h"

#include <device/group.h>

class ScanRuler;
class IndexRuler;
class CscanItem;

class CscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit CscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~CscanDisplay();

signals:

public slots:
    void resize_event(const QSize &size);

protected:
    DplDevice::GroupPointer m_group;
    CscanItem *m_cscanItem;
};

#endif // __C_SCAN_DISPLAY_H__
