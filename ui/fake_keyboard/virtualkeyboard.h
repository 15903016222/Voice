#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>

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
#if (PHASCAN | PHASCAN_II)
    void on_panelButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
#endif
    void on_pushButton_5_clicked();
};

#endif // VIRTUALKEYBOARD_H
