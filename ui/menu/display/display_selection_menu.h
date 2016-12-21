/**
 * @file selection_menu.h
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __DISPLAY_SELECTION_MENU_H__
#define __DISPLAY_SELECTION_MENU_H__

#include "base_menu.h"

namespace DplDisplayMenu {

class SelectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SelectionMenu(Ui::BaseMenu *ui, QObject *parent);
    ~SelectionMenu();

    void show();
    void hide();

private:
    MenuItem *m_groupItem;
    MenuItem *m_displayItem;
    MenuItem *m_cSourceitem;
    MenuItem *m_minThicknessItem;
    MenuItem *m_maxThicknessItem;
    MenuItem *m_dataCompressionItem;
};

}
#endif // __DISPLAY_SELECTION_MENU_H__