#ifndef __AREA_MENU_H__
#define __AREA_MENU_H__

#include "../base_menu.h"
#include <source/scan.h>

namespace DplScanMenu {

class AreaMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit AreaMenu(QWidget *parent);
    ~AreaMenu();

protected slots:
    void do_scanStartItem_changed(double val);
    void do_scanEndItem_changed(double val);
    void do_scanResolutionItem_changed(double val);
    void do_indexStartItem_changed(double val);
    void do_indexEndItem_changed(double val);
    void do_indexResolutionItem_changed(double val);

    void do_scan_mode_changed(DplSource::Scan::Mode mode);

private:
    SpinMenuItem *m_scanStartItem;
    SpinMenuItem *m_scanEndItem;
    SpinMenuItem *m_scanResolutionItem;
    SpinMenuItem *m_indexStartItem;
    SpinMenuItem *m_indexEndItem;
    SpinMenuItem *m_indexResolutionItem;

    DplSource::AxisPointer m_scanAxis;
    DplSource::AxisPointer m_indexAxis;
};

}
#endif // __AREA_MENU_H__
