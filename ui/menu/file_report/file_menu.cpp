#include "file_menu.h"
#include <configuration/configuration.h>
#include <ui/dialog/dpl_message_box.h>
#include <ui/dialog/file_dialog.h>
#include "inputpanelcontext.h"
#include <ui/menu/file_report/save_file_manager.h>
#include <limits.h>
#include <QDebug>
#include <QFile>

namespace DplFileReportMenu {

static const QString NUM_STR("###");

FileMenu::FileMenu(QWidget *parent) :
    BaseMenu(parent),

    m_openItem(new LabelMenuItem(this, tr("Open"))),
    m_storageItem(new ComboMenuItem(this, tr("Storage"))),
    m_saveModeItem(new ComboMenuItem(this, tr("Save Mode"))),
    m_saveDataItem(new LabelMenuItem(this, tr("Save Data"))),
    m_fileNameItem(new LabelMenuItem(this, tr("File Name"))),
    m_fileManagerItem(new LabelMenuItem(this, tr("File Manager"))),
    m_saveFileManager(new SaveFileManager(this))
{
    m_layout0->addWidget(m_openItem);
    m_layout1->addWidget(m_storageItem);
    m_layout2->addWidget(m_saveModeItem);
    m_layout3->addWidget(m_saveDataItem);
    m_layout4->addWidget(m_fileNameItem);
    m_layout5->addWidget(m_fileManagerItem);

    /* Storage Menu Item */
    QStringList storageList;
    storageList.append(tr("SD"));
    storageList.append(tr("SSD"));
    storageList.append(tr("U Storage"));
    m_storageItem->set(storageList);

    /* Save Mode menu item */
    m_saveModeNameList.append(tr("Inspection Data"));
    m_saveModeNameList.append(tr("Inspection Table"));
    m_saveModeNameList.append(tr("Screen"));
    m_saveModeNameList.append(tr("Report"));
    m_saveModeNameList.append(tr("Setup"));
    m_saveModeItem->set(m_saveModeNameList);

    connect(m_openItem, SIGNAL(clicked()), this, SLOT(do_openItem_clicked()));
    connect(m_saveModeItem, SIGNAL(value_changed(int)), this, SLOT(do_saveModeItem_value_changed(int)));
    connect(m_saveDataItem, SIGNAL(clicked()), this, SLOT(do_saveDataItem_clicked()));
    connect(m_fileNameItem, SIGNAL(clicked()), this, SLOT(do_fileNameItem_clicked()));
    connect(m_fileManagerItem, SIGNAL(clicked()), this, SLOT(do_fileManagerItem_clicked()));

    do_saveModeItem_value_changed(0);
}

FileMenu::~FileMenu()
{
}

void FileMenu::do_openItem_clicked()
{
    FileDialog::S_FileDialogParameters fileParam;

    fileParam.title            = tr("Open Setup");
    fileParam.filePath         = m_saveFileManager->get_file_path(m_storageItem->current_index(), m_saveModeItem->current_index());
    fileParam.nameFilters      = QStringList("*" + m_saveFileManager->get_file_suffix(m_saveModeItem->current_index()));
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

void FileMenu::do_saveModeItem_value_changed(int index)
{
    Q_UNUSED(index);
    m_fileNameItem->set_text(m_saveModeNameList.at(m_saveModeItem->current_index()) + NUM_STR);
}


void FileMenu::do_saveDataItem_clicked()
{
    QString fileName = m_fileNameItem->text().remove(NUM_STR);
    SaveFileManager::E_ResultType type = m_saveFileManager->save((SaveFileManager::E_SaveMode)m_saveModeItem->current_index(),
                                                                 (SaveFileManager::E_StorageType)m_storageItem->current_index(),
                                                                 fileName);

    if(type == SaveFileManager::Success) {
        DplMessageBox message(QMessageBox::Information, tr("Save ") + m_saveModeItem->current_text(), tr("Save Success!"));
        message.exec();
    } else if(type == SaveFileManager::InvalidName) {
        DplMessageBox message(QMessageBox::Warning, tr("Save"), tr("Include unsupported character, Please reedit"));
        message.exec();
    } else if(type == SaveFileManager::Failed) {
        DplMessageBox message(QMessageBox::Warning, tr("Save ") + m_saveModeItem->current_text(), tr("Save Failed!"));
        message.exec();
    }
}

void FileMenu::do_fileNameItem_clicked()
{
    InputPanelContext inputPanel;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->text().remove(NUM_STR);

    inputPanel.set_item_current_text(text);
    if (inputPanel.exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel.get_text() + NUM_STR);
        m_saveModeNameList.replace(m_saveModeItem->current_index(), inputPanel.get_text());
    } else {
        menu->set_text(text + NUM_STR);
    }
}


void FileMenu::do_fileManagerItem_clicked()
{
//    FileManagerDialog fileManagerDialog;
//    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //    fileManagerDialog.exec();
}

void FileMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_openItem->set_title(tr("Open"));
        m_storageItem->set_title(tr("Storage"));
        m_saveModeItem->set_title(tr("Save Mode"));
        m_saveDataItem->set_title(tr("Save Data"));
        m_fileNameItem->set_title(tr("File Name"));
        m_fileManagerItem->set_title(tr("File Manager"));

        return;
    }

    BaseMenu::changeEvent(e);
}

}
