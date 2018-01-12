#include "file_dialog.h"
#include "ui_file_dialog.h"

#include <QPainter>
#include <QShowEvent>
#include <QDebug>
#include <QDir>
#include <QStandardItemModel>
#include <QListWidgetItem>

FileDialog::FileDialog(const S_FileDialogParameters &dialogParameters, QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);

    ui->titleLabel->setStyleSheet("");
    ui->titleLabel->setText(dialogParameters.title);
    ui->okPushButton->setText(dialogParameters.okButtonText);

    ui->cancelPushButton->setText(dialogParameters.cancelButtonText);

    init_file_list(dialogParameters.filePath, dialogParameters.nameFilters);

    ui->okPushButton->setFocus();

    ui->fileNameLineEdit->setFocusPolicy(Qt::NoFocus);

    m_fileType = (E_FileType)ui->fileTypeComboBox->currentIndex();

    if(dialogParameters.operation != Update) {
        ui->fileTypeComboBox->hide();
        ui->fileTypeLabel->hide();
    }

    connect(ui->fileTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_currentIndexChanged(int)));
}

FileDialog::~FileDialog()
{
    delete ui;
}

QString FileDialog::get_selected_file_name()
{
    return m_selectedFile;
}

void FileDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Escape:
        {
            on_cancelPushButton_clicked();
            break;
        }
        case Qt::Key_Return:
        {
            on_okPushButton_clicked();
            break;
        }
    }
}

void FileDialog::on_cancelPushButton_clicked()
{
    m_selectedFile.clear();
    reject();
}

void FileDialog::on_okPushButton_clicked()
{
    accept();
}

void FileDialog::do_fileListWidget_currentItenChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    ui->fileNameLineEdit->setText(m_fileInfoList.at(ui->fileListWidget->currentIndex().row()).fileName());
    m_selectedFile = m_fileInfoList.at(ui->fileListWidget->currentIndex().row()).filePath();
}

void FileDialog::slot_currentIndexChanged(int index)
{
    m_fileType = (E_FileType)index;
}

void FileDialog::init_file_list(const QString &filePath, const QStringList &nameFilters)
{
    QDir dir(filePath);
    m_fileInfoList = dir.entryInfoList(nameFilters, QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    QStringList stringList;
    for(int i = 0; i < m_fileInfoList.size(); ++i) {
        stringList << m_fileInfoList.at(i).fileName();
    }

    ui->fileListWidget->insertItems(0, stringList);

    connect(ui->fileListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(do_fileListWidget_currentItenChanged(QListWidgetItem*,QListWidgetItem*)));


    ui->fileListWidget->setCurrentIndex(ui->fileListWidget->model()->index(0, 0));
}

