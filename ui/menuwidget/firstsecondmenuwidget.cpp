#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

#include <QTextCodec>
#include <QMessageBox>

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

    languageOption = 1;

    init_ui();
    QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
    set_second_menu_item_style(0, initModelIndex);

    m_mcu = Mcu::get_mcu();
 //   connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
    delete ui;
}

void FirstSecondMenuWidget::retranslate_main_menu_ui(QString string)
{
    ui->retranslateUi(this);
    if(string == "Chinese") {
        languageOption = 2;
    } else if(string == "English") {
        languageOption = 1;
    }
    init_ui();
    QModelIndex initModelIndex = modelList.at(8)->index(1, 0);
    set_second_menu_item_style(8, initModelIndex);
}

void FirstSecondMenuWidget::set_second_menu_name(int i)
{
    QStringList secondMenuList;
    QStringList stringList = get_second_menu_list(i);

    if(modelList.at(i)->rowCount() == stringList.count()) {
        modelList.at(i)->removeRows(0, stringList.count());
    }

    for(int j = 0; j < stringList.count(); j++) {
        secondMenuList.append(stringList.at(j));
        QString string = static_cast<QString>(secondMenuList.at(j));

        QStandardItem *item = new QStandardItem(string);
        modelList.at(i)->appendRow(item);
    }
}

void FirstSecondMenuWidget::set_second_menu_item_style(int i, QModelIndex index)
{
    QStringList stringList = get_second_menu_list(i);
    for(int j = 0; j < stringList.count(); j++) {
        QModelIndex modelIndex = modelList.at(i)->index(j, 0);
        if(modelIndex == index) {
            menuList.at(i)->setCurrentIndex(modelIndex);
        }
    }

    resize_height(i);
}

void FirstSecondMenuWidget::init_ui()
{
    for(int i = 0; i < FIRST_MENU_NUMBER; i++) {
        QListView* listView = findChild<QListView*>("listView_" + QString::number(i + 1));
        listView->setStyleSheet("QListView{font: 14pt 'Times New Roman';"
                                "outline: 0px;}"
                                "QListView::item{"
                                "background-color: rgba(0, 0, 0, 0);"
                                "color: yellow;}"
                                "QListView::item:Selected{"
                                "background-color: rgba(0, 0, 0, 0);"
                                "color: red;}");

        if(menuList.size() == 9) {
            menuList.clear();
        }
        menuList.append(listView);

        firstMenuData.append(ui->toolBox->itemText(i));

        QStandardItemModel *standardItemModel = new QStandardItemModel(this);
        standardItemModel->setObjectName("standardItemModel_"+QString::number(i + 1));
        if(modelList.size() == 9) {
            modelList.clear();
        }
        modelList.append(standardItemModel);


        set_second_menu_name(i);

        QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
        menuList.at(i)->setCurrentIndex(initModelIndex);
        menuList.at(i)->setModel(modelList.at(i));
    }
}

QVariantMap FirstSecondMenuWidget::read_json_file(QFile *file)
{
    QJson::Parser parser;
    bool ok;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file->readAll();
    QVariantMap variantMap = parser.parse(str.toUtf8(), &ok).toMap();
    if(!ok) {
        QMessageBox::warning(this, tr("Parsing file Error"), tr("Read file failure!"));
    }
    file->close();

#if (PHASCAN | PHASCAN_II)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    setFont(QFont("utf8",14,QFont::Normal));
#endif

    return variantMap;
}

QStringList FirstSecondMenuWidget::get_second_menu_list(int i)
{
    QStringList stringList;
    if(languageOption == 1) {
        QVariantMap variantMap = firstMenuMap[firstMenuData.at(i)].toMap();
        QVariantList variantList = variantMap.values("Queue_Second_Menu");
        stringList  = variantList.at(0).toStringList();
    } else if(languageOption == 2) {
        QVariantMap variantMap = translateChineseMap[firstMenuData.at(i)].toMap();
        QVariantList variantList = variantMap.values("Translate_Second_Menu");
        stringList  = variantList.at(0).toStringList();
    }
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
