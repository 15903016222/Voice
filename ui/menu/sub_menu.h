#ifndef SUB_MENU_H
#define SUB_MENU_H

#include "menu_item.h"
#include "menu_config.h"

#include <QWidget>

namespace Ui {
class SubMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

private:
    Ui::SubMenu *ui;
    void set_third_menu_content(MenuItem *widget, QVariantMap map);

    MenuConfig *menuConfig;

private slots:
    void set_third_menu(QString str1, QString str2);

};

#endif // SUB_MENU_H
