#ifndef __LAW_MENU_H__
#define __LAW_MENU_H__

#include "base_menu.h"
#include "focallaw/focallawer.h"

#include <device/group.h>

namespace DplFocalLawMenu {

class LawConfigMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit LawConfigMenu(Ui::BaseMenu *ui, QObject *parent);
    ~LawConfigMenu();

    void show();
    void hide();

private:
    bool m_updateFlga;

    ComboMenuItem m_lawTypeItem;
    SpinMenuItem m_pulseItem;
    SpinMenuItem m_receiverItem;
    ComboMenuItem m_waveTypeItem;

    DplFocallaw::PaProbePointer m_probePtr;
    DplFocallaw::ScanCnfPointer m_scanScnPtr;

    void update();

private slots:
    void do_lawTypeItem_changed(int index);
    void do_pulseItem_changed(double val);
    void do_receiverItem_changed(double val);

    void do_current_group_changed(const DplDevice::GroupPointer &group);
};

}

#endif // __LAW_MENU_H__
