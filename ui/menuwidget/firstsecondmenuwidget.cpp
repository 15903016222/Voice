#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

#include <QDebug>

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstSecondMenuWidget)
{
    ui->setupUi(this);

    toolBox.append(ui->toolBox);

    QFile *file = new QFile(":/json/resources/menuconf.json");
    firstMenuMap = read_json_file(file);
    QFile *fileTranslate = new QFile(":/json/resources/menutr_CHN.json");
    translateChineseMap = read_json_file(fileTranslate);

    init_ui();

    m_mcu = Mcu::get_mcu();
 //   connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
    delete ui;
}

void FirstSecondMenuWidget::retranslate_main_menu_ui()
{
    ui->retranslateUi(this);
}

void FirstSecondMenuWidget::set_second_menu_name(int i)
{
    QStringList secondMenuList;
    QStringList stringList = get_second_menu_list(i);

    for(int j = 0; j < stringList.count(); j++) {
        secondMenuList.append(stringList.at(j));

        QString string = static_cast<QString>(secondMenuList.at(j));

        QStandardItem *item = new QStandardItem(string);
        modelList.at(i)->appendRow(item);
        item->setForeground(QBrush(Qt::yellow, Qt::SolidPattern));
    }
}

void FirstSecondMenuWidget::set_second_menu_item_style(int i, QModelIndex index)
{
    QStringList stringList = get_second_menu_list(i);
    for(int j = 0; j < stringList.count(); j++) {
        QModelIndex modelIndex = modelList.at(i)->index(j, 0);
        QStandardItem *item = modelList.at(i)->itemFromIndex(modelIndex);

        if(modelIndex == index) {
            item->setForeground(QBrush(Qt::red, Qt::SolidPattern));
            menuList.at(i)->setCurrentIndex(modelIndex);
        } else {
            item->setForeground(QBrush(Qt::yellow, Qt::SolidPattern));
        }
    }

    resize_height(i);
}

void FirstSecondMenuWidget::init_ui()
{
    for(int i = 0; i < FIRST_MENU_NUMBER; i++) {
        QListView* listView = findChild<QListView*>("listView_" + QString::number(i + 1));
        listView->setStyleSheet("QListView{font: 14pt 'Times New Roman'}");
        menuList.append(listView);

        firstMenuData.append(ui->toolBox->itemText(i));

        QStandardItemModel *standardItemModel = new QStandardItemModel(this);
        standardItemModel->setObjectName("standardItemModel_"+QString::number(i + 1));
        modelList.append(standardItemModel);

        set_second_menu_name(i);

        QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
        QStandardItem *initItem = modelList.at(i)->itemFromIndex(initModelIndex);
        initItem->setForeground(QBrush(Qt::red));
        menuList.at(i)->setCurrentIndex(initModelIndex);
        menuList.at(i)->setModel(modelList.at(i));
    }

    QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
    set_second_menu_item_style(0, initModelIndex);
}


QVariantMap FirstSecondMenuWidget::read_json_file(QFile *file)
{
    QJson::Parser parser;
    bool ok;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file->readAll();
    QVariantMap variantMap = parser.parse(str.toUtf8(), &ok).toMap();
    if(!ok) {
        qDebug() << "An error occured during parsing.";
    }
    file->close();
    return variantMap;
}

QStringList FirstSecondMenuWidget::get_second_menu_list(int i)
{
    QVariantMap variantMap = firstMenuMap[firstMenuData.at(i)].toMap();
    QVariantList variantList = variantMap.values("Queue_Second_Menu");
    QStringList stringList  = variantList.at(0).toStringList();
    return stringList;
}

void FirstSecondMenuWidget::do_rotary_event(Mcu::RotaryType type)
{
    //  int i = ui->verticalSliderBrightness->value();
      int i = 0;
   //   m_mcu->set_brightness((char)value);
      if (type == Mcu::ROTARY_UP) {
          ++i;
      } else {
          --i;
      }
   //   ui->verticalSliderBrightness->setValue(i);
}

void FirstSecondMenuWidget::resize_height(int i)
{
    QStringList stringList = get_second_menu_list(i);
    int height = menuList.at(i)->fontMetrics().height() * stringList.count() + (menuList.at(i)->spacing() * 2) * stringList.count();
    int mainMenuHeight = this->height() - (menuList.at(i)->height() - height - menuList.at(i)->spacing());
    this->resize(this->width(), mainMenuHeight);
}
