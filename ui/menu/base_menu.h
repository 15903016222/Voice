/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include <QStringList>

#include "ui_base_menu.h"
#include "spin_menu_item.h"

class BaseMenu : public QObject
{
    Q_OBJECT
public:
    explicit BaseMenu(Ui::BaseMenu *ui, QObject *parent = 0);
    virtual ~BaseMenu();

    virtual void show() = 0;
    virtual void hide() = 0;

protected:
    static QStringList s_onOff;

    Ui::BaseMenu *ui;
};

#endif // __BASE_MENU_H__
