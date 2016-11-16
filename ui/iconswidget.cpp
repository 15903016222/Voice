#include "iconswidget.h"
#include "ui_iconswidget.h"

IconsWidget::IconsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconsWidget)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);


    connect(ui->pushButton_keyboard, SIGNAL(clicked(bool)), this, SIGNAL(keyboard_event()));
    connect(m_mcu, SIGNAL(battery_status_event(int, Mcu::BatteryStatus)), this, SLOT(do_battery_status_event(int, Mcu::BatteryStatus)));
    connect(m_mcu, SIGNAL(battery_quantity_event(int, int)), this, SLOT(do_battery_quantity_event(int, int)));
    connect(m_mcu, SIGNAL(temperature_event(Mcu::TemperatureType, int)), this, SLOT(do_temperature_event(Mcu::TemperatureType, int)));
}

IconsWidget::~IconsWidget()
{
    delete ui;
}

void IconsWidget::do_temperature_event(Mcu::TemperatureType type, int value)
{
    if (type == Mcu::TEMPERATURE_CPU) {
        QString temp_cpu;
        temp_cpu.sprintf("c:%d°C", value);
        ui->tempLabel->setText(temp_cpu);
    } /*else if (type == Mcu::TEMPERATURE_FPGA) {
        ui->label_2->setNum(value);
    } else if (type == Mcu::TEMPERATURE_MCU) {
        ui->label_3->setNum(value);
    } else if (type == Mcu::TEMPERATURE_POWER) {
        ui->label_4->setNum(value);
    }*/
}

void IconsWidget::do_battery_status_event(int index, Mcu::BatteryStatus status)
{
    if (index > 2) {
        qWarning()<<"out of battery number";
        return;
    }

    m_batteryStatus[index] = status;
    update_battery(index);
}

void IconsWidget::do_battery_quantity_event(int index, int value)
{
    if (index > 2) {
        qWarning()<<"out of battery number";
        return;
    }

    m_batteryQuantity[index] = value;
    update_battery(index);
}

void IconsWidget::update_battery(quint32 index)
{
    QString quantity;
    quantity.sprintf("%d%%", m_batteryQuantity[index]);

    QString image;

    switch (m_batteryStatus[index]) {
    case Mcu::DISCHARGE:
        image.sprintf("boarder-image:url(:/file/resources/b%d.png)", m_batteryQuantity[index]%10);
        break;
    case Mcu::CHARGE:
        image.sprintf("border-image:url(:/file/resources/bc%d.png)", m_batteryQuantity[index]%10);
        break;
    case Mcu::BATTERY_FULL:
        image.append("border-image:url(:/file/resources/b9.png)");
        break;
    default:
        image.append("border-image:url(:/file/resources/b_error.png)");
        break;
    }

    if (index == 0) {
        ui->label_battery1_quantity->setText(quantity);
        ui->label_battery1->setStyleSheet(image);
    } else if (index == 1) {
        ui->label_battery2_quantity->setText(quantity);
        ui->label_battery2->setStyleSheet(image);
    }
}
