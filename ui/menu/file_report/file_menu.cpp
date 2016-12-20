#include "file_menu.h"
#include "label_menu_item.h"

namespace DplFileReportMenu {

FileMenu::FileMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Save Setup As Menu Item */
    m_saveSetupItem = new LabelMenuItem;
    m_saveSetupItem->set(tr("Save Setup As"), "");

    /* Open menu item */
    m_openItem = new LabelMenuItem;
    m_openItem->set(tr("Open"), "");

    /* File Manager menu item */
    m_fileManagerItem = new LabelMenuItem;
    m_fileManagerItem->set(tr("File Manager"), "");
    connect(m_fileManagerItem, SIGNAL(clicked()), this, SLOT(do_fileManagerItem_clicked()));
}

FileMenu::~FileMenu()
{
    delete m_saveSetupItem;
    delete m_openItem;
    delete m_fileManagerItem;
}

void FileMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_saveSetupItem);
    ui->menuItem1->layout()->addWidget(m_openItem);
    ui->menuItem2->layout()->addWidget(m_fileManagerItem);
    m_saveSetupItem->show();
    m_openItem->show();
    m_fileManagerItem->show();
}

void FileMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_saveSetupItem);
    ui->menuItem1->layout()->removeWidget(m_openItem);
    ui->menuItem2->layout()->removeWidget(m_fileManagerItem);
    m_saveSetupItem->hide();
    m_openItem->hide();
    m_fileManagerItem->hide();
}

void FileMenu::do_fileManagerItem_clicked()
{
//    FileManagerDialog fileManagerDialog;
//    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    fileManagerDialog.exec();
}

}
