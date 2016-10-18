#include "inputpanelcontext.h"
#include "ui_inputpanelcontext.h"

#include <QPushButton>
#include <QTextCursor>
#include <QDebug>

InputPanelContext::InputPanelContext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPanelContext)
{
    ui->setupUi(this);

    capsLock = true;
    on_pushButton_capsLock_clicked();

    for(int i = 0; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    for(int i = 1; i <= 28; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("symbol_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    for(int i = 0; i < 3; i ++ ) {
        QFrame *frame = findChild<QFrame*>("frame_" + QString::number(i));
        frame->setStyleSheet("QWidget QPushButton{font: bold 12pt 'Times New Roman';}");
    }

    for(int i = 65; i <= 90; i ++) {
        QString string = (QChar)i;
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    ui->pushButton_alt->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_arrow_down->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_arrow_left->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_arrow_right->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_arrow_up->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_BackSpace->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_capsLock->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_Enter->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_Shift->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_Space->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_Tab->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ctrl->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_cancel->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ok->setFocusPolicy(Qt::NoFocus);

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(show_cursor()));
}

InputPanelContext::~InputPanelContext()
{
    delete ui;
}

void InputPanelContext::edit_text()
{
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertText(pushButton->text());
}

void InputPanelContext::on_pushButton_capsLock_clicked()
{
    for(int i = 65; i <= 90; i ++) {
        QString string = (QChar)i;
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);

        if(capsLock){
            ui->pushButton_capsLock->setStyleSheet("background-color: rgb(0, 170, 0)");
            pushButton->setText((QChar)(i));
        } else{
            ui->pushButton_capsLock->setStyleSheet("background-color: rgb(175, 175, 175)");
            pushButton->setText((QChar)(i + 32));
        }
    }
    capsLock = !capsLock;
}

void InputPanelContext::on_pushButton_Space_clicked()
{
    QString text = ui->textEdit->toPlainText();
    ui->textEdit->setText(text + " ");
}

void InputPanelContext::on_pushButton_BackSpace_clicked()
{
    QString text = ui->textEdit->toPlainText();
    if(text != NULL) {
        QTextCursor cursor = ui->textEdit->textCursor();
        if(cursor.position() == 0) {
            return;
        } else {
            if(cursor.hasSelection()) {
                cursor.clearSelection();
            }
            cursor.deletePreviousChar();
            ui->textEdit->setTextCursor(cursor);
        }
    }
}

void InputPanelContext::on_pushButton_ok_clicked()
{
    QString text = ui->textEdit->toPlainText();
    close();
    emit textEditFinished(text);
}

void InputPanelContext::set_item_current_text(QString string)
{
    ui->textEdit->setText(string);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}

void InputPanelContext::on_pushButton_arrow_left_clicked()
{
    ui->textEdit->setFocus();
    if(ui->textEdit->toPlainText() != NULL && ui->textEdit->textCursor().position() != 0) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Left);
        ui->textEdit->setTextCursor(cursor);
    }
}

void InputPanelContext::on_pushButton_arrow_right_clicked()
{
    ui->textEdit->setFocus();
    if(ui->textEdit->toPlainText() != NULL && ui->textEdit->textCursor().position() != ui->textEdit->toPlainText().length()) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Right);
        ui->textEdit->setTextCursor(cursor);
    }
}
void InputPanelContext::on_pushButton_arrow_up_clicked()
{
    ui->textEdit->setFocus();
    if(ui->textEdit->document()->lineCount() > 0) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Up);
        ui->textEdit->setTextCursor(cursor);
    }
}

void InputPanelContext::on_pushButton_arrow_down_clicked()
{
    ui->textEdit->setFocus();
    if(ui->textEdit->document()->lineCount() > 0) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Down);
        ui->textEdit->setTextCursor(cursor);
    }
}

void InputPanelContext::show_cursor()
{
    ui->textEdit->setFocus();
}


