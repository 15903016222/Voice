#include "inputpanelcontext.h"
#include "ui_inputpanelcontext.h"

#include <QPushButton>
#include <QDebug>

InputPanelContext::InputPanelContext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPanelContext)
{
    ui->setupUi(this);
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
    QString text = ui->textEdit->toPlainText();
    QPushButton *pushButton = qobject_cast<QPushButton*>(sender());
    if(pushButton->objectName() == "pushButton_Space") {
        ui->textEdit->setText(text + " ");
    } else if(pushButton->objectName() == "pushButton_BackSpace") {
        if(text != NULL) {
            QString newText = text.left(text.count() - 1);
            ui->textEdit->setText(newText);
        }
    } else {
        ui->textEdit->setText(text + pushButton->text());
    }
}

void InputPanelContext::on_pushButton_cancel_clicked()
{
    close();
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
