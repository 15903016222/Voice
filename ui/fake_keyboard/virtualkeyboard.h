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

    void input_number_to_lineedit(QLineEdit *lineEdit, QString string, int decimal);
    void open_persistent_editor(QStandardItemModel *model, QTableView *tableView, int index);
    void close_persistent_editor(QStandardItemModel *model, QTableView *tableView, int index);
    void input_lineedit_data(QTableView *tableView, QString string, int index);

private:
    Ui::VirtualKeyboard *ui;

signals:
    void input_number(QString string);
    void close_keyboard();

private slots:
    void do_click_button();
};

#endif // VIRTUALKEYBOARD_H
