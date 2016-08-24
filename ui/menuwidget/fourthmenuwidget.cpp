#include "fourthmenuwidget.h"
#include "ui_fourthmenuwidget.h"

#include "doublespinboxdelegate.h"


FourthMenuWidget::FourthMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourthMenuWidget)
{
  ui->setupUi(this);

  initGain_angle();
  initStandardModel();
}

FourthMenuWidget::~FourthMenuWidget()
{
  delete ui;
}

void FourthMenuWidget::initGain_angle()
{
  ui->tableView_gain->verticalHeader()->setResizeMode(QHeaderView::Stretch);
  ui->tableView_gain->verticalHeader()->hide();
  ui->tableView_gain->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  ui->tableView_gain->horizontalHeader()->hide();

  QStandardItemModel *model_gain = new QStandardItemModel(1, 2, this);
  ui->tableView_gain->setModel(model_gain);

  DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
  QStandardItem *item_gain1 = new QStandardItem(QString::number(100, 'f', 1));
  QStandardItem *item_gain2 = new QStandardItem("(" + QString::number(10, 'f', 2) + ")");
  model_gain->setItem(0, 0, item_gain1);
  model_gain->setItem(0, 1, item_gain2);
  model_gain->item(0)->setTextAlignment(Qt::AlignCenter);
  model_gain->item(0, 0)->setForeground(Qt::white);
  model_gain->item(0, 1)->setForeground(Qt::yellow);
  model_gain->item(0, 0)->setFont(QFont("Times New Roman", 11));
  model_gain->item(0, 1)->setFont(QFont("Times New Roman", 9));
  ui->tableView_gain->setItemDelegate(doubleSpinBox);
  ui->tableView_gain->show();


  ui->tableView_angle->verticalHeader()->setResizeMode(QHeaderView::Stretch);
  ui->tableView_angle->verticalHeader()->hide();
  ui->tableView_angle->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  ui->tableView_angle->horizontalHeader()->hide();

  QStandardItemModel *model_angle = new QStandardItemModel(1, 1, this);
  ui->tableView_angle->setModel(model_angle);

  DoubleSpinBoxDelegate *doubleSpinBox_angle = new DoubleSpinBoxDelegate(this);
  QStandardItem *item_angle = new QStandardItem(QString::number(70, 'f', 1));
  model_angle->setItem(0, item_angle);
  model_angle->item(0)->setTextAlignment(Qt::AlignCenter);
  model_angle->item(0)->setForeground(Qt::white);
  model_angle->item(0)->setFont(QFont("Times New Roman", 11));
  ui->tableView_angle->setItemDelegate(doubleSpinBox_angle);
  ui->tableView_angle->show();

}

void FourthMenuWidget::initStandardModel()
{
  model = new QStandardItemModel(1, 8, this);
  ui->tableView->setModel(model);
  ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
  ui->tableView->verticalHeader()->hide();
  ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

  ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                   "{font: 11pt 'Times New Roman'; background-color:rgb(71, 122, 166);"
                                                   "color:rgb(255, 255, 0); z}");
  for(int k = 0; k < 8; k++)
  {
    QModelIndex index = model->index(k, 0, QModelIndex());
    model->setData(index, k);

    model->setHeaderData(k, Qt::Horizontal, FOURTH_MENU_STRING[k]);

    DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
    model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QStandardItem *item = new QStandardItem(QString::number(100, 'f', 2));
    model->setItem(0, k, item);
    model->item(0, k)->setTextAlignment(Qt::AlignCenter);
    model->item(0, k)->setForeground(Qt::white);
    model->item(0, k)->setBackground(QBrush(Qt::black));
    model->item(0, k)->setFont(QFont("Times New Roman", 11));
    ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
  }

  ui->tableView->show();
}

void FourthMenuWidget::FourthMenuWidgetRetranslateUi()
{
  ui->retranslateUi(this);
}
