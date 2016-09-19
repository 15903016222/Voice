#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    connect(ui->pushButtonCoreTemp, &QPushButton::clicked, m_mcu, &Mcu::query_core_temp);
    connect(ui->pushButtonFpgaTemp, &QPushButton::clicked, m_mcu, &Mcu::query_fpga_temp);
    connect(ui->pushButtonPowerTemp, &QPushButton::clicked, m_mcu, &Mcu::query_power_temp);
    connect(ui->pushButtonMcuTemp, &QPushButton::clicked, m_mcu, &Mcu::query_mcu_temp);
    connect(ui->pushButtonFstBattery, &QPushButton::clicked, m_mcu, &Mcu::query_first_battery);
    connect(ui->pushButtonFstBatteryStatus, &QPushButton::clicked, m_mcu, &Mcu::query_first_battery_status);
    connect(ui->pushButtonSndBattery, &QPushButton::clicked, m_mcu, &Mcu::query_second_battery);
    connect(ui->pushButtonSndBatteryStatus, &QPushButton::clicked, m_mcu, &Mcu::query_second_battery_status);
    connect(ui->pushButtonStarted, &QPushButton::clicked, m_mcu, &Mcu::notify_started);
#endif

    connect(m_mcu, SIGNAL(key_event(int)), ui->labelKey, SLOT(setNum(int)));

    connect(ui->pushButtonPowerOff, SIGNAL(clicked(bool)), m_mcu, SLOT(set_poweroff()));

    connect(ui->verticalSliderBrightness, SIGNAL(valueChanged(int)), this, SLOT(do_verticalSliderBrightness_value_changed(int)));
    connect(m_mcu, SIGNAL(battery_status_event(int,Mcu::BatteryStatus)), this, SLOT(do_battery_status_event(int,Mcu::BatteryStatus)));
    connect(m_mcu, SIGNAL(battery_quantity_event(int,int)), this, SLOT(do_battery_quantity_event(int,int)));
    connect(m_mcu, SIGNAL(temperature_event(Mcu::TemperatureType,int)), this, SLOT(do_temperature_event(Mcu::TemperatureType,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_verticalSliderBrightness_value_changed(int value)
{
    m_mcu->set_brightness((char)value);
}

void MainWindow::do_battery_status_event(int index, Mcu::BatteryStatus status)
{
    static QString statusList[4] = {"Discharge", "Charge", "No Battery", "Full"};
    if (index == 0) {
        ui->labelFstBatteryStatus->setText(statusList[status]);
    } else if (index == 1) {
        ui->labelSndBatteryStatus->setText(statusList[status]);
    }
}

void MainWindow::do_battery_quantity_event(int index, int value)
{
    if (index == 0) {
        ui->labelFstBattery->setNum(value);
    } else if (index == 1) {
        ui->labelSndBattery->setNum(value);
    }
}

void MainWindow::do_temperature_event(Mcu::TemperatureType type, int value)
{
    if (type == Mcu::TEMPERATURE_CPU) {
        ui->labelCoreTemp->setNum(value);
    } else if (type == Mcu::TEMPERATURE_FPGA) {
        ui->labelFpgaTemp->setNum(value);
    } else if (type == Mcu::TEMPERATURE_MCU) {
        ui->labelMcuTemp->setNum(value);
    } else if (type == Mcu::TEMPERATURE_POWER) {
        ui->labelPowerTemp->setNum(value);
    }
}
