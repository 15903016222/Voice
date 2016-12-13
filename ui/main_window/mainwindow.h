#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "mcu.h"
#include "virtualkeyboard.h"
#include "main_menu.h"
#include "sub_menu.h"

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

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *moveEvent);
    void keyPressEvent(QKeyEvent *event);

signals:

protected slots:
    void do_key_event(Mcu::KeyType type);

    void update_translator(QString string);
    void do_keyboard_event();
    void slot_keyboard_close_clicked();
    void slot_setMenuOpacity(double value);

    void do_rotary_event(Mcu::RotaryType type);

private:
    Ui::MainWindow *ui;

    QTranslator *translator;
    QGraphicsOpacityEffect *effect;

    VirtualKeyboard *pVirtualKeyboard;

    MainMenu *mainMenu;
    SubMenu *subMenu;

    bool m_hiddenFirstSecondMenuFlag;
    bool m_hiddenThirdMenuFlag;
    bool m_hiddenCommonMenuFlag;
    bool m_hiddenArrowFlag;
    bool m_hiddenKeyboardFlag;
    void show_hidden_Menu();

};

#endif // MAINWINDOW_H
