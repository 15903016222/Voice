#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

#include <QDebug>
#include <QFile>

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FirstSecondMenuWidget)
{
  ui->setupUi(this);

  QFile *file = new QFile(":/json/resources/menuone.json");
  read_json_file(file);

  initUI();
}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
  delete ui;
}

void FirstSecondMenuWidget::setSecondMenuName(int i)
{
  QStringList secondMenuList;
  QStringList stringList = get_second_menu_list(i);
  for(int j = 0; j < stringList.count(); j++)
  {
      secondMenuList.append(stringList.at(j));

      QString string = static_cast<QString>(secondMenuList.at(j));

      QStandardItem *item = new QStandardItem(string);
      modelList.at(i)->appendRow(item);
      item->setForeground(QBrush(Qt::yellow));
  }
}

void FirstSecondMenuWidget::initSecondMenuItem(int i)
{
  QStringList stringList = get_second_menu_list(i);
  for(int j = 0; j < stringList.count(); j++)
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

void FirstSecondMenuWidget::secondMenuItemClicked(int i, QModelIndex index)
{
  QStringList stringList = get_second_menu_list(i);
  for(int j = 0; j < stringList.count(); j++)
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

void FirstSecondMenuWidget::initUI()
{
  toolBox.append(ui->toolBox);

  for(int i = 0; i < FIRST_MENU_NUMBER; i++)
  {
    QListView* listView = findChild<QListView*>("listView_" + QString::number(i+1));
    listView->setStyleSheet("QListView{font: 14px}");
    listView->adjustSize();
    menuList.append(listView);

    firstMenuData.append(ui->toolBox->itemText(i));

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

void FirstSecondMenuWidget::read_json_file(QFile *file)
{
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file->readAll();
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toUtf8(), &error);
    if(error.error == QJsonParseError::NoError) {
        if(!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
            if(jsonDocument.isObject()) {
                QJsonObject jsonObject = jsonDocument.object();
                firstMenuHash = jsonObject.toVariantHash();
            } else if(jsonDocument.isArray()) {

            }
        }
    } else {

    }
}

QStringList FirstSecondMenuWidget::get_second_menu_list(int i)
{
    QVariantList variantList = firstMenuHash.values(firstMenuData.at(i));
    QStringList stringList = variantList.at(0).toStringList();
    return stringList;
}
