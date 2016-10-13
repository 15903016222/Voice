#include "systeminfodialog.h"
#include "ui_systeminfodialog.h"

#include <QFile>
#include <QDebug>

#ifndef MY_FILE_NAME
#define MY_FILE_NAME ":/file/resources/systeminfo.txt"
#endif

SystemInfoDialog::SystemInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemInfoDialog)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setColumnWidth(0, 250);
    read_textFile();
}

SystemInfoDialog::~SystemInfoDialog()
{
    delete ui;
}

void SystemInfoDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void SystemInfoDialog::read_textFile()
{
    QFile file(MY_FILE_NAME);
    if ( !file.open(QIODevice::ReadOnly) ) {
        qDebug()<<"error read in concreate!";
    }  else {
        int rownum = 0;
        while(!file.atEnd()) {
            QByteArray line = file.readLine();
            QString str(line);
            ui->tableWidget->setItem(rownum ,0, new QTableWidgetItem(str));
            rownum++;
        }
    }
    file.close();
}
