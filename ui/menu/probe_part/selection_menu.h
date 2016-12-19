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

namespace DplProbeMenu {

class SelectionMenuprivate;
class SelectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    SelectionMenu(Ui::BaseMenu *ui, QObject *parent);

private slots:
    void do_probeItem_clicked();
    void do_wedgeItem_clicked();

private:
    SelectionMenuprivate *d;

};

}

#endif // SELECTIONMENU_H
