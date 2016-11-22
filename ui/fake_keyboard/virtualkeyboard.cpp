#include "virtualkeyboard.h"
#include "ui_virtualkeyboard.h"

#if (PHASCAN | PHASCAN_II)
#include "vinput.h"
#endif

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
#if (PHASCAN | PHASCAN_II)
    VInput::Key key = VInput::Key_1;
    VInput::get_vinput()->send((VInput::Key)(key + value - 1));
#endif
}

#if (PHASCAN | PHASCAN_II)
void VirtualKeyboard::on_panelButton_0_clicked()
{
    VInput::get_vinput()->send(VInput::Key_0);
}

void VirtualKeyboard::on_pushButton_1_clicked()
{
    VInput::get_vinput()->send(VInput::Key_Dot);
}

void VirtualKeyboard::on_pushButton_2_clicked()
{
    VInput::get_vinput()->send(VInput::Key_Backspace);
}

void VirtualKeyboard::on_pushButton_3_clicked()
{
    VInput::get_vinput()->send(VInput::Key_Left);
}

void VirtualKeyboard::on_pushButton_4_clicked()
{
    VInput::get_vinput()->send(VInput::Key_Right);
}
#endif

void VirtualKeyboard::on_pushButton_5_clicked()
{
#if (PHASCAN | PHASCAN_II)
    VInput::get_vinput()->send(VInput::Key_Enter);
#endif
    hide();
    emit close_keyboard();
}
