#ifndef COMMONMENUBUTTON_H
#define COMMONMENUBUTTON_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class CommonMenuButton;
}

class CommonMenuButton : public QWidget
{
    Q_OBJECT

public:
    explicit CommonMenuButton(QWidget *parent = 0);
    ~CommonMenuButton();

private:
    Ui::CommonMenuButton *ui;

public:
    QList<QPushButton*> pushButton_commonMenu;

};

#endif // COMMONMENUBUTTON_H
