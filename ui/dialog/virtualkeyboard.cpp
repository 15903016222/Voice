#include "virtualkeyboard.h"
#include "ui_virtualkeyboard.h"

#include "vinput.h"

#include <QPushButton>
#include <QDebug>

VirtualKeyboard::VirtualKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualKeyboard)
{
    ui->setupUi(this);

    for(int i = 1; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("panelButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(do_click_button()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    for(int i = 1; i < 6; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
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
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    int value = pushButton->text().toInt();
    VInput::Key key = VInput::Key_1;
    VInput::instance()->send((VInput::Key)(key + value - 1));
}

void VirtualKeyboard::on_panelButton_0_clicked()
{
    VInput::instance()->send(VInput::Key_0);
}

void VirtualKeyboard::on_pushButton_1_clicked()
{
    qDebug() << ".";
    VInput::instance()->send(VInput::Key_Dot);
}

void VirtualKeyboard::on_pushButton_2_clicked()
{
    VInput::instance()->send(VInput::Key_Backspace);
}

void VirtualKeyboard::on_pushButton_3_clicked()
{
    VInput::instance()->send(VInput::Key_Left);
}

void VirtualKeyboard::on_pushButton_4_clicked()
{
    VInput::instance()->send(VInput::Key_Right);
}

void VirtualKeyboard::on_pushButton_5_clicked()
{
    VInput::instance()->send(VInput::Key_Enter);
//    hide();
//    emit close_keyboard();
}

void VirtualKeyboard::on_pushButton_6_clicked()
{
    VInput::instance()->send(VInput::Key_Minus);
}

void VirtualKeyboard::on_pushButton_7_clicked()
{
    VInput::instance()->send(VInput::Key_Esc);
    hide();
    emit close_keyboard();
}
