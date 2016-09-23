#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstSecondMenuWidget)
{
    ui->setupUi(this);

    toolBox.append(ui->toolBox);
    QFile *file = new QFile(":/json/resources/menuone.json");
    read_json_file(file);

    initUI();
}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
    delete ui;
}

void FirstSecondMenuWidget::reTranslatorFirstSecondMenuUi()
{
    ui->retranslateUi(this);
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

        if(item->row() == 0) {
            item->setForeground(QBrush(Qt::red));
            menuList.at(i)->setCurrentIndex(modelIndex);
        } else {
            item->setForeground(QBrush(Qt::yellow));
        }
    }

    resize_height(i);
}

void FirstSecondMenuWidget::secondMenuItemClicked(int i, QModelIndex index)
{
    QStringList stringList = get_second_menu_list(i);
    for(int j = 0; j < stringList.count(); j++)
    {
        QModelIndex modelIndex = modelList.at(i)->index(j, 0);
        QStandardItem *item = modelList.at(i)->itemFromIndex(modelIndex);

        if(modelIndex == index) {
            item->setForeground(QBrush(Qt::red));
        } else {
            item->setForeground(QBrush(Qt::yellow));
        }
    }
}

void FirstSecondMenuWidget::initUI()
{
    for(int i = 0; i < FIRST_MENU_NUMBER; i++)
    {
        QListView* listView = findChild<QListView*>("listView_" + QString::number(i + 1));
        listView->setStyleSheet("QListView{font: 14pt 'Times New Roman'}");
        menuList.append(listView);

        firstMenuData.append(ui->toolBox->itemText(i));

        QStandardItemModel *standardItemModel = new QStandardItemModel(this);
        standardItemModel->setObjectName("standardItemModel_"+QString::number(i + 1));
        modelList.append(standardItemModel);

        setSecondMenuName(i);

        QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
        QStandardItem *initItem = modelList.at(i)->itemFromIndex(initModelIndex);
        initItem->setForeground(QBrush(Qt::red));
        menuList.at(i)->setCurrentIndex(initModelIndex);
        menuList.at(i)->setModel(modelList.at(i));
    }

    initSecondMenuItem(0);
    QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
    menuList.at(0)->setCurrentIndex(initModelIndex);
}


void FirstSecondMenuWidget::read_json_file(QFile *file)
{
    QJson::Parser parser;
    bool ok;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file->readAll();
    QVariant variant = parser.parse(str.toUtf8(), &ok);
    firstMenuMap = variant.toMap();
}

QStringList FirstSecondMenuWidget::get_second_menu_list(int i)
{
    QVariantList variantList = firstMenuMap.values(firstMenuData.at(i));
    QStringList stringList  = variantList.at(0).toStringList();
    return stringList;
}

void FirstSecondMenuWidget::resize_height(int i)
{
    QStringList stringList = get_second_menu_list(i);
    int height = menuList.at(i)->fontMetrics().height() * stringList.count() + (menuList.at(i)->spacing() * 2) * stringList.count();
    int mainMenuHeight = this->height() - (menuList.at(i)->height() - height - menuList.at(i)->spacing());
    this->resize(this->width(), mainMenuHeight);
}
