#include "networkdialog.h"
#include "ui_networkdialog.h"

#include <QKeyEvent>

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void NetworkDialog::set_dialog_title(QString &string)
{
    ui->label->setText(string);
}

void NetworkDialog::set_spinbox_value(QString &string)
{
    QString str = ".";
    QList<int> valueList = get_value_list(string, str);
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
    ui->spinBox_4->setValue(valueList.at(3));
}

QString NetworkDialog::get_text()
{
    return m_str;
}

QList<int> NetworkDialog::get_value_list(QString &text, QString &str)
{
    QList<int> valueList;
    QString tmpString = text;
    int tmpIndex = 0;
    for(int i = 0; i < text.length() - 1; i ++) {
        if(QString(text.at(i)) == str) {
            valueList.append(tmpString.left(i - tmpIndex).toInt());
            tmpString = tmpString.right(text.count() - i - 1);
            tmpIndex = i + 1;
        }
    }
    valueList.append(tmpString.toInt());
    return valueList;
}

void NetworkDialog::on_pushButton_ok_clicked()
{
    m_str.clear();
    m_str.append(QString::number(ui->spinBox_1->value()));
    m_str.append(".");
    m_str.append(QString::number(ui->spinBox_2->value()));
    m_str.append(".");
    m_str.append(QString::number(ui->spinBox_3->value()));
    m_str.append(".");
    m_str.append(QString::number(ui->spinBox_4->value()));
    accept();
}

void NetworkDialog::on_pushButton_cancel_clicked()
{
    reject();
}

void NetworkDialog::keyPressEvent(QKeyEvent *e)
{
    switch ((int)e->key()) {
    case Qt::Key_Escape:
        reject();
        break;
    case Qt::Key_Return:
        on_pushButton_ok_clicked();
        break;
    default:
        break;
    }
}
