/**
 * @file tcg_menu.h
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __TCG_MENU_H__
#define __TCG_MENU_H__

#include "base_menu.h"

namespace DplGateCurvesMenu {

class TcgMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit TcgMenu(Ui::BaseMenu *ui, QObject *parent);
    ~TcgMenu();

    void show();
    void hide();

private:
    ComboMenuItem m_modeItem;

    /* Setting */
    SpinMenuItem m_curveNoItem;
    ComboMenuItem m_curveXItem;
    SpinMenuItem m_dbOffsetItem;
    ComboMenuItem m_switchItem;

    /* Edit */
    ComboMenuItem m_pointItem;
    SpinMenuItem m_positionItem;
    SpinMenuItem m_gainItem;
    LabelMenuItem m_addPointItem;
    LabelMenuItem m_deletePointItem;

    void show_setting();
    void hide_setting();

    void show_edit();
    void hide_edit();

private slots:
    void do_mode_event(int pos);
};

}
#endif // __TCG_MENU_H__
