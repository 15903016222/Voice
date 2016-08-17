#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FirstSecondMenuWidget)
{
  ui->setupUi(this);

  initUI();
  ui->toolBox->setCurrentIndex(0);
  QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
  menuList.at(0)->setCurrentIndex(initModelIndex);
//  hideFirstMenuPage();

}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
  delete ui;
}

void FirstSecondMenuWidget::hideFirstMenuPage()
{
  ui->page_9->hide();
  ui->page_8->hide();
  ui->page_7->hide();
  ui->page_6->hide();

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

    QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
    QStandardItem *initItem = modelList.at(i)->itemFromIndex(initModelIndex);
    initItem->setForeground(QBrush(Qt::red));
    menuList.at(i)->setCurrentIndex(initModelIndex);
    menuList.at(i)->setModel(modelList.at(i));
  }
}
