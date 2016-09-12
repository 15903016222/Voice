#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_mcu = Mcu::get_instance();
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
    connect(ui->pushButtonPowerOff, &QPushButton::clicked, m_mcu, &Mcu::set_poweroff);
    connect(ui->pushButtonStarted, &QPushButton::clicked, m_mcu, &Mcu::notify_started);
    connect(ui->verticalSliderBrightness, &QSlider::valueChanged, m_mcu, &Mcu::set_brightness);

    connect(m_mcu, &Mcu::event, this, &MainWindow::do_mcu_event);
#else
    connect(m_mcu, SIGNAL(event(Mcu::Cmd,QByteArray&)), this, SLOT(do_mcu_event(Mcu::Cmd,QByteArray&)));
    connect(ui->verticalSliderBrightness, SIGNAL(valueChanged(int)), m_mcu, SLOT(set_brightness(int)));
    connect(ui->pushButtonPowerOff, SIGNAL(clicked(bool)), m_mcu, SLOT(set_poweroff()));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_mcu_event(Mcu::Cmd type, QByteArray &data)
{
    switch (type) {
    case Mcu::CORE_TEMPERATURE:
        ui->labelCoreTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::MCU_TEMPERATUREE:
        ui->labelMcuTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::FPGA_TEMPERATURE:
        ui->labelFpgaTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::POWER_TEMPERATURE:
        ui->labelPowerTemp->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY1_STATUS:
        ui->labelFstBatteryStatus->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY1_QUANTITY:
        ui->labelFstBattery->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY2_STATUS:
        ui->labelSndBatteryStatus->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::BATTERY2_QUANTITY:
        ui->labelSndBattery->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    case Mcu::KEY:
    case Mcu::ROTARY:
        ui->labelKey->setText(QString::number(data.toHex().toInt(0, 16)));
        break;
    default:
        break;
    }
}
