#ifndef __APETURE_MENU_H__
#define __APETURE_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

namespace DplFocalLawMenu {

class ApetureMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ApetureMenu(QWidget *parent);
    ~ApetureMenu();

protected:
    void update_apetureItem(const DplFocallaw::ScanCnfPointer &scanCnf);
    void update_firstElementItem(const DplFocallaw::ScanCnfPointer &scanCnf);
    void update_lastElementItem(const DplFocallaw::LinearScanCnfPointer &scanCnf);
    void update_elementStep(const DplFocallaw::LinearScanCnfPointer &scanCnf);

protected slots:
    void update(const DplDevice::GroupPointer &group);

private:
    SpinMenuItem *m_apetureItem;
    SpinMenuItem *m_firstElementItem;
    SpinMenuItem *m_lastElementItem;
    SpinMenuItem *m_elementStep;
    DplDevice::GroupPointer m_group;
};

}
#endif // __APETURE_MENU_H__
