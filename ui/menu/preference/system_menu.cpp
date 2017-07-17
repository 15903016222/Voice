/**
 * @file system_menu.cpp
 * @brief system menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "system_menu.h"
#include "label_menu_item.h"
#include "combo_menu_item.h"
#include "datetimesetdialog.h"
#include "resetconfigdialog.h"
#include "sysinfo_dialog.h"

#include <QDate>

namespace DplPreferenceMenu {

SystemMenu::SystemMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Date */
    m_dateItem.set(tr("Date"), QDate::currentDate().toString("yyyy-MM-dd"));
    connect(&m_dateItem, SIGNAL(clicked()), this, SLOT(show_date_dialog()));

    /* Time */
    m_timeItem.set(tr("Time"), QTime::currentTime().toString("hh:mm:ss"));
    connect(&m_timeItem, SIGNAL(clicked()), this, SLOT(show_time_dialog()));

    /* Cert Import menu item */
    QStringList m_list_certImport;
    m_list_certImport.append(tr("U-Disk"));
    m_list_certImport.append(tr("Network"));
    m_certItem.set(tr("Cert Import"), m_list_certImport);

    /* Update */
    m_updateItem.set(tr("Update"), "");

    /* Reset Configuration */
    m_resetCfgItem.set(tr("Reset Config"), "");
    connect(&m_resetCfgItem, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));

    /* System Information */
    m_infoItem.set(tr("System Info."), "");
    connect(&m_infoItem, SIGNAL(clicked()), this, SLOT(show_info_dialog()));

}

SystemMenu::~SystemMenu()
{
}

void SystemMenu::show()
{
    ui->layout0->addWidget(&m_timeItem);
    ui->layout1->addWidget(&m_dateItem);
    ui->layout2->addWidget(&m_certItem);
    ui->layout3->addWidget(&m_updateItem);
    ui->layout4->addWidget(&m_resetCfgItem);
    ui->layout5->addWidget(&m_infoItem);
    m_timeItem.show();
    m_dateItem.show();
    m_certItem.show();
    m_updateItem.show();
    m_resetCfgItem.show();
    m_infoItem.show();
}

void SystemMenu::hide()
{
    ui->layout0->removeWidget(&m_timeItem);
    ui->layout1->removeWidget(&m_dateItem);
    ui->layout2->removeWidget(&m_certItem);
    ui->layout3->removeWidget(&m_updateItem);
    ui->layout4->removeWidget(&m_resetCfgItem);
    ui->layout5->removeWidget(&m_infoItem);
    m_timeItem.hide();
    m_dateItem.hide();
    m_certItem.hide();
    m_updateItem.hide();
    m_resetCfgItem.hide();
    m_infoItem.hide();
}

void SystemMenu::show_time_dialog()
{
    DateTimeSetDialog *timeDialog = new DateTimeSetDialog;
    QMap<QString, QString> map;
    map.insert("Time Set", m_timeItem.get_title());
    QString str = m_timeItem.get_text();

    timeDialog->set_dialog_title(map);
    timeDialog->set_time_value(str);

    if (timeDialog->exec() == DateTimeSetDialog::Accepted) {
        m_timeItem.set_text(timeDialog->get_time());
    } else {
        m_timeItem.set_text(str);
    }
    delete timeDialog;
}

void SystemMenu::show_date_dialog()
{
    DateTimeSetDialog *dateDialog = new DateTimeSetDialog;
    QMap<QString, QString> map;
    map.insert("Date Set", m_dateItem.get_title());
    QString str = m_dateItem.get_text();

    dateDialog->set_dialog_title(map);
    dateDialog->set_date_value(str);

    if (dateDialog->exec() == DateTimeSetDialog::Accepted) {
        m_dateItem.set_text(dateDialog->get_date());
    } else {
        m_dateItem.set_text(str);
    }
    delete dateDialog;
}

void SystemMenu::show_resetconfig_dialog()
{
    ResetConfigDialog *resetConfigDialog = new ResetConfigDialog;
    resetConfigDialog->exec();
    delete resetConfigDialog;
}

void SystemMenu::show_info_dialog()
{
    Ui::Dialog::SysInfoDialog *infoDialog = new Ui::Dialog::SysInfoDialog;
    infoDialog->exec();
    delete infoDialog;
}

}
