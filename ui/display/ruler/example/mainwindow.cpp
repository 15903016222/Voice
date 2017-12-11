#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_topRuler(new Ruler(Ruler::BOTTOM, "mm", this)),
    m_leftRuler(new Ruler(Ruler::RIGHT, "mm", this)),
    m_rightRuler(new Ruler(Ruler::LEFT, "mm", this)),
    m_bottomRuler(new Ruler(Ruler::TOP, "mm", this))
{
    m_rightRuler->setMaximumWidth(30);
    m_leftRuler->setMaximumWidth(30);

    ui->setupUi(this);
    ui->topHorizontalLayout->addWidget(m_topRuler);
    ui->leftVerticalLayout->addWidget(m_leftRuler);
    ui->rightVerticalLayout->addWidget(m_rightRuler);
    ui->bottomHorizontalLayout->addWidget(m_bottomRuler);

//    m_topRuler->hide();
//    m_leftRuler->hide();
//    m_rightRuler->hide();

    m_topRuler->set_range(ui->startDoubleSpinBox->value(),
                       ui->endDoubleSpinBox->value());
    m_leftRuler->set_range(ui->startDoubleSpinBox->value(),
                       ui->endDoubleSpinBox->value());
    m_rightRuler->set_range(ui->startDoubleSpinBox->value(),
                       ui->endDoubleSpinBox->value());
    m_bottomRuler->set_range(ui->startDoubleSpinBox->value(),
                       ui->endDoubleSpinBox->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startDoubleSpinBox_valueChanged(double arg1)
{
    m_topRuler->set_range(arg1, arg1+100);
    m_leftRuler->set_range(arg1, arg1+100);
    m_rightRuler->set_range(arg1, arg1+100);
    m_bottomRuler->set_range(arg1, arg1+100);
}

void MainWindow::on_endDoubleSpinBox_valueChanged(double arg1)
{
    m_topRuler->set_range(arg1, arg1-100);
    m_leftRuler->set_range(arg1, arg1-100);
    m_rightRuler->set_range(arg1, arg1-100);
    m_bottomRuler->set_range(arg1, arg1-100);
}
