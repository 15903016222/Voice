#include "commonmenuwidget.h"
#include "ui_commonmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"

#include <QResizeEvent>

CommonMenuWidget::CommonMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CommonMenuWidget)
{
  ui->setupUi(this);
  this->resize(800, 72);

  initStandardModel();
}

CommonMenuWidget::~CommonMenuWidget()
{
  delete ui;
}

void CommonMenuWidget::initStandardModel()
{
  model = new QStandardItemModel(1, COMMON_MENU_NUMBER, this);
  ui->tableView->setModel(model);
//  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
  ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
  ui->tableView->verticalHeader()->hide();
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                   "{font: 11pt 'Times New Roman'; background-color: rgba(71, 122, 166, 0.4);;"
                                                   "color:rgba(255, 255, 255, 255); z}");

  for(int k = 0; k < COMMON_MENU_NUMBER; k++)
  {
    QModelIndex index = model->index(k, 0, QModelIndex());
    model->setData(index, k);

    widgetStyleChoice(k);
  }

  ui->tableView->show();
}

void CommonMenuWidget::setCommonMenuName()
{
  initStandardModel();
  for(int k = 0; k < COMMON_MENU_NUMBER; k ++)
  {
    if(COMMON_MENU_STRING[k] != NULL)
    {
      widgetStyleChoice(k);
    }
  }
}

void CommonMenuWidget::widgetStyleChoice(int k)
{
  model->setHeaderData(k, Qt::Horizontal, COMMON_MENU_STRING[k]);
  switch(CHOICE_WIDGET_CHAR[k].toInt())
  {
  case 1:
    {
      DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString::number(0, 'f', 2));
      model->setItem(0, k, item);
      model->item(0, k)->setTextAlignment(Qt::AlignCenter);
      model->item(0, k)->setForeground(Qt::yellow);
      model->item(0, k)->setFont(QFont("Times New Roman", 11));
      ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
      ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
      break;
    }
  case 2:
    {
      ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString("off"));
      model->setItem(0, k, item);
      model->item(0, k)->setTextAlignment(Qt::AlignCenter);
      model->item(0, k)->setForeground(Qt::yellow);
      model->item(0, k)->setFont(QFont("Times New Roman", 11));
      ui->tableView->setItemDelegateForColumn(k, comboBox);
      break;
    }
  case 3:
    {
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString("on"));
      model->setItem(0, k, item);
      model->item(0, k)->setTextAlignment(Qt::AlignCenter);
      model->item(0, k)->setFont(QFont("Times New Roman", 11));
      model->item(0, k)->setFlags(Qt::NoItemFlags);
      break;
    }
  default:
    break;
  }
}

//void CommonMenuWidget::on_pushButton_clicked()
//{
//  static bool flagShowWidget = true;

//  flagShowWidget = !flagShowWidget;

//  if(!flagShowWidget)
//  {
//    hide();
//  }else{
//    show();
//  }
//}

void CommonMenuWidget::resizeEvent(QResizeEvent *event)
{
    width = event->size().width();
    height = event->size().height();
    model->clear();
    initStandardModel();
    setCommonMenuName();
}
