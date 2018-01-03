#ifndef __LAW_MENU_H__
#define __LAW_MENU_H__

#include "../base_menu.h"
#include "focallaw/focallawer.h"

#include <device/group.h>

namespace DplFocalLawMenu {

class LawConfigMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit LawConfigMenu(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_probe_changed(const DplFocallaw::ProbePointer &probe);

    void update_lawTypeItem();
    void update_pulserItem();
    void update_receiverItem();

    void do_lawTypeItem_changed(int index);
    void do_pulseItem_changed(double val);
    void do_receiverItem_changed(double val);

private:
    ComboMenuItem *m_lawTypeItem;
    SpinMenuItem *m_pulseItem;
    SpinMenuItem *m_receiverItem;
    ComboMenuItem *m_waveTypeItem;

    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::PaProbePointer m_probe;
};

}

#endif // __LAW_MENU_H__
