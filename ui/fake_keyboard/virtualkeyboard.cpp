#include "virtualkeyboard.h"
#include "ui_virtualkeyboard.h"

#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

#ifdef Q_OS_WIN32
#include "windows.h"
#endif

#ifdef Q_OS_LINUX
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/XInput.h>
#include <X11/keysym.h>
#endif

VirtualKeyboard::VirtualKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualKeyboard)
{
    ui->setupUi(this);

    for(int i = 0; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("panelButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(do_click_button()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    for(int i = 1; i < 7; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(do_click_button()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

//#if QT_VERSION >= 0x050000
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::Tool);
//#endif

//#if QT_VERSION < 0x050000
//    setAttribute(Qt::WA_ShowWithoutActivating, true);
//    myInputPanelDlg->setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
//#endif
}

VirtualKeyboard::~VirtualKeyboard()
{
    delete ui;
}

void VirtualKeyboard::do_click_button()
{
    QString string;
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    if(pushButton->objectName() == "pushButton_4") {
        string = "Left Arrow";
    } else if(pushButton->objectName() == "pushButton_5") {
        string = "Right Arrow";
    } else {
        string = pushButton->text();
    }
    emit input_number(string);
    if(string == "Enter") {
        close();
        emit close_keyboard();
    }
}

#ifdef Q_OS_WIN32
void VirtualKeyboard::input_number_windows(HWND hwnd, QString string, int decimal)
{
    if(string == "." && decimal > 0) {
        SendMessage(hwnd, WM_KEYDOWN, VK_DECIMAL, 0);
    } else if(string == "Left Arrow") {
        SendMessage(hwnd, WM_KEYDOWN, VK_LEFT, 0);
    } else if(string == "Right Arrow") {
        SendMessage(hwnd, WM_KEYDOWN, VK_RIGHT, 0);
    } else if(string == "BackSpace") {
        SendMessage(hwnd, WM_KEYDOWN, VK_BACK, 0);
    } else if(string == "Delete") {
        SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 0);
    } else if(string == "Enter" || string == "Close") {
        SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
    } else {
        int value = string.toInt();
        SendMessage(hwnd, WM_KEYDOWN, VK_HELP + value + 1, 0);
    }
}
#endif

#ifdef Q_OS_LINUX
void VirtualKeyboard::input_number_linux(QString string, int decimal)
{
    Display *display = XOpenDisplay (NULL);
    KeySym keysym;

    if(display == NULL) {
        qDebug() << "Display id Null.";
    }

    if(string == "." && decimal > 0) {
        keysym = XK_KP_Decimal;
    } else if(string == "Left Arrow") {
        keysym = XK_Left;
    } else if(string == "Right Arrow") {
        keysym = XK_Right;
    } else if(string == "BackSpace") {
        keysym = XK_BackSpace;
    } else if(string == "Delete") {
        keysym = XK_Delete;
    } else if(string == "Enter" || string == "Close") {
        keysym = XK_Return;
    } else {
        int value = string.toInt();
        keysym = XK_0 + value;
    }

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, keysym), True, CurrentTime);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, keysym), False, CurrentTime);
    XCloseDisplay(display);
}
#endif

void VirtualKeyboard::input_number_to_lineedit(QLineEdit *lineEdit, QString string, int decimal)
{
    QKeyEvent *event;
    if(string == "." && decimal > 0) {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Period, Qt::NoModifier);
    } else if(string == "Left Arrow") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    } else if(string == "Right Arrow") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    } else if(string == "BackSpace") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    } else if(string == "Delete") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
    } else if(string == "Enter" || string == "Close") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    } else {
        int value = string.toInt();
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_0 + value, Qt::NoModifier);
    }
    QApplication::sendEvent(lineEdit, event);
}
