#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private:
    Ui::MainMenu *ui;
};

#endif // MAIN_MENU_H
