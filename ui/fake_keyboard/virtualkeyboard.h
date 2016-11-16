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

#ifdef Q_OS_WIN32
    void input_number_windows(HWND hwnd, QString string, int decimal);
#endif
#ifdef Q_OS_LINUX
    void input_number_linux(QString string, int decimal);
#endif

private:
    Ui::VirtualKeyboard *ui;

signals:
    void input_number(QString string);
    void close_keyboard();

private slots:
    void do_click_button();
};

#endif // VIRTUALKEYBOARD_H
