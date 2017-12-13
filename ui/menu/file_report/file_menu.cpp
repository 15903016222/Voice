#include "file_menu.h"
#include <configuration/configuration.h>
#include <ui/dialog/dpl_message_box.h>
#include <ui/dialog/file_dialog.h>
#include "inputpanelcontext.h"
#include <limits.h>
#include <QDebug>

namespace DplFileReportMenu {

static const QString g_configFilePath("/opt/mercury/configs/usr/");
static const QString g_fileType(".cfg");

FileMenu::FileMenu(QWidget *parent) :
    BaseMenu(parent),
    m_saveSetupItem(new LabelMenuItem(this, tr("Save Setup"))),
    m_openItem(new LabelMenuItem(this, tr("Open"))),
    m_fileManagerItem(new LabelMenuItem(this, tr("File Manager")))
{
    m_layout0->addWidget(m_saveSetupItem);
    m_layout1->addWidget(m_openItem);
    m_layout2->addWidget(m_fileManagerItem);

    connect(m_fileManagerItem, SIGNAL(clicked()), this, SLOT(do_fileManagerItem_clicked()));
    connect(m_saveSetupItem, SIGNAL(clicked()), this, SLOT(do_saveSetupItem_clicked()));
    connect(m_openItem, SIGNAL(clicked()), this, SLOT(do_openItem_clicked()));
}

FileMenu::~FileMenu()
{
}

bool FileMenu::is_legal(const QString &name)
{
    if(name.right(g_fileType.length()) != g_fileType) {
        if(((name.length() + g_fileType.length()) > NAME_MAX)
            || ((g_configFilePath.length() + name.length() + g_fileType.length()) > PATH_MAX)) {
            return false;
        }
    } else {
        if((name.length() > NAME_MAX)
           || ((g_configFilePath.length() + name.length()) > PATH_MAX)) {
            return false;
        }
    }
    /* 只判断 \ / : * ? " < > 八种特殊字符 */
    QRegExp regExp(("[\\\\/:|*?\"<>]"));
    if(name.indexOf(regExp) >= 0) {
        return false;
    }

    return true;
}

void FileMenu::do_saveSetupItem_clicked()
{
    InputPanelContext inputPanel;

    while(inputPanel.exec() == QDialog::Accepted) {
        QString configFileName = inputPanel.get_text();
        if(is_legal(configFileName)) {
            if(configFileName.right(g_fileType.length()) != g_fileType) {
                configFileName = configFileName + g_fileType;
            }

            m_saveSetupItem->set_text(configFileName);

            configFileName = g_configFilePath + configFileName;

            Config::Configuration config;
            if(config.save_config(configFileName)) {
                DplMessageBox message(QMessageBox::Information, tr("Save Setup"), tr("Save Success!"));
                message.exec();
                return;

            } else {
                DplMessageBox message(QMessageBox::Warning, tr("Save Setup"), tr("Save Failed!"));
                message.exec();
            }
        } else if(configFileName.isEmpty()){
            DplMessageBox message(QMessageBox::Question, tr("Save Setup"), tr("Empty content, Reedit?"));
            if(message.exec() == QDialog::Accepted) {
                continue;
            }
            break;
        } else {
            DplMessageBox message(QMessageBox::Question, tr("Save Setup"), tr("Include unsupported character, Reedit?"));
            if(message.exec() == QDialog::Accepted) {
                continue;
            }
            break;
        }
    }

    m_saveSetupItem->set_text("");
}

void FileMenu::do_openItem_clicked()
{
    FileDialog::S_FileDialogParameters fileParam;

    fileParam.title            = tr("Open Setup");
    fileParam.filePath         = g_configFilePath;
    fileParam.nameFilters      << (tr("*") + g_fileType);
    fileParam.okButtonText     = tr("Open");
    fileParam.cancelButtonText = tr("Cancel");
    fileParam.operation        = FileDialog::Config;

    FileDialog configDialog(fileParam);
    if(configDialog.exec() == QDialog::Accepted) {
        Config::Configuration config;
        if(config.load_config(configDialog.get_selected_file_name())) {
            DplMessageBox messageBox(QMessageBox::Information, tr("Open Setup"), tr("Open Success!"));
            messageBox.exec();
        } else {
            DplMessageBox messageBox(QMessageBox::Warning, tr("Open Setup"), tr("Open Failed!"));
            messageBox.exec();
        }
    }
}

void FileMenu::do_fileManagerItem_clicked()
{
//    FileManagerDialog fileManagerDialog;
//    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    fileManagerDialog.exec();
}

}
