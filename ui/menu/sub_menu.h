/**
 * @file sub_menu.h
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SUB_MENU_H__
#define __SUB_MENU_H__

#include "main_menu/main_menu.h"
#include "base_menu.h"
#include <QLayout>

class QStackedLayout;
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

private:
    QStackedLayout *m_layout;
};

inline BaseMenu *SubMenu::get_menu(MainMenu::Type type)
{
    return this->findChild<BaseMenu *>(QString::number(type));
}

#endif // SUB_MENU_H
