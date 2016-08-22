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
    QList<QPushButton*> commonMenuButton;

private:
    Ui::CommonMenuButton *ui;
};

#endif // COMMONMENUBUTTON_H
