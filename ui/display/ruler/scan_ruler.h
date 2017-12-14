#ifndef __SCAN_RULER_H__
#define __SCAN_RULER_H__

#include "ruler.h"

#include <device/group.h>
#include <source/scan.h>

class ScanRuler : public Ruler
{
    Q_OBJECT
public:
    ScanRuler(const DplDevice::GroupPointer &grp, MarkPostion pos, QWidget *parent);

protected slots:
    void do_data_event(const DplSource::BeamsPointer &beams);

protected:
    double range() const;

private:
    DplSource::Scan *m_scan;
    DplSource::AxisPointer m_axis;
    DplDevice::GroupPointer m_group;
};

#endif // __SCAN_RULER_H__
