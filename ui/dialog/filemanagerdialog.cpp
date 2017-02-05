#include "filemanagerdialog.h"
#include "ui_filemanagerdialog.h"
#include "inputpanelcontext.h"

#include <QFile>
#include <QMessageBox>
#include <QDebug>

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

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    for(int i = 0; i < FILE_PATH_NUMBER; i ++) {
        m_filePathList.append(tr(FILE_PATH_STRING[i]));
    }

    m_listSetup.append(".conf");

    m_listData.append(".dat");

    m_listReport.append(".html");

    m_listImage.append(".jpg");
    m_listImage.append(".jepg");
    m_listImage.append(".png");
    m_listImage.append(".bmp");

    m_listCAD.append(".dwg");
    m_listCAD.append(".dxf");
    m_listCAD.append(".dws");
    m_listCAD.append(".dwt");
    
    m_listAll.append(m_listSetup);
    m_listAll.append(m_listData);
    m_listAll.append(m_listReport);
    m_listAll.append(m_listImage);
    m_listAll.append(m_listCAD);

    QListWidgetItem *item = ui->listWidget->item(0);
    ui->listWidget->setCurrentItem(item);

    init_path();
    init_source_path_tableView();
    init_target_path_tableView();

    connect(ui->tableView_1->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(do_header1_clicked(int)));
    connect(ui->tableView_2->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(do_header2_clicked(int)));

    m_clickedTableView1 = false;
    m_clickedTableView2 = false;

//    m_dirModel = new QFileSystemModel;
//    m_dirModel->setRootPath(QDir::currentPath());

}

FileManagerDialog::~FileManagerDialog()
{
    delete ui;
}

void FileManagerDialog::on_pushButton_close_clicked()
{
    close();
}

void FileManagerDialog::init_path()
{
    for(int i = 0; i < FILE_PATH_NUMBER; i ++) {
        ui->comboBox_1->addItem(tr(FILE_PATH_STRING[i]));
        ui->comboBox_2->addItem(tr(FILE_PATH_STRING[i]));
    }

    ui->comboBox_1->setStyleSheet("QComboBox{"
        "font: 12pt 'Arial';"
        "color: black;"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: black;}"
        "QComboBox QAbstractItemView{selection-color:white;}");

    ui->comboBox_2->setStyleSheet("QComboBox{"
        "font: 12pt 'Arial';"
        "color: black;"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: black;}"
        "QComboBox QAbstractItemView{selection-color:white;}");

}
void FileManagerDialog::init_source_path_tableView()
{
    m_modelSource = new QFileSystemModel;
    m_modelSource->setRootPath(QDir::rootPath());
    ui->tableView_1->setModel(m_modelSource);

#if QT_VERSION >= 0x050000
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);
#endif

#if QT_VERSION < 0x050000
//    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);
    ui->tableView_1->horizontalHeader()->resizeSections(QHeaderView::Custom);
#endif

    int width = qRound(((qreal)this->geometry().width()) * 5 / 6);
    ui->tableView_1->horizontalHeader()->resizeSection(0, qRound(((qreal)width) / 4));
    ui->tableView_1->horizontalHeader()->resizeSection(1, qRound(((qreal)width) / 4));
    ui->tableView_1->horizontalHeader()->resizeSection(2, qRound(((qreal)width) / 4));
    ui->tableView_1->horizontalHeader()->resizeSection(3, qRound(((qreal)width) / 4));

    ui->tableView_1->horizontalHeader()->setFixedHeight(60);
    ui->tableView_1->verticalHeader()->setDefaultSectionSize(30);

    ui->tableView_1->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableView_1->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 14pt 'Arial';"
        "background-color: rgba(255, 255, 255, 255);"
        "color: rgba(0, 0, 0, 255);"
        "border: 0px solid black;"
        "border-top: 1px solid gray;"
        "border-bottom: 1px solid gray;}");

    ui->tableView_1->show();
}

void FileManagerDialog::init_target_path_tableView()
{
    m_modelTarget = new QFileSystemModel;
    m_modelTarget->setRootPath(QDir::currentPath());
    ui->tableView_2->setModel(m_modelTarget);

#if QT_VERSION >= 0x050000
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);
#endif

#if QT_VERSION < 0x050000
    ui->tableView_2->horizontalHeader()->setResizeMode(QHeaderView::Custom);
#endif

    int width = qRound(((qreal)this->geometry().width()) * 5 / 6);
    ui->tableView_2->horizontalHeader()->resizeSection(0, qRound(((qreal)width) / 4));
    ui->tableView_2->horizontalHeader()->resizeSection(1, qRound(((qreal)width) / 4));
    ui->tableView_2->horizontalHeader()->resizeSection(2, qRound(((qreal)width) / 4));
    ui->tableView_2->horizontalHeader()->resizeSection(3, qRound(((qreal)width) / 4));

    ui->tableView_2->horizontalHeader()->setFixedHeight(60);
    ui->tableView_2->verticalHeader()->setDefaultSectionSize(30);

    ui->tableView_2->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 14pt 'Arial';"
        "background-color: rgba(255, 255, 255, 255);"
        "color: rgba(0, 0, 0, 255);"
        "border: 0px solid black;"
        "border-top: 1px solid gray;"
        "border-bottom: 1px solid gray;}");

    ui->tableView_2->show();
}

void FileManagerDialog::set_tableView_header_data(QFileSystemModel *model)
{
//    model->setHeaderData(1, Qt::Horizontal, tr("File Name"));
//    model->setHeaderData(0, Qt::Horizontal, tr("Type"));
//    model->setHeaderData(2, Qt::Horizontal, tr("Modification Time"));
//    model->setHeaderData(3, Qt::Horizontal, tr("Copy"));
//    model->setHeaderData(4, Qt::Horizontal, tr("Move"));
//    model->setHeaderData(5, Qt::Horizontal, tr("Delete"));
}

void FileManagerDialog::do_header1_clicked(int index)
{
    ui->tableView_1->sortByColumn(index);
}

void FileManagerDialog::do_header2_clicked(int index)
{
    ui->tableView_2->sortByColumn(index);
}

void FileManagerDialog::on_listWidget_clicked(const QModelIndex &index)
{
    int row = index.row();
    ui->comboBox_1->setCurrentIndex(row);
    ui->comboBox_2->setCurrentIndex(row);
    ui->listWidget->setCurrentIndex(index);
}

void FileManagerDialog::on_tableView_1_pressed(const QModelIndex &index)
{
//    QString fromDir = ui->comboBox_1->currentText() + "/"/* + ui->tableView_1->item(index.row(), 0)->text()*/;
//    QString toDir = ui->comboBox_2->currentText() + "/";
//    if(index.column() == 3) {
//        copy_file_to_path(fromDir, toDir);
//    } else if(index.column() == 4) {
//        cut_file_to_path(fromDir, toDir);
//    } else if(index.column() == 5) {
//        delete_file(fromDir);
//    }
    m_clickedTableView1 = true;
    m_clickedTableView2 = false;
    m_clickedIndex1 = index;
}

void FileManagerDialog::on_tableView_2_pressed(const QModelIndex &index)
{
//    QString fromDir = ui->comboBox_2->currentText() + "/" /*+ ui->tableView_2->item(index.row(), 0)->text()*/;
//    QString toDir = ui->comboBox_1->currentText() + "/";
//    if(index.column() == 3) {
//        copy_file_to_path(fromDir, toDir);
//    } else if(index.column() == 4) {
//        cut_file_to_path(fromDir, toDir);
//    } else if(index.column() == 5) {
//        delete_file(fromDir);
//    }
    m_clickedTableView1 = false;
    m_clickedTableView2 = true;
    m_clickedIndex2 = index;
}

void FileManagerDialog::copy_file_to_path(QString fromDir, QString toDir)
{
    if(fromDir == toDir) {
        return;
    }
    if(!QFile::exists(fromDir)) {
        return;
    }
    if(!QFile::copy(fromDir, toDir)) {
        return;
    }
}

void FileManagerDialog::on_pushButton_select_clicked()
{
//    if(m_clickedTableView1) {
//        ui->tableView_1->setSelectionBehavior(QAbstractItemView::SelectRows);
////        emit ui->tableView_1->pressed(m_clickedIndex1);
//    } else {
//        ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
////        emit ui->tableView_2->pressed(m_clickedIndex2);
//    }
}

void FileManagerDialog::on_pushButton_selectAll_clicked()
{

}

void FileManagerDialog::on_pushButton_rename_clicked()
{
    InputPanelContext *dialog = new InputPanelContext;
    dialog->exec();
    delete dialog;
}

void FileManagerDialog::on_comboBox_1_currentIndexChanged(const QString &arg1)
{
//    do_file_filters(ui->tableView_1, m_modelSource, arg1);
}

void FileManagerDialog::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
//    do_file_filters(ui->tableView_2, m_modelTarget, arg1);
}

void FileManagerDialog::do_file_filters(QTableView *view, QFileSystemModel *model, const QString &str)
{
    if(str == tr("Setup")) {
        model->setNameFilters(m_listSetup);
    } else if(str == tr("Data")) {
        model->setNameFilters(m_listData);
    } else if(str == tr("Report")) {
        model->setNameFilters(m_listReport);
    } else if(str == tr("Image")) {
        model->setNameFilters(m_listImage);
    } else if(str == tr("CAD")) {
        model->setNameFilters(m_listCAD);
    }
    model->setNameFilterDisables(false);
    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));
}

void FileManagerDialog::on_pushButton_copy_clicked()
{
    if(m_clickedTableView1) {
        copy_file_to_path(m_modelSource->filePath(m_clickedIndex1), m_modelTarget->rootPath());
    } else if(m_clickedTableView2) {
        copy_file_to_path(m_modelTarget->filePath(m_clickedIndex2), m_modelSource->rootPath());
    }
}

void FileManagerDialog::on_pushButton_move_clicked()
{
    on_pushButton_copy_clicked();
    on_pushButton_delete_clicked();
}

void FileManagerDialog::on_pushButton_delete_clicked()
{
    bool ok;
    if(!m_clickedTableView1 && !m_clickedTableView2) {
        return;
    } else if(m_clickedTableView1  && !m_clickedTableView2) {
        ok = m_modelSource->remove(m_clickedIndex1);
        if(!ok) {
            QMessageBox::information(this, tr("Remove"), tr("It's failed to remove the file %1.").arg(m_modelSource->fileName(m_clickedIndex1)));
        }
    } else if(!m_clickedTableView1 && m_clickedTableView1) {
        ok = m_modelTarget->remove(m_clickedIndex2);
        if(!ok) {
            QMessageBox::information(this, tr("Remove"), tr("It's failed to remove the file %1.").arg(m_modelTarget->fileName(m_clickedIndex2)));
        }
    }
}
