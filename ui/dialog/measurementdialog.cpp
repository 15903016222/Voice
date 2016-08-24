#include "measurementdialog.h"
#include "ui_measurementdialog.h"

#include <QDebug>

MeasurementDialog::MeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasurementDialog)
{
  ui->setupUi(this);

  initUI();
}

MeasurementDialog::~MeasurementDialog()
{
  delete ui;
}

void MeasurementDialog::initUI()
{
  buttonList.append(ui->pushButton_cancel);
  buttonList.append(ui->pushButton_ok);
  listView = new QListView(this);
  listView->resize(ui->scrollArea->geometry().width(), 800);
  ui->scrollArea->setFrameShape(QFrame::NoFrame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidget(listView);
//  qDebug()<<this->geometry();
//  qDebug()<<this->ui->widget_2->geometry();
//  qDebug()<<listView->size();
//  qDebug()<<this->ui->scrollArea->size();
}

void MeasurementDialog::on_pushButton_cancel_clicked()
{
  close();
}

void MeasurementDialog::on_pushButton_ok_clicked()
{
  close();
  //判断是否有点击listView，若有，返回所点击内容对应的文字，更改label的文字及相应测量值
}
