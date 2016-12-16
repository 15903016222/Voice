/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include <QObject>
#include <QStringList>

#include "ui_sub_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"

class BaseMenu : public QObject
{
    Q_OBJECT
public:
    explicit BaseMenu(Ui::SubMenu *ui, QObject *parent = 0);
    virtual void show() = 0;
    virtual void hide() = 0;

signals:

public slots:

protected:
    static QStringList s_onOff;

    Ui::SubMenu *ui;
};

#endif // __BASE_MENU_H__
