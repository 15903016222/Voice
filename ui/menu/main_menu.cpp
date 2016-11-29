#include "main_menu.h"
#include "ui_main_menu.h"

#include <QKeyEvent>
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

//    QFile *fileTranslate = new QFile(":/file/json/menutr_CHN.json");
//    translateChineseMap = read_json_file(fileTranslate);

    m_languageOption = 1;

    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(0);
    ui->treeWidget->expandItem(item);

    QTreeWidgetItem *initItem = item->child(0);
    ui->treeWidget->setCurrentItem(initItem);

    ui->treeWidget->setExpandsOnDoubleClick(false);
    ui->treeWidget->setRootIsDecorated(false);
    ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeWidget->installEventFilter(this);

    m_firstCount = ui->treeWidget->topLevelItemCount();
    qDebug() << m_firstCount;
    ui->treeWidget->setFocus();

    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(change_item_selection()));

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::change_item_selection()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item->childCount() > 0) {
        ui->treeWidget->collapseAll();
        ui->treeWidget->expandItem(item);
        QTreeWidgetItem *initItem = item->child(0);
        ui->treeWidget->setCurrentItem(initItem);

        int index = ui->treeWidget->indexOfTopLevelItem(item);
        if(index >= 4 && index < m_firstCount) {
            ui->treeWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
        }
    } else {
//        ui->textEdit->setText(item->text(0));
    }
    qDebug() << "itemSelectionChanged" << ui->treeWidget->currentItem()->text(0);
}

bool MainMenu::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QTreeWidgetItem *previous = ui->treeWidget->currentItem();
        int index = ui->treeWidget->indexOfTopLevelItem(previous->parent());
        int subIndex = previous->parent()->indexOfChild(previous);

        QTreeWidgetItem *current;

        switch (keyEvent->key()) {
        case Qt::Key_Up:
            if(subIndex == 0) {
                if(index > 0) {
                    QTreeWidgetItem *newItem = ui->treeWidget->topLevelItem(index - 1);
                    ui->treeWidget->collapseItem(previous->parent());
                    ui->treeWidget->expandItem(newItem);
                    current = newItem->child(newItem->childCount() - 1);
                    ui->treeWidget->setCurrentItem(current);
                }
            } else {
                current = previous->parent()->child(subIndex - 1);
                ui->treeWidget->setCurrentItem(current);
            }
            return true;
        case Qt::Key_Down:
            if(subIndex == (previous->parent()->childCount() - 1)) {
                if(index < m_firstCount - 1) {
                    QTreeWidgetItem *newItem = ui->treeWidget->topLevelItem(index + 1);
                    ui->treeWidget->collapseItem(previous->parent());
                    ui->treeWidget->expandItem(newItem);
                    current = newItem->child(0);
                    ui->treeWidget->setCurrentItem(current);
                }
            } else {
                current = previous->parent()->child(subIndex + 1);
                ui->treeWidget->setCurrentItem(current);
            }
            return true;
        case Qt::Key_Enter:
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(object, event);
}


//void MainMenu::resize_height(int i)
//{
//    QStringList stringList = get_second_menu_list(i);
//    int height = menuList.at(i)->fontMetrics().height() * stringList.count() + (menuList.at(i)->spacing() * 2) * stringList.count();
//    int mainMenuHeight = this->height() - (menuList.at(i)->height() - height - menuList.at(i)->spacing());
//    this->resize(this->width(), mainMenuHeight);
//}


//FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::FirstSecondMenuWidget)
//{
//    ui->setupUi(this);

//    toolBox.append(ui->toolBox);

//    QFile *file = new QFile(":/file/json/menuconf.json");
//    firstMenuMap = read_json_file(file);
//    QFile *fileTranslate = new QFile(":/file/json/menutr_CHN.json");
//    translateChineseMap = read_json_file(fileTranslate);

//    m_languageOption = 1;

//    init_ui();
//    QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
//    set_second_menu_item_style(0, initModelIndex);
//}

//FirstSecondMenuWidget::~FirstSecondMenuWidget()
//{
//    delete ui;
//}

//void FirstSecondMenuWidget::retranslate_main_menu_ui(QString string)
//{
//    ui->retranslateUi(this);
//    if(string == "Chinese") {
//        m_languageOption = 2;
//    } else if(string == "English") {
//        m_languageOption = 1;
//    }
//    init_ui();
//    QModelIndex initModelIndex = modelList.at(8)->index(1, 0);
//    set_second_menu_item_style(8, initModelIndex);
//}

//void FirstSecondMenuWidget::set_second_menu_name(int i)
//{
//    QStringList secondMenuList;
//    QStringList stringList = get_second_menu_list(i);

//    if(modelList.at(i)->rowCount() == stringList.count()) {
//        modelList.at(i)->removeRows(0, stringList.count());
//    }

//    for(int j = 0; j < stringList.count(); j++) {
//        secondMenuList.append(stringList.at(j));
//        QString string = static_cast<QString>(secondMenuList.at(j));

//        QStandardItem *item = new QStandardItem(string);
//        modelList.at(i)->appendRow(item);
//    }
//}

//void FirstSecondMenuWidget::set_second_menu_item_style(int i, QModelIndex index)
//{
//    menuList.at(i)->setCurrentIndex(index);

//    resize_height(i);
//}

//void FirstSecondMenuWidget::init_ui()
//{
//    for(int i = 0; i < FIRST_MENU_NUMBER; i++) {
//        QListView* listView = findChild<QListView*>("listView_" + QString::number(i + 1));
//        listView->setStyleSheet("QListView{font: 14pt 'Times New Roman';"
//                                "outline: 0px;}"
//                                "QListView::item{"
//                                "background-color: rgba(0, 0, 0, 0);"
//                                "color: yellow;}"
//                                "QListView::item:selected{"
//                                "background-color: rgba(0, 0, 0, 0);"
//                                "color: red;}");

//        if(menuList.size() == 9) {
//            menuList.clear();
//        }
//        menuList.append(listView);

//        firstMenuData.append(ui->toolBox->itemText(i));

//        QStandardItemModel *standardItemModel = new QStandardItemModel(this);
//        standardItemModel->setObjectName("standardItemModel_"+QString::number(i + 1));
//        if(modelList.size() == 9) {
//            modelList.clear();
//        }
//        modelList.append(standardItemModel);

//        set_second_menu_name(i);

//        QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
//        menuList.at(i)->setCurrentIndex(initModelIndex);
//        menuList.at(i)->setModel(modelList.at(i));
//    }
//}

//QStringList FirstSecondMenuWidget::get_second_menu_list(int i)
//{
//    QStringList stringList;
//    if(m_languageOption == 1) {
//        QVariantMap variantMap = firstMenuMap[firstMenuData.at(i)].toMap();
//        QVariantList variantList = variantMap.values("Queue_Second_Menu");
//        stringList  = variantList.at(0).toStringList();
//    } else if(m_languageOption == 2) {
//        QVariantMap variantMap = translateChineseMap[firstMenuData.at(i)].toMap();
//        QVariantList variantList = variantMap.values("Translate_Second_Menu");
//        stringList  = variantList.at(0).toStringList();
//    }
//    return stringList;
//}


