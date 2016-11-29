#ifndef SUB_MENU_H
#define SUB_MENU_H

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
};

#endif // SUB_MENU_H
