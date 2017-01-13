#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../probe.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DplProbe::Probe probe;
    probe.load("/opt/mercury/probe/pa/test.opp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Probe File", "/opt/mercury/probe", tr("Probe (*.opp *.oup)"));

    ui->lineEdit->setText(fileName);
    DplProbe::Probe probe;

    probe.load(fileName);

    ui->textBrowser->setText(probe.show());
}
