#include "filemanagerdialog.h"
#include "ui_filemanagerdialog.h"

#include "comboboxdelegate.h"

#include <QDebug>

#define FILE_TYPE_NUMBER 6
static const char* FILE_TYPE_STRING[FILE_TYPE_NUMBER] =
{
    QT_TRANSLATE_NOOP("FileManagerDialog", "Setup"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "Data"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "Report"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "Image"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "CAD"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "ALL")
};

#define FILE_PATH_NUMBER 6
static const char* FILE_PATH_STRING[FILE_PATH_NUMBER] =
{
    QT_TRANSLATE_NOOP("FileManagerDialog", "Setup"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "Data"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "Report"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "Image"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "CAD"),
    QT_TRANSLATE_NOOP("FileManagerDialog", "U Storage")
};

FileManagerDialog::FileManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerDialog)
{
    ui->setupUi(this);

    for(int i = 0; i < FILE_TYPE_NUMBER; i ++) {
        fileTypeList.append(tr(FILE_TYPE_STRING[i]));
        filePathList.append(tr(FILE_PATH_STRING[i]));
    }

    init_type();
    init_path();
    init_source_path_tableView();
    init_target_path_tableView();

    connect(ui->tableView_2->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));

}

FileManagerDialog::~FileManagerDialog()
{
    delete ui;
}

void FileManagerDialog::on_pushButton_close_clicked()
{
    close();
}

void FileManagerDialog::init_type()
{
    ui->listView->setStyleSheet("QListView{font: 14pt 'Times New Roman'}");
    modelType = new QStandardItemModel(this);

    QStringList list;
    for(int i = 0; i < fileTypeList.count(); i++) {
        list.append(fileTypeList.at(i));
        QString string = static_cast<QString>(list.at(i));

        QStandardItem *item = new QStandardItem(string);
        modelType->appendRow(item);
        item->setForeground(QBrush(Qt::white, Qt::SolidPattern));
    }

    QModelIndex initModelIndex = modelType->index(0, 0);
    QStandardItem *initItem = modelType->itemFromIndex(initModelIndex);
    initItem->setForeground(QBrush(Qt::red));
    ui->listView->setCurrentIndex(initModelIndex);
    ui->listView->setModel(modelType);

    ui->listView->setSpacing(8);
    ui->listView->setEditTriggers(QAbstractItemView::EditKeyPressed);

}

void FileManagerDialog::init_path()
{
    for(int i = 0; i < FILE_PATH_NUMBER; i ++) {
        ui->comboBox_1->addItem(tr(FILE_PATH_STRING[i]));
        ui->comboBox_2->addItem(tr(FILE_PATH_STRING[i]));
    }
    ui->comboBox_1->setStyleSheet("QComboBox{"
        "font: 12pt 'Times New Roman';"
        "color: black;"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: black;}"
        "QComboBox QAbstractItemView{selection-color:white;}");

    ui->comboBox_2->setStyleSheet("QComboBox{"
        "font: 12pt 'Times New Roman';"
        "color: black;"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: black;}"
        "QComboBox QAbstractItemView{selection-color:white;}");


}
void FileManagerDialog::init_source_path_tableView()
{
    modelSourcePath = new QStandardItemModel(1, 6, this);
    ui->tableView_1->setModel(modelSourcePath);

    int width = this->geometry().width() / 6 * 5;
    ui->tableView_1->horizontalHeader()->resizeSection(0, width / 8);
    ui->tableView_1->horizontalHeader()->resizeSection(1, width / 4);
    ui->tableView_1->horizontalHeader()->resizeSection(2, width / 4);
    ui->tableView_1->horizontalHeader()->resizeSection(3, width / 8 );
    ui->tableView_1->horizontalHeader()->resizeSection(4, width / 8);
    ui->tableView_1->horizontalHeader()->resizeSection(5, width / 8);

    ui->tableView_1->verticalHeader()->hide();
    ui->tableView_1->horizontalHeader()->setFixedHeight(60);
    ui->tableView_1->verticalHeader()->setDefaultSectionSize(30);

    ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
    comboBox->set_comboBox_item_list(fileTypeList);
    comboBox->set_model_item_list(fileTypeList);
    comboBox->set_minimum_contents_length(ui->tableView_1->width());

    QStandardItem *item = new QStandardItem(fileTypeList.at(0));
    modelSourcePath->setItem(0, 0, item);
    modelSourcePath->item(0, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    modelSourcePath->item(0, 0)->setForeground(Qt::black);
    modelSourcePath->item(0, 0)->setFont(QFont("Times New Roman", 14));

    set_tableView_header_data(modelSourcePath);

    ui->tableView_1->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 13pt 'Times New Roman';"
        "background-color: rgba(255, 255, 255, 255);"
        "color: rgba(0, 0, 0, 255);"//rgba(235, 235, 235, 255)
        "border: 0px solid black;}");


    ui->tableView_1->setItemDelegate(comboBox);
    ui->tableView_1->show();
}

void FileManagerDialog::init_target_path_tableView()
{
    modelTargetPath = new QStandardItemModel(1, 6, this);
    ui->tableView_2->setModel(modelTargetPath);

    int width = this->geometry().width() / 6 * 5;
    ui->tableView_2->horizontalHeader()->resizeSection(0, width / 8);
    ui->tableView_2->horizontalHeader()->resizeSection(1, width / 4);
    ui->tableView_2->horizontalHeader()->resizeSection(2, width / 4);
    ui->tableView_2->horizontalHeader()->resizeSection(3, width / 8 );
    ui->tableView_2->horizontalHeader()->resizeSection(4, width / 8);
    ui->tableView_2->horizontalHeader()->resizeSection(5, width / 8);

    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->horizontalHeader()->setFixedHeight(60);
    ui->tableView_2->verticalHeader()->setDefaultSectionSize(30);

    ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
    comboBox->set_comboBox_item_list(fileTypeList);
    comboBox->set_model_item_list(fileTypeList);
    comboBox->set_minimum_contents_length(ui->tableView_2->width());

    QStandardItem *item = new QStandardItem(fileTypeList.at(0));
    modelTargetPath->setItem(0, 0, item);
    modelTargetPath->item(0, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    modelTargetPath->item(0, 0)->setForeground(Qt::black);
    modelTargetPath->item(0, 0)->setFont(QFont("Times New Roman", 14));

    set_tableView_header_data(modelTargetPath);

    ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 13pt 'Times New Roman';"
        "background-color: rgba(255, 255, 255, 255);"
        "color: rgba(0, 0, 0, 255);"
        "border: 0px solid black;}");


    ui->tableView_2->setItemDelegate(comboBox);
    ui->tableView_2->show();
}

void FileManagerDialog::set_tableView_header_data(QStandardItemModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, tr("Number"));
    model->setHeaderData(1, Qt::Horizontal, tr("File Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Modification Time"));
    model->setHeaderData(3, Qt::Horizontal, tr("Copy"));
    model->setHeaderData(4, Qt::Horizontal, tr("Move"));
    model->setHeaderData(5, Qt::Horizontal, tr("Delete"));
}

void FileManagerDialog::on_tableView_1_clicked(const QModelIndex &index)
{
//    ui->tableView_1->edit(index);
}

void FileManagerDialog::onHeaderClicked(int index)
{
//    ComboBoxDelegate *comboBox = static_cast<ComboBoxDelegate*>(ui->tableView_1->itemDelegate());
//    if(!comboBox->editFlag) {
//        QModelIndex modelIndex = model->item(0, index)->index();
//        ui->tableView_1->edit(modelIndex);
//    }
}

void FileManagerDialog::on_listView_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->comboBox_1->setCurrentIndex(row);
    ui->comboBox_2->setCurrentIndex(row);
//    ui->comboBox_1->setCurrentText(filePathList.at(row));
//    ui->comboBox_2->setCurrentText(filePathList.at(row));

    for(int i = 0; i < FILE_TYPE_NUMBER; i++) {
        QModelIndex modelIndex = modelType->index(i, 0);
        QStandardItem *item = modelType->itemFromIndex(modelIndex);
        if(modelIndex == index) {
            item->setForeground(QBrush(Qt::red, Qt::SolidPattern));
            ui->listView->setCurrentIndex(modelIndex);
        } else {
            item->setForeground(QBrush(Qt::white, Qt::SolidPattern));
        }
    }
}

void FileManagerDialog::on_tableView_2_clicked(const QModelIndex &index)
{

}
