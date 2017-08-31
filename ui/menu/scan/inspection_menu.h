#ifndef __INSPECTION_MENU_H__
#define __INSPECTION_MENU_H__

#include "../base_menu.h"

#include <source/scan.h>

namespace DplScanMenu {

class InspectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit InspectionMenu(QWidget *parent);

protected slots:
    void do_typeItem_changed(int pos);
    void do_scanItem_changed(int pos);
    void do_indexItem_changed(int pos);

protected:
    void update_scanItem();
    void update_indexItem();

private:
    ComboMenuItem *m_typeItem;
    ComboMenuItem *m_scanItem;
    ComboMenuItem *m_indexItem;
    SpinMenuItem *m_maxScanSpeedItem;
    SpinMenuItem *m_maxScanSpeedRPMItem;

    DplSource::Scan *m_scan;
};

}
#endif // __INSPECTION_MENU_H__
