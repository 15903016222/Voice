#include "iconswidget.h"
#include "ui_iconswidget.h"

IconsWidget::IconsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconsWidget)
{
    ui->setupUi(this);

    connect(m_mcu, SIGNAL(battery_status_event(int, Mcu::BatteryStatus)), this, SLOT(do_battery_status_event(int, Mcu::BatteryStatus)));
    connect(m_mcu, SIGNAL(battery_quantity_event(int, int)), this, SLOT(do_battery_quantity_event(int, int)));
    connect(m_mcu, SIGNAL(temperature_event(Mcu::TemperatureType, int)), this, SLOT(do_temperature_event(Mcu::TemperatureType, int)));
}

IconsWidget::~IconsWidget()
{
    delete ui;
}

void IconsWidget::on_pushButton_keyboard_clicked()
{
    MyInputPanel myInputPanelDlg;
    myInputPanelDlg.setWindowFlags(Qt::FramelessWindowHint);
    myInputPanelDlg.setModal(true);
    myInputPanelDlg.showNormal();
    myInputPanelDlg.exec();
}

void IconsWidget::on_pushButton_scan_clicked()
{
    static bool scan = false;
    if(scan)
    {
        ui->pushButton_scan->setStyleSheet("QPushButton{border-image: url(:/file/resources/set.png)}");

    }else{
        ui->pushButton_scan->setStyleSheet("QPushButton{border-image: url(:/file/resources/clock.png)}");
    }
    scan = !scan;
}

void IconsWidget::do_temperature_event(Mcu::TemperatureType type, int value)
{
    if (type == Mcu::TEMPERATURE_CPU) {
        ui->label_temperature->setNum(value);
    } /*else if (type == Mcu::TEMPERATURE_FPGA) {
        ui->labelFpgaTemp->setNum(value);
    } else if (type == Mcu::TEMPERATURE_MCU) {
        ui->labelMcuTemp->setNum(value);
    } else if (type == Mcu::TEMPERATURE_POWER) {
        ui->labelPowerTemp->setNum(value);
    }*/

}

void IconsWidget::do_battery_status_event(int index, Mcu::BatteryStatus status)
{
    static QString statusList[4] = {"Discharge", "Charge", "No Battery", "Full"};
    if (index == 0) {
        ui->label_battery1->setText(statusList[status]);
    } else if (index == 1) {
        ui->label_battery2->setText(statusList[status]);
    }
}

void IconsWidget::do_battery_quantity_event(int index, int value)
{
    if (index == 0) {
        ui->label_battery1->setNum(value);
    } else if (index == 1) {
        ui->label_battery2->setNum(value);
    }
}
