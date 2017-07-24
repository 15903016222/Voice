/**
 * @file dac_menu.h
 * @brief dac menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __DAC_MENU_H__
#define __DAC_MENU_H__

#include "../base_menu.h"

namespace DplGateCurvesMenu {

class DacMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit DacMenu(QWidget *parent);
    ~DacMenu();

private:
    ComboMenuItem *m_modeItem;

    /* Setting */
    SpinMenuItem *m_curveNoItem;
    ComboMenuItem *m_curveXItem;
    SpinMenuItem *m_dbOffsetItem;
    SpinMenuItem *m_refGainItem;
    ComboMenuItem *m_switchItem;

    /* Edit */
    ComboMenuItem *m_pointItem;
    SpinMenuItem *m_positionItem;
    LabelMenuItem *m_addPointItem;
    LabelMenuItem *m_deletePointItem;

    void show_setting();
    void hide_setting();
    void show_edit();
    void hide_edit();

private slots:
    void do_modeItem_changed(int pos);
};

}
#endif // DACMENU_H
