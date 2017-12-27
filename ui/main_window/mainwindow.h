#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "mcu/mcu.h"
#include "virtualkeyboard.h"
#include "../menu/main_menu/main_menu.h"
#include "../menu/sub_menu.h"

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void do_key_event(Mcu::KeyType type);

    void do_keyboard_event();

    void do_rotary_event(Mcu::RotaryType type);

protected:
    void load_style_sheet(const QString &fileName);

    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *event);

    void show_hidden_Menu();

private:
    Ui::MainWindow *ui;

    VirtualKeyboard *m_virtualKeyboard;

    MainMenu *m_mainMenu;
    SubMenu *m_subMenu;
};

#endif // MAINWINDOW_H
