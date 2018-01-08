#ifndef __FOCAL_POINT_MENU_H__
#define __FOCAL_POINT_MENU_H__

#include "../base_menu.h"

#include <device/group.h>

namespace DplFocalLawMenu {

class FocalPointMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FocalPointMenu(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_focus_changed(const DplFocallaw::FocusPointer &focus);

    void update_typeItem();
    void update_offsetStartItem();
    void update_offsetEndItem();
    void update_depthStartItem();
    void update_depthEndItem();

    void do_typeItem_changed(int i);
    void do_offsetStartItem_changed(double val);
    void do_offsetEndItem_changed(double val);
    void do_depthStartItem_changed(double val);
    void do_depthEndItem_changed(double val);

protected:
    void changeEvent(QEvent *e);

private:
    ComboMenuItem *m_typeItem;
    SpinMenuItem *m_offsetStartItem;
    SpinMenuItem *m_offsetEndItem;
    SpinMenuItem *m_depthStartItem;
    SpinMenuItem *m_depthEndItem;

    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::FocusPointer m_focus;
};

}
#endif // __FOCAL_POINT_MENU_H__
