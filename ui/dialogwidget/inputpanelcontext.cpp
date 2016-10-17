#include "inputpanelcontext.h"
#include "ui_inputpanelcontext.h"

#include <QPushButton>
#include <QDebug>

InputPanelContext::InputPanelContext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPanelContext)
{
    ui->setupUi(this);

    capsLock = true;
    on_pushButton_capsLock_clicked();

//    ui->pushButton_arrow_up->setText("<font>&uarr;</font>");
//    ui->pushButton_arrow_left->setText((QChar)27);
//    ui->pushButton_arrow_right->setText((QChar)26);
//    ui->pushButton_arrow_down->setText(QString((QChar)25));

    for(int i = 0; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

//    for(int i = 65; i <= 90; i ++) {
//        QString string = (QChar)i;
//        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);
//        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
//    }

    for(int i = 1; i <= 28; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("symbol_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

    for(int i = 0; i < 3; i ++ ) {
        QFrame *frame = findChild<QFrame*>("frame_" + QString::number(i));
        frame->setStyleSheet("QWidget QPushButton{font: bold 12pt 'Times New Roman';}");
    }
}

InputPanelContext::~InputPanelContext()
{
    delete ui;
}

void InputPanelContext::edit_text()
{
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    QString text = ui->textEdit->toPlainText() + pushButton->text();
    ui->textEdit->setText(text);
}

void InputPanelContext::edit_lowerText()
{
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    QString text = ui->textEdit->toPlainText();
    ui->textEdit->setText(text + pushButton->text().toLower());
}

void InputPanelContext::on_pushButton_capsLock_clicked()
{
    for(int i = 65; i <= 90; i ++) {
        QString string = (QChar)i;
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);

        if(capsLock){
            ui->pushButton_capsLock->setStyleSheet("background-color: rgb(0, 170, 0)");
            connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
        } else{
            ui->pushButton_capsLock->setStyleSheet("background-color: rgb(175, 175, 175)");
            connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_lowerText()));
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
        ui->textEdit->setText(text.left(text.count() - 1));
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
}
