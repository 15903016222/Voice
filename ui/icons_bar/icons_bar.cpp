#include "icons_bar.h"
#include "ui_icons_bar.h"
#include <source/scan.h>
#include <QDebug>

IconsBar::IconsBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconsBar)
{
    Mcu *mcu = Mcu::instance();
    ui->setupUi(this);

    connect(ui->keyboardPushButton, SIGNAL(clicked(bool)), this, SIGNAL(keyboard_event()));
    connect(mcu, SIGNAL(battery_status_event(int, Mcu::BatteryStatus)), this, SLOT(do_battery_status_event(int, Mcu::BatteryStatus)));
    connect(mcu, SIGNAL(battery_quantity_event(int, int)), this, SLOT(do_battery_quantity_event(int, int)));
    connect(mcu, SIGNAL(temperature_event(Mcu::TemperatureType, int)), this, SLOT(do_temperature_event(Mcu::TemperatureType, int)));
    connect(static_cast<DplSource::Axis *>(DplSource::Scan::instance()->scan_axis().data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this,
            SLOT(do_driving_changed()));
    do_driving_changed();
}

IconsBar::~IconsBar()
{
    delete ui;
}

void IconsBar::do_temperature_event(Mcu::TemperatureType type, int value)
{
    if (type == Mcu::TEMPERATURE_CPU) {
        QString temp_cpu;
        temp_cpu.sprintf("%d\260C", value);
        ui->tempLabel->setText(temp_cpu);
    } /*else if (type == Mcu::TEMPERATURE_FPGA) {
        ui->label_2->setNum(value);
    } else if (type == Mcu::TEMPERATURE_MCU) {
        ui->label_3->setNum(value);
    } else if (type == Mcu::TEMPERATURE_POWER) {
        ui->label_4->setNum(value);
    }*/
}

void IconsBar::do_battery_status_event(int index, Mcu::BatteryStatus status)
{
    if (0 == index) {
        ui->fstBatteryLabel->set_status(status);
    } else if (1 == index) {
        ui->sndBatteryLabel->set_status(status);
    }
}

void IconsBar::do_battery_quantity_event(int index, int value)
{
    if (0 == index) {
        ui->fstBatteryLabel->set_quantity(value);
    } else if (1 == index) {
        ui->sndBatteryLabel->set_quantity(value);
    }
}

void IconsBar::do_driving_changed()
{
    qDebug("%s[%d]: wh(%d, %d)",__func__, __LINE__, ui->encoderLabel->width(), ui->encoderLabel->height());
    if ( DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::TIMER ) {
        ui->encoderLabel->setPixmap(QPixmap("://resource/clock.png").scaled(ui->encoderLabel->width(), ui->encoderLabel->height()));
    } else {
        ui->encoderLabel->setPixmap(QPixmap("://resource/gear.png").scaled(ui->encoderLabel->width(), ui->encoderLabel->height()));
    }
}

void IconsBar::show_tcg(bool flag)
{
    if (flag) {
        ui->tcgLabel->setText("TCG");
    } else {
        ui->tcgLabel->clear();
    }
}

void IconsBar::show_dac(bool flag)
{
    if (flag) {
        ui->dacLabel->setText("DAC");
    } else {
        ui->dacLabel->clear();
    }
}

void IconsBar::show_sensitivity_calibration(bool flag)
{
    QPalette palette = ui->sLabel->palette();
    QBrush brush = palette.windowText();

    if (flag) {
        brush.setColor(Qt::green);
    } else {
        brush.setColor(Qt::red);
    }

    palette.setBrush(QPalette::WindowText, brush);
    ui->sLabel->setPalette(palette);
}

void IconsBar::show_velocity_calibration(bool flag)
{
    QPalette palette = ui->vLabel->palette();
    QBrush brush = palette.windowText();

    if (flag) {
        brush.setColor(Qt::green);
    } else {
        brush.setColor(Qt::red);
    }

    palette.setBrush(QPalette::WindowText, brush);
    ui->vLabel->setPalette(palette);
}

void IconsBar::show_delay_calibration(bool flag)
{
    QPalette palette = ui->wLabel->palette();
    QBrush brush = palette.windowText();

    if (flag) {
        brush.setColor(Qt::green);
    } else {
        brush.setColor(Qt::red);
    }

    palette.setBrush(QPalette::WindowText, brush);
    ui->wLabel->setPalette(palette);
}
