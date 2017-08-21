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
    ~AngleMenu();

protected:
    void update_minAngleItem(const DplFocallaw::ScanCnfPointer &scanCnf);
    void update_maxAngleItem(const DplFocallaw::SectorialScanCnfPointer &scanCnf);
    void update_angleStepItem(const DplFocallaw::SectorialScanCnfPointer &scanCnf);

protected slots:
    void update(const DplDevice::GroupPointer &group);

private:
    SpinMenuItem *m_minAngleItem;
    SpinMenuItem *m_maxAngleItem;
    SpinMenuItem *m_angleStepItem;
    DplDevice::GroupPointer m_group;
};

}

#endif // __ANGLE_MENU_H__
