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
#include "menu_item.h"

#define MAX_ITEMS   6

class BaseMenu : public QObject
{
    Q_OBJECT
public:
    explicit BaseMenu(Ui::BaseMenu *ui,
                      const MenuItem::Type types[MAX_ITEMS],
                      QObject *parent = 0);
    virtual ~BaseMenu();

    virtual void show();
    virtual void hide();

signals:

public slots:

protected:
    static QStringList s_onOff;

    MenuItem *m_menuItem[MAX_ITEMS];

    Ui::BaseMenu *ui;
};

#endif // __BASE_MENU_H__
