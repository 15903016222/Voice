#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);
    this->resize(800, 560);

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    connect(ui->pushButtonCoreTemp, &QPushButton::clicked, m_mcu, &Mcu::query_core_temp);
    connect(ui->pushButtonFpgaTemp, &QPushButton::clicked, m_mcu, &Mcu::query_fpga_temp);
    connect(ui->pushButtonPowerTemp, &QPushButton::clicked, m_mcu, &Mcu::query_power_temp);
    connect(ui->pushButtonMcuTemp, &QPushButton::clicked, m_mcu, &Mcu::query_mcu_temp);
    connect(ui->pushButtonFstBattery, &QPushButton::clicked, m_mcu, &Mcu::query_first_battery);
    connect(ui->pushButtonFstBatteryStatus, &QPushButton::clicked, m_mcu, &Mcu::query_first_battery_status);
    connect(ui->pushButtonSndBattery, &QPushButton::clicked, m_mcu, &Mcu::query_second_battery);
    connect(ui->pushButtonSndBatteryStatus, &QPushButton::clicked, m_mcu, &Mcu::query_second_battery_status);
#endif

    connect(m_mcu, SIGNAL(key_event(int)), ui->labelKey, SLOT(setNum(int)));
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));

    connect(ui->pushButtonPowerOff, SIGNAL(clicked(bool)), m_mcu, SLOT(set_poweroff()));

    connect(ui->verticalSliderBrightness, SIGNAL(valueChanged(int)), this, SLOT(do_verticalSliderBrightness_value_changed(int)));
    connect(m_mcu, SIGNAL(battery_status_event(int,Mcu::BatteryStatus)), this, SLOT(do_battery_status_event(int,Mcu::BatteryStatus)));
    connect(m_mcu, SIGNAL(battery_quantity_event(int,int)), this, SLOT(do_battery_quantity_event(int,int)));
    connect(m_mcu, SIGNAL(temperature_event(Mcu::TemperatureType,int)), this, SLOT(do_temperature_event(Mcu::TemperatureType,int)));
    connect(m_mcu, SIGNAL(probe_event(const Probe&)), this, SLOT(do_probe_event(const Probe&)));


    ui->verticalSliderBrightness->setValue(90);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_verticalSliderBrightness_value_changed(int value)
{
    m_mcu->set_brightness((char)value);
}

void MainWindow::do_rotary_event(Mcu::RotaryType type)
{
    int i = ui->verticalSliderBrightness->value();
    if (type == Mcu::ROTARY_UP) {
        ++i;
    } else {
        --i;
    }
    ui->verticalSliderBrightness->setValue(i);
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

void MainWindow::do_probe_event(const Probe &probe)
{
//    ui->labelProbeType->setNum(probe.type());
    switch(probe.type()){
        case 0:ui->labelProbeType->setText("UNKNOWN"); break;
        case 1:ui->labelProbeType->setText("CUSTOM"); break;
        case 3:ui->labelProbeType->setText("ANGLE_BEAM"); break;
        case 5:ui->labelProbeType->setText("CONTACT"); break;
        case 6:ui->labelProbeType->setText("IMMERSION"); break;
        default:  break;
    }
    ui->labelProbeModel->setText(probe.model());
    ui->labelProbeSerial->setText(probe.serial());
//    ui->labelProbePitch->setNum(probe.pitch());
    QString pitch;
    pitch.append(QString::number((double)probe.pitch()/1000, 'f', 3));
    pitch.append(" mm");
    ui->labelProbePitch->setText(pitch);
//    ui->labelProbeFreq->setNum(probe.freq());
    QString freq;
    freq.append(QString::number((double)probe.freq()/1000, 'f', 2));
    freq.append(" MHz");
    ui->labelProbeFreq->setText(freq);
    ui->labelProbePoint->setNum(probe.reference_point());
    ui->labelProbeElemQty->setNum(probe.elements_quantity());
}

void MainWindow::on_pushButtonStarted_clicked()
{
     m_mcu->notify_started();
     m_mcu->query_probe();
}
