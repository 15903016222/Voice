#include "datetimesetdialog.h"
#include "ui_datetimesetdialog.h"

#include <QKeyEvent>
#include <QDebug>

DateTimeSetDialog::DateTimeSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateTimeSetDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    ui->spinBox_1->setSingleStep(1);
    ui->spinBox_2->setSingleStep(1);
    ui->spinBox_3->setSingleStep(1);

    connect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(set_prefix(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(set_prefix(int)));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(set_prefix(int)));
}

DateTimeSetDialog::~DateTimeSetDialog()
{
    delete ui;
}

void DateTimeSetDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void DateTimeSetDialog::set_datetime_string(QString &str)
{
    str.clear();
    str.append(ui->spinBox_1->prefix() + QString::number(ui->spinBox_1->value()));
    str.append(ui->label_2->text());
    str.append(ui->spinBox_2->prefix() + QString::number(ui->spinBox_2->value()));
    str.append(ui->label_3->text());
    str.append(ui->spinBox_3->prefix() + QString::number(ui->spinBox_3->value()));
}

void DateTimeSetDialog::check_date_valid(int number)
{
    Q_UNUSED(number);
    qDebug() << "number";
    qDebug() << ui->spinBox_1->value() << ui->spinBox_2->value() << ui->spinBox_3->value();
    QDate date = QDate(ui->spinBox_1->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
    if(date.isValid()) {
        return;
    } else {
        int days = QDate(ui->spinBox_1->value(), ui->spinBox_2->value(),1).daysInMonth();
        if(ui->spinBox_3->value() > days) {
            ui->spinBox_3->setValue(days);
        }
    }
}

void DateTimeSetDialog::set_dialog_title(QMap<QString, QString> &map)
{
    ui->label->setText(map.values().at(0));
    m_titleMap = map;
    if(map.keys().at(0) == "Date Set") {
        ui->spinBox_1->setMinimum(1970);
        ui->spinBox_2->setMinimum(1);
        ui->spinBox_3->setMinimum(1);

        ui->spinBox_1->setMaximum(5000);
        ui->spinBox_2->setMaximum(12);
        ui->spinBox_3->setMaximum(31);

        connect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
    } else {
        ui->spinBox_1->setMinimum(0);
        ui->spinBox_2->setMinimum(0);
        ui->spinBox_3->setMinimum(0);

        ui->spinBox_1->setMaximum(23);
        ui->spinBox_2->setMaximum(59);
        ui->spinBox_3->setMaximum(59);
    }
}

void DateTimeSetDialog::set_time_value(QString &string)
{
    QString str = ":";
    QList<int> valueList = get_value_list(string, str);
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
    ui->label_2->setText(str);
    ui->label_3->setText(str);
}

void DateTimeSetDialog::set_date_value(QString &string)
{
    QString str = "-";
    QList<int> valueList = get_value_list(string, str);
    qDebug() << valueList;
    ui->spinBox_1->setValue(valueList.at(0));
    qDebug() << valueList.at(0);
    qDebug() << ui->spinBox_1->value();
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
    ui->label_2->setText(str);
    ui->label_3->setText(str);
}

QString DateTimeSetDialog::get_date()
{
    return m_strDate;
}

QString DateTimeSetDialog::get_time()
{
    return m_strTime;
}

QList<int> DateTimeSetDialog::get_value_list(QString &text, QString &str)
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

void DateTimeSetDialog::set_prefix(int value)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(value >= 10) {
        spinBox->setPrefix("");
    } else {
        spinBox->setPrefix("0");
    }
}

void DateTimeSetDialog::on_pushButton_ok_clicked()
{
    if(m_titleMap.keys().at(0) == "Date Set") {
        set_datetime_string(m_strDate);
    } else {
        set_datetime_string(m_strTime);
    }
    accept();
}

void DateTimeSetDialog::on_pushButton_cancel_clicked()
{
    reject();
}

void DateTimeSetDialog::keyPressEvent(QKeyEvent *e)
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
