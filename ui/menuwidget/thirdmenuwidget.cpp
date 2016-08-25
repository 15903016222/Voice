#include "thirdmenuwidget.h"
#include "ui_thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ThirdMenuWidget)
{
  ui->setupUi(this);

  initStandardModel();
  setThirdMenuName(0, 0);
}

ThirdMenuWidget::~ThirdMenuWidget()
{
  delete ui;
}

void ThirdMenuWidget::initStandardModel()
{
  model = new QStandardItemModel(1, THIRD_MENU_NUMBER, this);
  ui->tableView->setModel(model);
//  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
  ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
  ui->tableView->verticalHeader()->hide();
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//  ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);  //Qt-4.8.6

  ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                   "{font: 11pt 'Times New Roman';"
                                                   "background-color: rgba(0, 130, 195, 255);"
                                                   "color: rgba(255, 255, 255, 255);"
                                                   "border: 0px solid black;"
                                                   "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                                   "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

//  ui->tableView->setStyleSheet("QTableView::item{"
//                               "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));"
//                               "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));}");


  for(int k = 0; k < THIRD_MENU_NUMBER; k++)
  {
    QModelIndex index = model->index(k, 0, QModelIndex());
    model->setData(index, k);
  }
  ui->tableView->show();
}

void ThirdMenuWidget::setThirdMenuName(int i, int j)
{
  currFirstNum = i;
  currSecondNum = j;
  model->clear();
  initStandardModel();
  for(int k = 0; k < THIRD_MENU_NUMBER; k ++)
  {
    if(THIRD_MENU_STRING[i][j][k] != NULL)
    {
      widgetStyleChoice(i, j, k);
      model->item(0, k)->setTextAlignment(Qt::AlignCenter);
      model->item(0, k)->setForeground(Qt::yellow);
      model->item(0, k)->setFont(QFont("Times New Roman", 11));
      model->item(0, k)->setBackground(QBrush(QColor(0, 0, 63, 255)));
    }else
    {
      model->setHeaderData(k, Qt::Horizontal, "");
      QStandardItem *item = new QStandardItem(QString(tr("")));
      model->setItem(0, k, item);
      model->item(0, k)->setFlags(Qt::NoItemFlags);
      model->item(0, k)->setBackground(QBrush(QColor(0, 0, 63, 255)));
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
      ui->tableView->setItemDelegateForColumn(k, comboBox);
      break;
    }
  case 3:
    {
      model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      QStandardItem *item = new QStandardItem(QString(""));
      model->setItem(0, k, item);
      break;
    }
  default:
    break;
  }
}

void ThirdMenuWidget::resizeEvent(QResizeEvent *event)
{
  width = event->size().width();
  height = event->size().height();
  model->clear();
  initStandardModel();
  setThirdMenuName(currFirstNum, currSecondNum);
}
