#include "base_open_file_dialog.h"
#include "ui_base_open_file_dialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QIcon>
#include <QKeyEvent>
#include <QPainter>

static const QString SLASH = "/";

BaseOpenFileDialog::BaseOpenFileDialog(const QString &basePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseOpenFileDialog),
    m_basePath(basePath),
    m_standardItemModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground);       /* 设置窗口背景透明 */

    ui->pathComboBox->addItem(SLASH);

    m_currentFileList = get_file_list(basePath);

    update_model();

    connect(ui->filesTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(do_filesTasbleView_clicked(QModelIndex)));

    ui->filesTableView->setFocus();

}

BaseOpenFileDialog::~BaseOpenFileDialog()
{
    delete ui;
}

QString BaseOpenFileDialog::get_selected_file() const
{
    if(ui->fileNameLineEdit->text().isEmpty()) {
        return tr("");
    }

    if(ui->pathComboBox->currentText() == SLASH) {
        return m_basePath + SLASH + ui->fileNameLineEdit->text();
    } else {
        return m_basePath + ui->pathComboBox->currentText() + SLASH + ui->fileNameLineEdit->text();
    }
}


void BaseOpenFileDialog::on_openBtn_clicked()
{
    close();
}


void BaseOpenFileDialog::on_cancleBtn_clicked()
{
    ui->fileNameLineEdit->setText(tr(""));
    close();
}


void BaseOpenFileDialog::on_backBtn_clicked()
{
    if(ui->pathComboBox->currentText().length() <= 1) {
        return;
    }

    QString targetPath = ui->pathComboBox->currentText();
    QStringList cell =targetPath.split(SLASH);

    targetPath.clear();

    for(int i = 0; i < cell.count(); ++i) {

        if(i == (cell.count() - 1)) {
            break;
        }

        if(cell.at(i).isEmpty()) {
            continue;
        }

        targetPath.append(SLASH);
        targetPath.append(cell.at(i));
    }

    m_currentFileList = get_file_list(m_basePath + targetPath);

    update_model();

    if(targetPath.isEmpty()) {
        targetPath = SLASH;
        ui->backBtn->setEnabled(false);
    }

    ui->pathComboBox->removeItem(0);
    ui->pathComboBox->insertItem(0, targetPath);
    ui->fileNameLineEdit->setText(tr(""));

}

void BaseOpenFileDialog::do_filesTableView_current_row_changed(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if(m_currentFileList.at(current.row()).isFile()) {
        ui->fileNameLineEdit->setText(m_currentFileList.at(current.row()).baseName());
    } else {
        ui->fileNameLineEdit->setText(tr(""));
    }
}


void BaseOpenFileDialog::do_filesTasbleView_clicked(const QModelIndex &index)
{
    if(m_currentFileList.at(index.row()).isFile()) {
        ui->fileNameLineEdit->setText(m_currentFileList.at(index.row()).baseName());
    } else {

        QString baseName = m_currentFileList.at(index.row()).baseName();
        m_currentFileList = get_file_list(m_currentFileList.at(index.row()).absoluteFilePath());

        update_model();

        QString currentPath;

        if(ui->pathComboBox->currentText() == SLASH) {
            currentPath = ui->pathComboBox->currentText() + baseName;
        } else {
            currentPath = ui->pathComboBox->currentText() + SLASH + baseName;
        }

        ui->pathComboBox->removeItem(0);
        ui->pathComboBox->insertItem(0, currentPath);
        ui->backBtn->setEnabled(true);
    }
}


QFileInfoList BaseOpenFileDialog::get_file_list(const QString &path)
{
    QDir dir(path);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    return fileList;
}


void BaseOpenFileDialog::update_model()
{
    m_standardItemModel->clear();

    for(int i = 0; i < m_currentFileList.size(); ++i) {

        QList<QStandardItem*>   list;
        if(m_currentFileList.at(i).isDir()) {
            list << new QStandardItem(QIcon(":/resources/wizard/floder.png"),m_currentFileList.at(i).baseName());
        } else  {
            list << new QStandardItem(QIcon(":/resources/wizard/docs.png"), m_currentFileList.at(i).baseName());
        }

        m_standardItemModel->insertRow(i, list);
    }

    ui->filesTableView->setModel(m_standardItemModel);
    ui->filesTableView->setColumnWidth(0, 200);

    connect(ui->filesTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(do_filesTableView_current_row_changed(QModelIndex,QModelIndex)));

}

void BaseOpenFileDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {

         if(ui->backBtn->isEnabled()
                 && (ui->pathComboBox->currentText() != SLASH)) {
                on_backBtn_clicked();
         } else {
             on_cancleBtn_clicked();
         }

    } else if(event->key() == Qt::Key_Return) {

        if(ui->filesTableView->hasFocus()) {

            if(ui->filesTableView->currentIndex().row() < 0) {
                return;
            }

            if(m_currentFileList.at(ui->filesTableView->currentIndex().row()).isDir()) {
                do_filesTasbleView_clicked(ui->filesTableView->currentIndex());
            } else {
                close();
            }
        } else if(ui->openBtn->hasFocus()) {
            close();
        }
    }
}


void BaseOpenFileDialog::paintEvent(QPaintEvent *event)
{
    /* 圆角实现，并且需设置窗口背景透明 setAttribute(Qt::WA_TranslucentBackground); */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  /* 反锯齿; */
    painter.setBrush(QBrush(QColor(0, 100, 150)));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 8, 8);

    QWidget::paintEvent(event);
}
