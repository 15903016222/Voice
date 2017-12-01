#include "file_menu.h"


namespace DplFileReportMenu {

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
}

FileMenu::~FileMenu()
{
}

void FileMenu::do_fileManagerItem_clicked()
{
//    FileManagerDialog fileManagerDialog;
//    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    fileManagerDialog.exec();
}

}
