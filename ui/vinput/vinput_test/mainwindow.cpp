#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../vinput.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_APushButton_clicked()
{
//    VInput::get_vinput()->send(VInput::Key_A);
}

void MainWindow::on_ZPushButton_clicked()
{
//    VInput::get_vinput()->send(VInput::Key_Z);
}


void MainWindow::on_onePushButton_clicked()
{
    VInput::get_vinput()->send(VInput::Key_1);
}

void MainWindow::on_twoPushButton_clicked()
{
    VInput::get_vinput()->send(VInput::Key_9);
}

void MainWindow::on_capsPushButton_clicked()
{
//    VInput::get_vinput()->send(VInput::Key_Capslock);
}

void MainWindow::on_leftShiftPushButton_clicked()
{
//    VInput::get_vinput()->send(VInput::Key_LeftShift);
}
