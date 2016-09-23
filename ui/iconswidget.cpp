#include "iconswidget.h"
#include "ui_iconswidget.h"

IconsWidget::IconsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconsWidget)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);

    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
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

void IconsWidget::do_rotary_event(Mcu::RotaryType type)
{
  //  int i = ui->verticalSliderBrightness->value();
    int i = 0;
 //   m_mcu->set_brightness((char)value);
    if (type == Mcu::ROTARY_UP) {
        ++i;
    } else {
        --i;
    }
 //   ui->verticalSliderBrightness->setValue(i);
}

void IconsWidget::do_temperature_event(Mcu::TemperatureType type, int value)
{
    if (type == Mcu::TEMPERATURE_CPU) {
        QString temp_cpu;
        temp_cpu.append("c:");
        temp_cpu.append(QString::number((double)value, 'f', 1));
        temp_cpu.append("°C");
        ui->label_1->setText(temp_cpu);
      //  ui->label_1->setNum(value);
    } else if (type == Mcu::TEMPERATURE_FPGA) {
        ui->label_2->setNum(value);
    } else if (type == Mcu::TEMPERATURE_MCU) {
        ui->label_3->setNum(value);
    } else if (type == Mcu::TEMPERATURE_POWER) {
        ui->label_4->setNum(value);
    }

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
//        ui->label_battery1_quantity->setNum(value);
        QString battery1_quantity;
        battery1_quantity.append(QString::number((double)value, 'f', 0));
        battery1_quantity.append("%");
        ui->label_battery1_quantity->setText(battery1_quantity);
    } else if (index == 1) {
     //   ui->label_battery2_quantity->setNum(value);
        QString battery2_quantity;
        battery2_quantity.append(QString::number((double)value, 'f', 0));
        battery2_quantity.append("%");
        ui->label_battery2_quantity->setText(battery2_quantity);
    }
}
