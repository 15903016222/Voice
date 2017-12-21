#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "mcu/mcu.h"
#include "virtualkeyboard.h"
#include "../menu/main_menu/main_menu.h"
#include "../menu/sub_menu.h"

#include <device/group.h>

#include <QMainWindow>
#include <QTranslator>
#include <QGraphicsOpacityEffect>

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
    void update(const DplDevice::GroupPointer &group);
    void update_angleMenuItem();

    void do_key_event(Mcu::KeyType type);

    void do_keyboard_event();

    void do_rotary_event(Mcu::RotaryType type);

    void do_angleMenuItem_value_changed(double val);

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

    DplDevice::GroupPointer m_group;
};

#endif // MAINWINDOW_H
