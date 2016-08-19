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

    QStandardItemModel *standardItemModel = new QStandardItemModel(this);
    standardItemModel->setObjectName("standardItemModel_"+QString::number(i+1));
    modelList.append(standardItemModel);

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
    menuList.at(i)->setCurrentIndex(initModelIndex);
    menuList.at(i)->setModel(modelList.at(i));
  }
}

void FirstSecondMenuWidget::on_pushButton_bottom_clicked()
{
  int menuTopY = ui->frame_mainMenu->pos().y() + ui->scrollArea->geometry().y();
  int scrollTopY = ui->scrollArea->geometry().y();

  int menuBottomY = ui->scrollArea->viewport()->pos().y() + ui->scrollArea->viewport()->geometry().height();
  int scrollBottomY = ui->scrollArea->geometry().height();

  if(menuBottomY > scrollBottomY)
  {
    ui->scrollArea->viewport()->scroll(0, -50);
    ui->frame_bottom->show();
  }else if(menuBottomY == scrollBottomY)
  {
 //   ui->frame_bottom->hide();
  }

  if(menuTopY == scrollTopY)
  {
    ui->frame_top->hide();
  }else
  {
    ui->frame_top->show();
  }
}

void FirstSecondMenuWidget::on_pushButton_top_clicked()
{
  int menuTopY = ui->frame_mainMenu->pos().y() + ui->scrollArea->geometry().y();
  int scrollTopY = ui->scrollArea->geometry().y();

  int menuBottomY = ui->frame_mainMenu->pos().y() + ui->frame_mainMenu->geometry().height() + ui->scrollArea->geometry().y();
  int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

  if(menuTopY < scrollTopY)
  {
    ui->scrollArea->viewport()->scroll(0, 50);
    ui->frame_top->show();
  }else if(menuTopY == scrollTopY)
  {
    ui->frame_top->hide();
  }

  if(menuBottomY == scrollBottomY)
  {
    ui->pushButton_bottom->hide();
  }
  else
  {
    ui->pushButton_bottom->show();
  }
}
