#ifndef __APETURE_MENU_ITEM_H__
#define __APETURE_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class ApetureMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    ApetureMenuItem(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_probe_changed(const DplFocallaw::ProbePointer &probe);
    void do_scan_changed(const DplFocallaw::ScanCnfPointer &scan);

    void update_value();

    void do_value_changed(double val);

protected:
    void language_changed();

private:
    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::PaProbePointer m_probe;
    DplFocallaw::ScanCnfPointer m_scan;
};

#endif // __APETURE_MENU_ITEM_H__
