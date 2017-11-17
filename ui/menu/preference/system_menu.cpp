/**
 * @file system_menu.cpp
 * @brief system menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "system_menu.h"
#include "ui_base_menu.h"
#include "datetimesetdialog.h"
#include "resetconfigdialog.h"
#include "sysinfo_dialog.h"

#include <QDate>

namespace DplPreferenceMenu {

SystemMenu::SystemMenu(QWidget *parent) :
    BaseMenu(parent),
    m_dateItem(new LabelMenuItem(this, tr("Date"), QDate::currentDate().toString("yyyy-MM-dd"))),
    m_timeItem(new LabelMenuItem(this, tr("Time"), QTime::currentTime().toString("hh:mm:ss"))),
    m_certItem(new LabelMenuItem(this, tr("Cert Import"))),
    m_updateItem(new LabelMenuItem(this, tr("Update"))),
    m_resetCfgItem(new LabelMenuItem(this, tr("Reset"))),
    m_infoItem(new LabelMenuItem(this, tr("Infomation")))
{
    ui->layout0->addWidget(m_timeItem);
    ui->layout1->addWidget(m_dateItem);
    ui->layout2->addWidget(m_certItem);
    ui->layout3->addWidget(m_updateItem);
    ui->layout4->addWidget(m_resetCfgItem);
    ui->layout5->addWidget(m_infoItem);

    /* Date */
    connect(m_dateItem, SIGNAL(clicked()), this, SLOT(show_date_dialog()));

    /* Time */
    connect(m_timeItem, SIGNAL(clicked()), this, SLOT(show_time_dialog()));


    /* Reset Configuration */
    connect(m_resetCfgItem, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));

    /* System Information */
    connect(m_infoItem, SIGNAL(clicked()), this, SLOT(show_info_dialog()));
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
        m_timeItem->set_text(timeDialog.get_time());
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
        m_dateItem->set_text(dateDialog.get_date());
    }
}

void SystemMenu::show_resetconfig_dialog()
{
    ResetConfigDialog resetConfigDialog;
    resetConfigDialog.exec();
}

void SystemMenu::show_info_dialog()
{
    Ui::Dialog::SysInfoDialog infoDialog;
    infoDialog.exec();
    this->set_focus();
}

}
