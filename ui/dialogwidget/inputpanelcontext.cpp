#include "inputpanelcontext.h"
#include "ui_inputpanelcontext.h"

#include <QPushButton>
#include <QDebug>

InputPanelContext::InputPanelContext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPanelContext)
{
    ui->setupUi(this);

    capsLock = false;

//    ui->pushButton_arrow_up->setText("<font>&uarr;</font>");
//    ui->pushButton_arrow_left->setText((QChar)27);
//    ui->pushButton_arrow_right->setText((QChar)26);
//    ui->pushButton_arrow_down->setText(QString((QChar)25));

    for(int i = 0; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

    for(int i = 65; i <= 90; i ++) {
        QString string = (QChar)i;
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
    }

    for(int i = 1; i <= 28; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("symbol_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
        qDebug()<<"init_caps";
    }

    connect(ui->pushButton_Space, SIGNAL(clicked()), this, SLOT(edit_text()));
    connect(ui->pushButton_BackSpace, SIGNAL(clicked()), this, SLOT(edit_text()));

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
    if(!capsLock){
        text = ui->textEdit->toPlainText();
        QPushButton *pushButton = qobject_cast<QPushButton*>(sender());

        if(pushButton->objectName() == "pushButton_Space") {
            ui->textEdit->setText(text + " ");
        } else if(pushButton->objectName() == "pushButton_BackSpace") {
            if(text != NULL) {
                ui->textEdit->setText(text.left(text.count() - 1));
            }
        } else{
            text = text + pushButton->text();
            ui->textEdit->setText(text);
            qDebug()<<"caps";
        }
    }
}

void InputPanelContext::edit_lowerText()
{
    if(capsLock){
        text = ui->textEdit->toPlainText();
        QPushButton *pushButton = qobject_cast<QPushButton*>(sender());

        if(pushButton->objectName() == "pushButton_Space") {
            ui->textEdit->setText(text + " ");
        } else if(pushButton->objectName() == "pushButton_BackSpace") {
            if(text != NULL) {
                ui->textEdit->setText(text.left(text.count() - 1));
            }
        } else{
            text = text + pushButton->text().toLower();
            ui->textEdit->setText(text);
            qDebug()<<"lower";
        }
    }
}

void InputPanelContext::on_pushButton_28_clicked()
{
//    if(capsLock){
//        ui->pushButton_28->setStyleSheet("background-color: rgb(0, 170, 0)");

//        for(int i = 65; i <= 90; i ++) {
//            QString string = (QChar)i;
//            QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);
//            connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
//            qDebug()<<"pushButton_28_caps";
//        }

//    } else{
//        ui->pushButton_28->setStyleSheet("background-color: rgb(175, 175, 175)");

//        for(int i = 65; i <= 90; i ++) {
//            QString string = (QChar)i;
//            QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);
//            connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_lowerText()));
//            qDebug()<<"pushButton_28_lower";
//        }
//    }
//    capsLock = !capsLock;
    for(int i = 65; i <= 90; i ++) {
        QString string = (QChar)i;
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + string);

        if(capsLock){
            ui->pushButton_28->setStyleSheet("background-color: rgb(0, 170, 0)");
            connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_text()));
        } else{
            ui->pushButton_28->setStyleSheet("background-color: rgb(175, 175, 175)");
            connect(pushButton, SIGNAL(clicked()), this, SLOT(edit_lowerText()));
        }
    }
    capsLock = !capsLock;
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
