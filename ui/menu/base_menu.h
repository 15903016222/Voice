/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include "menu_item/spin_menu_item.h"
#include "menu_item/combo_menu_item.h"
#include "menu_item/label_menu_item.h"

namespace Ui {
class BaseMenu;
}

class BaseMenu : public QWidget
{
    Q_OBJECT
public:
    explicit BaseMenu(QWidget *parent = 0);
    virtual ~BaseMenu();

protected:
    static QStringList s_onOff;
    Ui::BaseMenu *ui;
};


#endif // __BASE_MENU_H__
