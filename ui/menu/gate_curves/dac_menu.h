/**
 * @file dac_menu.h
 * @brief dac menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __DAC_MENU_H__
#define __DAC_MENU_H__

#include "base_menu.h"

namespace DplGateCurvesMenu {

class DacMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit DacMenu(Ui::BaseMenu *ui, QObject *parent);
    ~DacMenu();

    void show();
    void hide();

private:
    MenuItem *m_modeItem;

    /* Setting */
    MenuItem *m_curveNoItem;
    MenuItem *m_curveXItem;
    MenuItem *m_dbOffsetItem;
    MenuItem *m_refGainItem;
    MenuItem *m_switchItem;

    /* Edit */
    MenuItem *m_pointItem;
    MenuItem *m_positionItem;
    MenuItem *m_addPointItem;
    MenuItem *m_deletePointItem;

    void show_setting();
    void hide_setting();
    void show_edit();
    void hide_edit();

private slots:
    void do_mode_event(int pos);
};

}
#endif // DACMENU_H
