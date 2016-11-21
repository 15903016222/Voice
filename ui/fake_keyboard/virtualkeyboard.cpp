#include "virtualkeyboard.h"
#include "ui_virtualkeyboard.h"

#include "vinput.h"

#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

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

    for(int i = 1; i < 6; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(do_click_button()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
}

VirtualKeyboard::~VirtualKeyboard()
{
    delete ui;
}

void VirtualKeyboard::do_click_button()
{
    QString string;
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    if(pushButton->objectName() == "pushButton_3") {
        string = "Left";
    } else if(pushButton->objectName() == "pushButton_4") {
        string = "Right";
    } else {
        string = pushButton->text();
    }
    input_number(string);
    if(string == "Enter") {
//        close();
        qDebug() << "enter";
        hide();
//        emit close_keyboard();
    }  
}

void VirtualKeyboard::input_number(QString string)
{
//    VInput::Key key;
    if(string == ".") {
        VInput::get_vinput()->send(VInput::Key_Dot);
    } else if(string == "Left") {
        VInput::get_vinput()->send(VInput::Key_Left);
    } else if(string == "Right") {
        VInput::get_vinput()->send(VInput::Key_Right);
    } else if(string == "Del") {
        VInput::get_vinput()->send(VInput::Key_Backspace);
    } else if(string == "Enter" || string == "Close") {
        VInput::get_vinput()->send(VInput::Key_Enter);
    } else  if(string == "0") {
        VInput::get_vinput()->send(VInput::Key_0);
    } else if(string == "1") {
        VInput::get_vinput()->send(VInput::Key_1);
    } else if(string == "2") {
        VInput::get_vinput()->send(VInput::Key_2);
    } else if(string == "3") {
        VInput::get_vinput()->send(VInput::Key_3);
    } else if(string == "4") {
        VInput::get_vinput()->send(VInput::Key_4);
    } else if(string == "5") {
        VInput::get_vinput()->send(VInput::Key_5);
    } else if(string == "6") {
        VInput::get_vinput()->send(VInput::Key_6);
    } else if(string == "7") {
        VInput::get_vinput()->send(VInput::Key_7);
    } else if(string == "8") {
        VInput::get_vinput()->send(VInput::Key_8);
    } else if(string == "9") {
        VInput::get_vinput()->send(VInput::Key_9);
    }
}


