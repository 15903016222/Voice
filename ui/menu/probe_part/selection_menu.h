/**
 * @file probe_selection_menu.h
 * @brief Probe/Part Select Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#ifndef __PROBE_SELECTION_MENU_H__
#define __PROBE_SELECTION_MENU_H__

#include "base_menu.h"
#include <device/device.h>

namespace DplProbeMenu {

class SelectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SelectionMenu(Ui::BaseMenu *ui, QObject *parent);
    ~SelectionMenu();

    void show();
    void hide();

private slots:
    void do_probeItem_clicked();
    void do_wedgeItem_clicked();
    void do_groupModeItem_changed(int index);
    void do_current_group_changed(const DplDevice::GroupPointer &group);

private:
    bool m_updateFlag;

    ComboMenuItem m_groupItem;
    ComboMenuItem m_modeItem;
    LabelMenuItem m_probeItem;
    LabelMenuItem m_wedgeItem;
    ComboMenuItem m_autoDetectItem;

    DplDevice::GroupPointer m_group;

    void update();
};

}

#endif // SELECTIONMENU_H
