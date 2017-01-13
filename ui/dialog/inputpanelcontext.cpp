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

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    m_capsLock = true;
    on_pushButton_capsLock_clicked();

    for(int i = 0; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

    for(int i = 1; i <= 28; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("symbol_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

    for(int i = 65; i <= 90; i ++) {
        QString string = (QChar)i;
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(show_cursor()));

    ui->widget_2->show();
    ui->widget_3->show();
    ui->widget_4->show();
    ui->widget_6->hide();
    ui->widget_7->hide();
    ui->widget_8->hide();
    ui->widget_1->resize(450, 85);
    ui->widget_00->resize(450, 250);
    ui->widget_10->resize(450, 45);
    resize(450, 380);
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

        if(m_capsLock){
            ui->pushButton_capsLock->setStyleSheet("background-color: rgb(0, 170, 0)");
            pushButton->setText((QChar)(i));
        } else{
            ui->pushButton_capsLock->setStyleSheet("background-color: rgb(175, 175, 175)");
            pushButton->setText((QChar)(i + 32));
        }
    }
    m_capsLock = !m_capsLock;
}

void InputPanelContext::on_pushButton_space_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertText(" ");
}

void InputPanelContext::on_pushButton_backSpace_clicked()
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
    m_text.clear();
    m_text = ui->textEdit->toPlainText();
    accept();
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

//void InputPanelContext::on_pushButton_arrow_up_clicked()
//{
//    ui->textEdit->setFocus();
//    if(ui->textEdit->document()->lineCount() > 0) {
//        QTextCursor cursor = ui->textEdit->textCursor();
//        cursor.movePosition(QTextCursor::Up);
//        ui->textEdit->setTextCursor(cursor);
//    }
//}

//void InputPanelContext::on_pushButton_arrow_down_clicked()
//{
//    ui->textEdit->setFocus();
//    if(ui->textEdit->document()->lineCount() > 0) {
//        QTextCursor cursor = ui->textEdit->textCursor();
//        cursor.movePosition(QTextCursor::Down);
//        ui->textEdit->setTextCursor(cursor);
//    }
//}

void InputPanelContext::show_cursor()
{
    ui->textEdit->setFocus();
}

QString InputPanelContext::get_text()
{
    return m_text;
}

void InputPanelContext::on_pushButton_cancel_clicked()
{
    reject();
}

void InputPanelContext::on_pushButton_symbol_clicked()
{
    if(ui->pushButton_symbol->text() == "Symbol") {
        ui->widget_2->hide();
        ui->widget_3->hide();
        ui->widget_4->hide();
        ui->widget_5->hide();
        ui->widget_6->show();
        ui->widget_7->show();
        ui->widget_8->show();
        ui->pushButton_symbol->setText("Eng");
    } else {
        ui->widget_2->show();
        ui->widget_3->show();
        ui->widget_4->show();
        ui->widget_5->show();
        ui->widget_6->hide();
        ui->widget_7->hide();
        ui->widget_8->hide();
        ui->pushButton_symbol->setText("Symbol");
    }
}

void InputPanelContext::on_pushButton_backSpace2_clicked()
{
    on_pushButton_backSpace_clicked();
}
