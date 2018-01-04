#ifndef __LAW_MENU_H__
#define __LAW_MENU_H__

#include "../base_menu.h"
#include "focallaw/focallawer.h"

#include <device/group.h>

class PulserMenuItem;

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
    void update_receiverItem();
    void update_waveTypeItem();

    void do_lawTypeItem_changed(int index);
    void do_receiverItem_changed(double val);

protected:
    void changeEvent(QEvent *e);

private:
    ComboMenuItem *m_lawTypeItem;
    PulserMenuItem *m_pulseItem;
    SpinMenuItem *m_receiverItem;
    ComboMenuItem *m_waveTypeItem;

    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::PaProbePointer m_probe;
};

}

#endif // __LAW_MENU_H__
