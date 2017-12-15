#include "file_menu.h"
#include "inputpanelcontext.h"

namespace DplFileReportMenu {

FileMenu::FileMenu(QWidget *parent) :
    BaseMenu(parent),
    m_openItem(new LabelMenuItem(this, tr("Open"))),
    m_storageItem(new ComboMenuItem(this, tr("Storage"))),
    m_saveModeItem(new ComboMenuItem(this, tr("Save Mode"))),
    m_saveDataItem(new LabelMenuItem(this, tr("Save Data"))),
    m_fileNameItem(new LabelMenuItem(this, tr("File Name"))),
    m_fileManagerItem(new LabelMenuItem(this, tr("File Manager")))

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
    QStringList saveModeList;
    saveModeList.append(tr("Inspection Data"));
    saveModeList.append(tr("Inspection Table"));
    saveModeList.append(tr("Screen"));
    saveModeList.append(tr("Report"));
    saveModeList.append(tr("Setup"));
    m_saveModeItem->set(saveModeList);

    connect(m_fileNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
    connect(m_fileManagerItem, SIGNAL(clicked()), this, SLOT(do_fileManagerItem_clicked()));
    connect(m_saveModeItem, SIGNAL(value_changed(int)), this, SLOT(do_saveModeItem_value_changed(int)));
    connect(m_saveDataItem, SIGNAL(clicked()), this, SLOT(do_saveDataItem_clicked()));

    do_saveModeItem_value_changed(0);
}

FileMenu::~FileMenu()
{
}

void FileMenu::show_input_dialog()
{
    InputPanelContext *inputPanel = new InputPanelContext;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->text().remove(tr("###"));

    inputPanel->set_item_current_text(text);
    if (inputPanel->exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel->get_text() + tr("###"));
    } else {
        menu->set_text(text + tr("###"));
    }

    delete inputPanel;
}

void FileMenu::do_fileManagerItem_clicked()
{
//    FileManagerDialog fileManagerDialog;
//    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    fileManagerDialog.exec();
}

void FileMenu::do_saveModeItem_value_changed(int index)
{
    Q_UNUSED(index);
    m_fileNameItem->set_text(m_saveModeItem->current_text() + tr("###"));
}

void FileMenu::do_saveDataItem_clicked()
{

}


}
