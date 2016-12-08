#include "datetimesetdialog.h"
#include "ui_datetimesetdialog.h"

DateTimeSetDialog::DateTimeSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateTimeSetDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

DateTimeSetDialog::~DateTimeSetDialog()
{
    delete ui;
}

void DateTimeSetDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void DateTimeSetDialog::on_buttonBox_accepted()
{    
    int valueOne = ui->spinBox_1->value();
    int valueTwo = ui->spinBox_2->value();
    int valueThree = ui->spinBox_3->value();

    if(titleMap.keys().at(0) == "Date Set") {
        m_strDate.clear();
        m_strDate.append(QString::number((double)valueOne, 'f', 0));
        m_strDate.append("-");
        if(valueTwo < 10){
            m_strDate.append("0" + QString::number((double)valueTwo, 'f', 0));
        }else{
            m_strDate.append(QString::number((double)valueTwo, 'f', 0));
        }
        m_strDate.append("-");
        if(valueThree < 10){
            m_strDate.append("0" + QString::number((double)valueThree, 'f', 0));
        }else{
            m_strDate.append(QString::number((double)valueThree, 'f', 0));
        }

    } else {
        m_strTime.clear();
        if(valueOne < 10){
            m_strTime.append("0" + QString::number((double)valueOne, 'f', 0));
        }else{
            m_strTime.append(QString::number((double)valueOne, 'f', 0));
        }
        m_strTime.append(":");
        if(valueTwo < 10){
            m_strTime.append("0" + QString::number((double)valueTwo, 'f', 0));
        }else{
            m_strTime.append(QString::number((double)valueTwo, 'f', 0));
        }
        m_strTime.append(":");
        if(valueThree < 10){
            m_strTime.append("0" + QString::number((double)valueThree, 'f', 0));
        }else{
            m_strTime.append(QString::number((double)valueThree, 'f', 0));
        }
    }
}

void DateTimeSetDialog::check_date_valid(int number)
{
    Q_UNUSED(number);
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

void DateTimeSetDialog::set_dialog_title(QMap<QString, QString> map)
{
    ui->label->setText(map.values().at(0));
    titleMap = map;
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

        disconnect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        disconnect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        disconnect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
    }
}

void DateTimeSetDialog::set_spinbox_value(QList<int> valueList)
{
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
}
