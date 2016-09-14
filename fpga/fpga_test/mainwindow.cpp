#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../gpio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Gpio *gpio = Gpio::get_instance();
    gpio->set(Gpio::PIN_61, Gpio::LOW);
}

MainWindow::~MainWindow()
{
    delete ui;
}
