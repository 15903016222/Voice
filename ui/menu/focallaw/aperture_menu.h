#ifndef __aperture_MENU_H__
#define __aperture_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

namespace DplFocalLawMenu {

class ApertureMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ApertureMenu(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_probe_changed(const DplFocallaw::ProbePointer &probe);
    void do_scan_changed(const DplFocallaw::ScanCnfPointer &scan);

    void update_apertureItem();
    void update_firstElementItem();
    void update_lastElementItem();
    void update_stepMenuItem();

    void do_apertureItem_changed(double val);
    void do_firstElementItem_changed(double val);
    void do_lastElementItem_changed(double val);
    void do_stepItem(double val);

protected:
    void changeEvent(QEvent *e);

private:
    SpinMenuItem *m_apertureItem;
    SpinMenuItem *m_firstElementItem;
    SpinMenuItem *m_lastElementItem;
    SpinMenuItem *m_stepmenuItem;

    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::PaProbePointer m_probe;
    DplFocallaw::ScanCnfPointer m_scan;
};

}
#endif // __aperture_MENU_H__
