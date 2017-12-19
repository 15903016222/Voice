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

    double start();

    double stop();

    void set_range(double start, double stop);

public slots:
    void update();

protected slots:
    void do_data_event(const DplSource::BeamsPointer &beams);

protected:
    double range() const;
    double time_range() const;
    double encoder_range() const;

    void resizeEvent(QResizeEvent *e);

private:
    DplSource::Scan *m_scan;
    DplSource::AxisPointer m_axis;
    DplDevice::GroupPointer m_group;
};

#endif // __SCAN_RULER_H__
