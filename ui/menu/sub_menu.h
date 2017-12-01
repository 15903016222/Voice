/**
 * @file sub_menu.h
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SUB_MENU_H__
#define __SUB_MENU_H__

#include "main_menu.h"
#include "base_menu.h"
#include <QLayout>

class SubMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

    BaseMenu *get_menu(MainMenu::Type type);

public slots:
    void set_menu(MainMenu::Type type);
    void set_opacity_main_menu(double value);

protected:
    void create_menus();

    void add_menu(MainMenu::Type type, BaseMenu *menu);

private:
    BaseMenu *m_curMenu;
};

inline BaseMenu *SubMenu::get_menu(MainMenu::Type type)
{
    return this->findChild<BaseMenu *>(QString::number(type));
}

inline void SubMenu::add_menu(MainMenu::Type type, BaseMenu *menu)
{
    menu->setObjectName(QString::number(type));
    layout()->addWidget(menu);
}

#endif // SUB_MENU_H
