#include "datetimesetdialog.h"
#include "ui_datetimesetdialog.h"

DateTimeSetDialog::DateTimeSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateTimeSetDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    ui->spinBox_1->setSingleStep(1);
    ui->spinBox_2->setSingleStep(1);
    ui->spinBox_3->setSingleStep(1);
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

    if(m_titleMap.keys().at(0) == "Date Set") {
        m_strDate.clear();
        m_strDate.append(QString::number(valueOne));
        m_strDate.append("-");
        if(valueTwo < 10){
            m_strDate.append("0" + QString::number(valueTwo));
        }else{
            m_strDate.append(QString::number(valueTwo));
        }
        m_strDate.append("-");
        if(valueThree < 10){
            m_strDate.append("0" + QString::number(valueThree));
        }else{
            m_strDate.append(QString::number(valueThree));
        }

    } else {
        m_strTime.clear();
        if(valueOne < 10){
            m_strTime.append("0" + QString::number(valueOne));
        }else{
            m_strTime.append(QString::number(valueOne));
        }
        m_strTime.append(":");
        if(valueTwo < 10){
            m_strTime.append("0" + QString::number(valueTwo));
        }else{
            m_strTime.append(QString::number(valueTwo));
        }
        m_strTime.append(":");
        if(valueThree < 10){
            m_strTime.append("0" + QString::number(valueThree));
        }else{
            m_strTime.append(QString::number(valueThree));
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

        disconnect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        disconnect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        disconnect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
    }
}

void DateTimeSetDialog::set_time_value(QString &string)
{
    QString str = ":";
    QList<int> valueList = get_value_list(string, str);
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
}

void DateTimeSetDialog::set_date_value(QString &string)
{
    QString str = "-";
    QList<int> valueList = get_value_list(string, str);
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
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
