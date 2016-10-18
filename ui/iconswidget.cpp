#include "iconswidget.h"
#include "ui_iconswidget.h"

IconsWidget::IconsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconsWidget)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);

   // connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
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
    InputPanelContext myInputPanelDlg;
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
    int i = 50;
 //   m_mcu->set_brightness((char)i);
    if (type == Mcu::ROTARY_UP) {
        ++i;
    } else {
        --i;
    }
    m_mcu->set_brightness((char)i);
}

void IconsWidget::do_temperature_event(Mcu::TemperatureType type, int value)
{
    if (type == Mcu::TEMPERATURE_CPU) {
        QString temp_cpu;
        temp_cpu.append("c:");
        temp_cpu.append(QString::number((double)value, 'f', 0));
        temp_cpu.append("°C");
        ui->label_1->setText(temp_cpu);
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
    if (index == 0) {
        status_batteryFirst = status;
    } else if (index == 1) {
        status_batterySecond = status;
    }
}

void IconsWidget::insert_battery1_icon(int value)
{
  //0:Discharge; 1:Charge; 2:No Battery; 3:Full;
    if(status_batteryFirst == 0){
    //    qDebug()<<"discharge_battery_1:  "<<value;
        if(value >= 0 && value < 10){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b0.png);");
        }else if(value >= 10 && value < 20){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b1.png);");
        }else if(value >= 20 && value < 30){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b2.png);");
        }else if(value >= 30 && value < 40){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b3.png);");
        }else if(value >= 40 && value < 50){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b4.png);");
        }else if(value >= 50 && value < 60){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b5.png);");
        }else if(value >= 60 && value < 70){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b6.png);");
        }else if(value >= 70 && value < 80){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b7.png);");
        }else if(value >= 80 && value < 90){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b8.png);");
        }else if(value >= 90 && value <= 100){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b9.png);");
        }
    }else if(status_batteryFirst == 1){
    //    qDebug()<<"charge_battery_1:     "<<value;
        if(value >= 0 && value < 10){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc0.png);");
        }else if(value >= 10 && value < 20){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc1.png);");
        }else if(value >= 20 && value < 30){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc2.png);");
        }else if(value >= 30 && value < 40){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc3.png);");
        }else if(value >= 40 && value < 50){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc4.png);");
        }else if(value >= 50 && value < 60){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc5.png);");
        }else if(value >= 60 && value < 70){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc6.png);");
        }else if(value >= 70 && value < 80){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc7.png);");
        }else if(value >= 80 && value < 90){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc8.png);");
        }else if(value >= 90 && value < 100){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc9.png);");
        }else if(value == 100){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/bc_full.png);");
        }
    }else if(status_batteryFirst == 2){
    //    qDebug()<<"No_Battery_battery_1: "<<value;
        ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b_error.png);");
    }else if(status_batteryFirst == 3){
    //    qDebug()<<"full_battery_1:       "<<value;
        ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b9.png);");
    }
}

void IconsWidget::insert_battery2_icon(int value)
{
  //0:Discharge; 1:Charge; 2:No Battery; 3:Full;
    if(status_batterySecond == 0){
     //   qDebug()<<"discharge_battery_2:  "<<value;
        if(value >= 0 && value < 10){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b0.png);");
        }else if(value >= 10 && value < 20){
            ui->label_battery1->setStyleSheet("border-image:url(:/file/resources/b1.png);");
        }else if(value >= 20 && value < 30){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b2.png);");
        }else if(value >= 30 && value < 40){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b3.png);");
        }else if(value >= 40 && value < 50){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b4.png);");
        }else if(value >= 50 && value < 60){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b5.png);");
        }else if(value >= 60 && value < 70){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b6.png);");
        }else if(value >= 70 && value < 80){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b7.png);");
        }else if(value >= 80 && value < 90){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b8.png);");
        }else if(value >= 90 && value < 100){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b9.png);");
        }
    }else if(status_batterySecond == 1){
     //   qDebug()<<"charge_battery_2:     "<<value;
        if(value >= 0 && value < 10){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc0.png);");
        }else if(value >= 10 && value < 20){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc1.png);");
        }else if(value >= 20 && value < 30){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc2.png);");
        }else if(value >= 30 && value < 40){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc3.png);");
        }else if(value >= 40 && value < 50){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc4.png);");
        }else if(value >= 50 && value < 60){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc5.png);");
        }else if(value >= 60 && value < 70){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc6.png);");
        }else if(value >= 70 && value < 80){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc7.png);");
        }else if(value >= 80 && value < 90){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc8.png);");
        }else if(value >= 90 && value < 100){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc9.png);");
        }else if(value == 100){
            ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/bc_full.png);");
        }
    }else if(status_batterySecond == 2){
     //   qDebug()<<"No_Battery_battery_2: "<<value;
        ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b_error.png);");
    }else if(status_batterySecond == 3){
     //   qDebug()<<"full_battery_2:       "<<value;
        ui->label_battery2->setStyleSheet("border-image:url(:/file/resources/b9.png);");
    }
}

void IconsWidget::do_battery_quantity_event(int index, int value)
{
    if (index == 0) {
        QString battery1_quantity;
        battery1_quantity.append(QString::number((double)value, 'f', 0));
        battery1_quantity.append("%");
        ui->label_battery1_quantity->setText(battery1_quantity);

     //   qDebug()<<"status_battery_1        =         "<<status_batteryFirst;
        insert_battery1_icon(value);
    } else if (index == 1) {
        QString battery2_quantity;
        battery2_quantity.append(QString::number((double)value, 'f', 0));
        battery2_quantity.append("%");
        ui->label_battery2_quantity->setText(battery2_quantity);

    //    qDebug()<<"status_battery_2             =             "<<status_batterySecond;
        insert_battery2_icon(value);
    }
}
