#include "measurementdialog.h"
#include "ui_measurementdialog.h"
#include "topmenu.h"

#include <QDebug>
#include <QStandardItemModel>

MeasurementDialog::MeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasurementDialog)
{
  ui->setupUi(this);

  initUI();

  changedFlag = false;
}

MeasurementDialog::~MeasurementDialog()
{
  delete ui;
}

void MeasurementDialog::initUI()
{
  buttonList.append(ui->pushButton_cancel);
  buttonList.append(ui->pushButton_ok);

  for(int i = 0; i < MEASUREMENT_NUMBER; i++)
  {
    QString  str = MEASUREMENT_STRING[i];
    if(str.contains(" ") == true)
    {
      int index = str.indexOf(" ");
      QString text = str.left(index);
      if(str.contains("%") || MEASUREMENT_STRING[i].contains("Percentage"))
      {
        text = text + "\n(%)";
      }
      else if(str.contains("dB"))
      {
        text = text + "\n(dB)";
      }
      else
      {
        text = text + "\n(mm)";
      }
      labelMap.insert(text, MEASUREMENT_STRING[i]);
    }
  }
//  for(QMap<QString, QString>::const_iterator p = labelMap.constBegin(); p != labelMap.constEnd(); ++ p)
//  {
//    qDebug()<<p.key()<<":"<<p.value();
//  }

  listView = new QListView(this);
  listView->resize(ui->scrollArea->geometry().width(), 800);
  listView->setSpacing(3);
  ui->scrollArea->setFrameShape(QFrame::NoFrame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidget(listView);

  measurementModel = new QStandardItemModel(this);

  for(int i = 0; i < MEASUREMENT_NUMBER; i++)
  {
    measurementList.append(MEASUREMENT_STRING[i]);
    QString string = static_cast<QString>(measurementList.at(i));
    QStandardItem *item = new QStandardItem(string);
    measurementModel->appendRow(item);
    item->setForeground(QBrush(Qt::black));
    item->setFont(QFont("Times New Roman", 12));
  }
  listView->setModel(measurementModel);
  connect(listView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_listViewItemClicked(QModelIndex)));
}

void MeasurementDialog::on_pushButton_cancel_clicked()
{
  close();
}

void MeasurementDialog::on_pushButton_ok_clicked()
{
  if(changedFlag)
  {
    close();
    emit labelTextChanged(changedString);
  }
}

void MeasurementDialog::slot_listViewItemClicked(QModelIndex index)
{
  changedFlag = true;
  QStandardItem *item = measurementModel->itemFromIndex(index);
  changedString = labelMap.key(item->text());

}
