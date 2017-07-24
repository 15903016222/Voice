/**
 * @file selection_menu.h
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __DISPLAY_SELECTION_MENU_H__
#define __DISPLAY_SELECTION_MENU_H__

#include "../base_menu.h"

namespace DplDisplayMenu {

class SelectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SelectionMenu(QWidget *parent = 0);
    ~SelectionMenu();

    void show();
    void hide();

protected slots:
    void do_displayItem_clicked();

private:
    LabelMenuItem *m_displayItem;
    ComboMenuItem *m_cSourceItem;
    SpinMenuItem *m_minThicknessItem;
    SpinMenuItem *m_maxThicknessItem;
    ComboMenuItem *m_dataCompressionItem;
};

}
#endif // __DISPLAY_SELECTION_MENU_H__
