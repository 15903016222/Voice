/**
 * @file tcg_menu.h
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __TCG_MENU_H__
#define __TCG_MENU_H__

#include "../base_menu.h"
#include <device/group.h>

namespace DplGateCurvesMenu {

class TcgMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit TcgMenu(QWidget *parent);

protected slots:
    void do_modeItem_changed(int pos);
    void do_switchItem_changed(int pos);
    void do_pointItem_changed(int val);
    void do_positionItem_changed(double val);
    void do_gainItem_changed(double val);
    void do_addPointItem_clicked();
    void do_deletePointItem_clicked();

    void do_current_beam_changed(int index);

    void update(const DplDevice::GroupPointer &group);

    void update_switchItem();
    void update_pointItem();
    void update_positionItem();
    void update_gainItem();

private:
    ComboMenuItem *m_modeItem;

    /* Setting */
    SpinMenuItem *m_curveNoItem;
    ComboMenuItem *m_curveXItem;
    SpinMenuItem *m_dbOffsetItem;
    ComboMenuItem *m_switchItem;

    /* Edit */
    ComboMenuItem *m_pointItem;
    SpinMenuItem *m_positionItem;
    SpinMenuItem *m_gainItem;
    LabelMenuItem *m_addPointItem;
    LabelMenuItem *m_deletePointItem;

    DplDevice::GroupPointer m_group;
};

}
#endif // __TCG_MENU_H__
