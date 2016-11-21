#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QTableView>

#include "lineeditdelegate.h"

namespace Ui {
class VirtualKeyboard;
}

class VirtualKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualKeyboard(QWidget *parent = 0);
    ~VirtualKeyboard();

private:
    Ui::VirtualKeyboard *ui;

    void input_number(QString string);

signals:
    void close_keyboard();

private slots:
    void do_click_button();
};

#endif // VIRTUALKEYBOARD_H
