#include "file_menu.h"
#include "label_menu_item.h"

namespace DplFileReportMenu {

FileMenu::FileMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Save Setup As Menu Item */
    m_saveSetupItem.set(tr("Save Setup As"), "");

    /* Open menu item */
    m_openItem.set(tr("Open"), "");

    /* File Manager menu item */
    m_fileManagerItem.set(tr("File Manager"), "");
    connect(&m_fileManagerItem, SIGNAL(clicked()), this, SLOT(do_fileManagerItem_clicked()));
}

FileMenu::~FileMenu()
{
}

void FileMenu::show()
{
    ui->layout0->addWidget(&m_saveSetupItem);
    ui->layout1->addWidget(&m_openItem);
    ui->layout2->addWidget(&m_fileManagerItem);
    m_saveSetupItem.show();
    m_openItem.show();
    m_fileManagerItem.show();
}

void FileMenu::hide()
{
    ui->layout0->removeWidget(&m_saveSetupItem);
    ui->layout1->removeWidget(&m_openItem);
    ui->layout2->removeWidget(&m_fileManagerItem);
    m_saveSetupItem.hide();
    m_openItem.hide();
    m_fileManagerItem.hide();
}

void FileMenu::do_fileManagerItem_clicked()
{
//    FileManagerDialog fileManagerDialog;
//    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    fileManagerDialog.exec();
}

}
