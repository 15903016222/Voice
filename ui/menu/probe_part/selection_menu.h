/**
 * @file probe_selection_menu.h
 * @brief Probe/Part Select Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#ifndef __PROBE_SELECTION_MENU_H__
#define __PROBE_SELECTION_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

namespace DplProbeMenu {

class SelectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SelectionMenu(QWidget *parent);
    ~SelectionMenu();

private slots:
    void do_probeItem_clicked();
    void do_wedgeItem_clicked();
    void do_groupModeItem_changed(int index);

    void update(const DplDevice::GroupPointer &group);

private:
    ComboMenuItem *m_groupItem;
    ComboMenuItem *m_modeItem;
    LabelMenuItem *m_probeItem;
    LabelMenuItem *m_wedgeItem;
    ComboMenuItem *m_autoDetectItem;

    DplDevice::GroupPointer m_group;
};

}

#endif // SELECTIONMENU_H
