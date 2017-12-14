/**
 * @file system_menu.cpp
 * @brief system menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "system_menu.h"

#include "datetimesetdialog.h"
#include "file_dialog.h"
#include "resetconfigdialog.h"
#include "sysinfo_dialog.h"
#include "dpl_message_box.h"
#include "base_dialog.h"
#include <device/device.h>
#include <configuration/configuration.h>

#include <time.h>
#include <sys/time.h>
#include <QMessageBox>
#include <QDateTime>
#include <QCalendarWidget>

namespace DplPreferenceMenu {


static const QString s_usbPath =  "/opt/usbStorage/";
static const QString s_fileType = "*.cert";

static const QString s_updatePath =  "/home/tt/TT/";
static const QString s_updateFileType = "*";
static const QString s_resetFile =  "/opt/mercury/configs/reset.cfg";

SystemMenu::SystemMenu(QWidget *parent) :
    BaseMenu(parent),
    m_dateItem(new LabelMenuItem(this, tr("Date"), QDate::currentDate().toString("yyyy-MM-dd"))),
    m_timeItem(new LabelMenuItem(this, tr("Time"), QTime::currentTime().toString("hh:mm:ss"))),
    m_certItem(new LabelMenuItem(this, tr("Cert Import"))),
    m_updateItem(new LabelMenuItem(this, tr("Update"))),
    m_resetCfgItem(new LabelMenuItem(this, tr("Reset"))),
    m_infoItem(new LabelMenuItem(this, tr("Infomation"))),
    m_timer(new QTimer(this))
{
    m_layout0->addWidget(m_timeItem);
    m_layout1->addWidget(m_dateItem);
    m_layout2->addWidget(m_certItem);
    m_layout3->addWidget(m_updateItem);
    m_layout4->addWidget(m_resetCfgItem);
    m_layout5->addWidget(m_infoItem);

    /* Date */
    connect(m_dateItem, SIGNAL(clicked()), this, SLOT(show_date_dialog()));

    /* Time */
    connect(m_timeItem, SIGNAL(clicked()), this, SLOT(show_time_dialog()));

    /* Cert Import */
    connect(m_certItem, SIGNAL(clicked()), this, SLOT(show_cert_import_dialog()));

    /* Update */
    connect(m_updateItem, SIGNAL(clicked()), this, SLOT(show_update_dialog()));

    /* Reset Configuration */
    connect(m_resetCfgItem, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));

    /* System Information */
    connect(m_infoItem, SIGNAL(clicked()), this, SLOT(show_info_dialog()));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_time_out()));

    init_date_time();
    m_timer->start(1000);

}

SystemMenu::~SystemMenu()
{
}

void SystemMenu::show_time_dialog()
{
    DateTimeSetDialog timeDialog;
    QMap<QString, QString> map;
    map.insert("Time Set", m_timeItem->title());

    timeDialog.set_dialog_title(map);
    timeDialog.set_time_value(m_timeItem->text());

    if (timeDialog.exec() == DateTimeSetDialog::Accepted) {
        QDateTime dateTime = QDateTime::fromString(m_dateItem->text() + tr(" ") + timeDialog.get_time(), "yyyy-MM-dd hh:mm:ss");
        if(set_date_time(dateTime)) {
            m_timeItem->set_text(timeDialog.get_time());
            DplMessageBox messageBox(QMessageBox::Information, tr("Info"), tr("Done!"));
            messageBox.exec();
        } else {
            DplMessageBox messageBox(QMessageBox::Information, tr("Warning"), tr("Failed!"));
            messageBox.exec();
        }
    }
}

void SystemMenu::show_date_dialog()
{
    DateTimeSetDialog dateDialog;
    QMap<QString, QString> map;
    map.insert("Date Set", m_dateItem->title());

    dateDialog.set_dialog_title(map);
    dateDialog.set_date_value(m_dateItem->text());

    if (dateDialog.exec() == DateTimeSetDialog::Accepted) {
        uint currentDate = DplDevice::Device::instance()->date_time();
        QDateTime cruuentDateTime = QDateTime::fromTime_t(currentDate);
        QString dateTimeString = dateDialog.get_date() + tr(" ") + cruuentDateTime.toString("hh:mm:ss:zzz");
        QDateTime dateTime = QDateTime::fromString(dateTimeString, "yyyy-MM-dd hh:mm:ss:zzz");
        if(set_date_time(dateTime)) {
            m_dateItem->set_text(dateDialog.get_date());
            DplMessageBox messageBox(QMessageBox::Information, tr("Info"), tr("Done!"));
            messageBox.exec();
        } else {
            DplMessageBox messageBox(QMessageBox::Information, tr("Warning"), tr("Failed!"));
            messageBox.exec();
        }
    }
}

void SystemMenu::show_cert_import_dialog()
{
    FileDialog::S_FileDialogParameters parameters;
    parameters.title            = tr("Cert Import");
    parameters.filePath         = s_usbPath;
    parameters.nameFilters      = QStringList(s_fileType);
    parameters.okButtonText     = tr("Import");
    parameters.cancelButtonText = tr("Cancel");
    parameters.operation        = FileDialog::CertImport;

    FileDialog importDialog(parameters);
    if(importDialog.exec() == QDialog::Accepted) {
        if(DplDevice::Device::instance()->import_cert(importDialog.get_selected_file_name())) {
            DplMessageBox messageBox(QMessageBox::Information, tr("Import"), tr("Done!"));
            messageBox.exec();
        } else {
            DplMessageBox messageBox(QMessageBox::Warning, tr("Warning"), tr("Failed!"));
            messageBox.exec();
        }
    }
}

void SystemMenu::show_update_dialog()
{
    FileDialog::S_FileDialogParameters parameters;
    parameters.title            = tr("Update");
    parameters.filePath         = s_updatePath;
    parameters.nameFilters      = QStringList(s_updateFileType);
    parameters.okButtonText     = tr("Update");
    parameters.cancelButtonText = tr("Cancel");
    parameters.operation        = FileDialog::Update;

    FileDialog importDialog(parameters);
    if(importDialog.exec() == QDialog::Accepted) {
        if(importDialog.get_file_type() == FileDialog::FPGA) {
            /* TODO: */
        } else if(importDialog.get_file_type() == FileDialog::System) {
            /* TODO: */
        }
    }
}

void SystemMenu::show_resetconfig_dialog()
{
    DplMessageBox messageBox(QMessageBox::Question, tr("Reset"), tr("Reset Config ?"));
    if(messageBox.exec() == QDialog::Accepted) {
        Config::Configuration config;
        if(config.load_config(s_resetFile)) {
            DplMessageBox messageBox(QMessageBox::Information, tr("Reset"), tr("Reset Success!"));
            messageBox.exec();
        } else {
            DplMessageBox messageBox(QMessageBox::Warning, tr("Reset"), tr("Reset Failed!"));
            messageBox.exec();
        }
    }
}

void SystemMenu::show_info_dialog()
{
    SysInfoDialog infoDialog;
    infoDialog.exec();
}

void SystemMenu::do_time_out()
{
    time_t dateTime = DplDevice::Device::instance()->date_time();
    QDateTime currentDateTime = QDateTime::fromTime_t(dateTime);
    m_timeItem->set_text(currentDateTime.toString("hh:mm:ss"));
}

bool SystemMenu::set_date_time(const QDateTime &dateTime)
{
    if(DplDevice::Device::instance()->set_date_time(dateTime)) {
        return true;
    } else {
        return false;
    }
}

void SystemMenu::init_date_time()
{
    time_t dateTime = DplDevice::Device::instance()->date_time();
    QDateTime currentDateTime = QDateTime::fromTime_t(dateTime);
    m_dateItem->set_text(currentDateTime.toString("yyyy-MM-dd"));
    m_timeItem->set_text(currentDateTime.toString("hh:mm:ss"));
}

}
