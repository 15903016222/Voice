#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../line.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *w1 = new QWidget();
    w1->setObjectName("w1");

    QWidget *w2 = new QWidget();
    w2->setObjectName("w2");

    Line *l = new Line();
    l->setObjectName("line1");

    setStyleSheet("Line { background-color:rgb(191, 234, 191); }\n #w1,#w2 { background-color: rgb(33, 44, 55);}");

    ui->horizontalLayout->addWidget(w1, 1);

    ui->horizontalLayout->addWidget(l, 1);

    ui->horizontalLayout->addWidget(w2, 1);


}

MainWindow::~MainWindow()
{
    delete ui;
}
