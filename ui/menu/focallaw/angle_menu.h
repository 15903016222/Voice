#ifndef __ANGLE_MENU_H__
#define __ANGLE_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

namespace DplFocalLawMenu {

class AngleMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AngleMenu(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_probe_changed(const DplFocallaw::ProbePointer &probe);
    void do_scan_changed(const DplFocallaw::ScanCnfPointer &scan);

    void update_minAngleItem();
    void update_maxAngleItem();
    void update_angleStepItem();

    void do_minAngleItem_changed(double val);
    void do_maxAngleItem_changed(double val);
    void do_angleStepItem_changed(double val);

protected:
    void changeEvent(QEvent *e);

private:
    SpinMenuItem *m_minAngleItem;
    SpinMenuItem *m_maxAngleItem;
    SpinMenuItem *m_angleStepItem;
    DplDevice::GroupPointer m_group;

    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::PaProbePointer m_probe;
    DplFocallaw::ScanCnfPointer m_scan;
};

}

#endif // __ANGLE_MENU_H__
