#include "thirdmenuwidget.h"
#include "ui_Thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ThirdMenuWidget)
{
  ui->setupUi(this);

  initStandardModel(0, 0);
}

ThirdMenuWidget::~ThirdMenuWidget()
{
  delete ui;
}

void ThirdMenuWidget::initStandardModel(int i, int j)
{
  model = new QStandardItemModel(1, THIRD_MENU_NUMBER, this);
  ui->tableView->setModel(model);
  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->verticalHeader()->hide();
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                   "{font: 11pt 'Times New Roman';background-color:rgba(61, 61, 61, 0.5);"
                                                   "color:rgba(255, 255, 255, 255); z}");

  for(int k = 0; k < THIRD_MENU_NUMBER; k++)
  {
    QModelIndex index = model->index(k, 0, QModelIndex());
    model->setData(index, k);

    widgetStyleChoice(i, j, k);
  }

  ui->tableView->show();
}

void ThirdMenuWidget::setThirdMenuName(int i, int j)
{
  initStandardModel(i, j);
  for(int k = 0; k < THIRD_MENU_NUMBER; k ++)
  {
    if(THIRD_MENU_STRING[i][j][k] != NULL)
    {
      widgetStyleChoice(i, j, k);
    }
  }
}

void ThirdMenuWidget::widgetStyleChoice(int i, int j, int k)
{
  model->setHeaderData(k, Qt::Horizontal, THIRD_MENU_STRING[i][j][k]);
  switch(WIDGET_CHOICE_CHAR[i][j][k].toInt())
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
