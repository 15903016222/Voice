#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FirstSecondMenuWidget)
{
  ui->setupUi(this);

  initUI();
}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
  delete ui;
}

void FirstSecondMenuWidget::setSecondMenuName(int i)
{
  QStringList secondMenuList;
  for(int j = 0; j < SECOND_MENU_NUMBER; j++)
  {
    if(SECOND_MENU_STRING[i][j] != NULL)
    {
      secondMenuList.append(SECOND_MENU_STRING[i][j]);
      QString string = static_cast<QString>(secondMenuList.at(j));

      QStandardItem *item = new QStandardItem(string);
      modelList.at(i)->appendRow(item);
      item->setForeground(QBrush(Qt::yellow));
    }
  }
}

void FirstSecondMenuWidget::initSecondMenuItem(int i)
{
  for(int j = 0; j < SECOND_MENU_NUMBER; j++)
  {
    if(SECOND_MENU_STRING[i][j] != NULL)
    {
      QModelIndex modelIndex = modelList.at(i)->index(j, 0);
      QStandardItem *item = modelList.at(i)->itemFromIndex(modelIndex);

      if(item->row() == 0)
      {
        item->setForeground(QBrush(Qt::red));
        menuList.at(i)->setCurrentIndex(modelIndex);
      }else{
        item->setForeground(QBrush(Qt::yellow));
      }
    }
  }
}

void FirstSecondMenuWidget::secondMenuItemClicked(int i, QModelIndex index)
{
  for(int j = 0; j < SECOND_MENU_NUMBER; j++)
  {
    if(SECOND_MENU_STRING[i][j] != NULL)
    {
      QModelIndex modelIndex = modelList.at(i)->index(j, 0);
      QStandardItem *item = modelList.at(i)->itemFromIndex(modelIndex);

      if(modelIndex == index)
      {
        item->setForeground(QBrush(Qt::red));
      }else{
        item->setForeground(QBrush(Qt::yellow));
      }
    }
  }
}

void FirstSecondMenuWidget::initUI()
{
  toolBox.append(ui->toolBox);

  for(int i = 0; i < FIRST_MENU_NUMBER; i++)
  {
    QListView* listView = findChild<QListView*>("listView_" + QString::number(i+1));
    listView->setStyleSheet("QListView{font: 13px}");
    listView->adjustSize();
    menuList.append(listView);

    QStandardItemModel *standardItemModel = new QStandardItemModel(this);
    standardItemModel->setObjectName("standardItemModel_"+QString::number(i+1));
    modelList.append(standardItemModel);

    setSecondMenuName(i);

    QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
    QStandardItem *initItem = modelList.at(i)->itemFromIndex(initModelIndex);
    initItem->setForeground(QBrush(Qt::red));
    menuList.at(i)->setCurrentIndex(initModelIndex);
    menuList.at(i)->setModel(modelList.at(i));
  }

  ui->toolBox->setCurrentIndex(0);
  QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
  menuList.at(0)->setCurrentIndex(initModelIndex);
}
