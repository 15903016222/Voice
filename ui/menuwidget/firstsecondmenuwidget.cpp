#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FirstSecondMenuWidget)
{
  ui->setupUi(this);

  initUI();

  ui->frame_top->hide();
  ui->scrollAreaWidgetContents->setMinimumSize(50, 600);

}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
  delete ui;
}

void FirstSecondMenuWidget::initUI()
{
  toolBox.append(ui->toolBox);

  for(int i = 0; i < FIRST_MENU_NUMBER; i++)
  {
    QListView* listView = findChild<QListView*>("listView_" + QString::number(i+1));
    menuList.append(listView);

    QStandardItemModel *standardItemModel_1 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_2 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_3 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_4 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_5 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_6 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_7 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_8 = new QStandardItemModel(this);
    QStandardItemModel *standardItemModel_9 = new QStandardItemModel(this);

    modelList.append(standardItemModel_1);
    modelList.append(standardItemModel_2);
    modelList.append(standardItemModel_3);
    modelList.append(standardItemModel_4);
    modelList.append(standardItemModel_5);
    modelList.append(standardItemModel_6);
    modelList.append(standardItemModel_7);
    modelList.append(standardItemModel_8);
    modelList.append(standardItemModel_9);

    QStringList secondMenuList;
    for(int j = 0; j < SECOND_MENU_NUMBER; j++)
    {
      secondMenuList.append(SECOND_MENU_STRING[i][j]);

      QString string = static_cast<QString>(secondMenuList.at(j));
      QStandardItem *item = new QStandardItem(string);
      modelList.at(i)->appendRow(item);
      item->setForeground(QBrush(Qt::yellow));
    }

    QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
    QStandardItem *initItem = modelList.at(i)->itemFromIndex(initModelIndex);
    initItem->setForeground(QBrush(Qt::red));

    menuList.at(i)->setModel(modelList.at(i));
  }
}

void FirstSecondMenuWidget::on_pushButton_bottom_clicked()
{
  ui->frame_top->show();
//  if(ui->scrollArea->viewport()->depth() < 600)
  {
    ui->scrollArea->viewport()->scroll(0, -50);
  }
}

void FirstSecondMenuWidget::on_pushButton_top_clicked()
{
//  if(ui->scrollArea->viewport()->depth() < 600)
  {
    ui->scrollArea->viewport()->scroll(0, 50);
  }
}
