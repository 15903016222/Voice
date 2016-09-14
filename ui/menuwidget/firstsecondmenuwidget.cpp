#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

#include <QVariant>

//static const char* SECOND_MENU_STRING[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER] = {
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "General"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Pulser"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Receiver"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Advanced")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Gate"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Alarm"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Output"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "DAC"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "TCG")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Selection"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Color Setting"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Properties")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Select"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Position"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "FFT"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Part"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Advanced")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Law Config"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Angle"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Aperture"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Focal Point")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Inspection"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Encoder"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Area"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Start")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Reading"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Cursors"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "TOFD"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Flaw Record")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "File"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Save Mode"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Report"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Format"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "User Field")
//    },
//    {
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Preference"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "System"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Network"),
//        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Service")
//    }
//};
#include <QDebug>

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

//void FirstSecondMenuWidget::reTranslatorFirstSecondMenuUi()
//{
//    ui->retranslateUi(this);

//    qDebug()<<__func__<<tr(SECOND_MENU_STRING[0][0]);

//}

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

    int height = 0;
    height = menuList.at(i)->fontMetrics().height() * stringList.count() + (menuList.at(i)->spacing() * 2) * stringList.count();
    int mainMenuHeight = this->height() - (menuList.at(i)->height() - height - menuList.at(i)->spacing());
    this->resize(this->width(), mainMenuHeight);
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
    toolBox.append(ui->toolBox);

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
//#if QT_VERSION >= 0x050000
//    file->open(QIODevice::ReadOnly | QIODevice::Text);
//    QString str = file->readAll();
//    QJsonParseError error;
//    QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toUtf8(), &error);
//    if(error.error == QJsonParseError::NoError) {
//        if(!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
//            if(jsonDocument.isObject()) {
//                QJsonObject jsonObject = jsonDocument.object();
//                firstMenuHash = jsonObject.toVariantHash();
//            } else if(jsonDocument.isArray()) {

//            }
//        }
//    } else {

//    }
//#endif

//#if QT_VERSION < 0x050000
    QJson::Parser parser;
    bool ok;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file->readAll();
    QVariant variant = parser.parse(str.toUtf8(), &ok);
    firstMenuMap = variant.toMap();
    if(!ok) {
        qDebug() << "An error occured during parsing.";
    }
//#endif
}

QStringList FirstSecondMenuWidget::get_second_menu_list(int i)
{
//#if QT_VERSION >= 0x050000
//    QVariantList variantList = firstMenuHash.values(firstMenuData.at(i));
//    QStringList stringList = variantList.at(0).toStringList();
//    return stringList;
//
//#endif

//#if QT_VERSION < 0x050000
    QVariantList variantList = firstMenuMap.values(firstMenuData.at(i));
    QStringList stringList  = variantList.at(0).toStringList();
    return stringList;
//#endif
}
