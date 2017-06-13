#include "user_field_menu.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"
#include "inputpanelcontext.h"

namespace DplFileReportMenu {

UserFieldMenu::UserFieldMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Select Menu Item */   
    QStringList selectList;
    selectList << "1"
               << "2"
               << "3"
               << "4"
               << "5"
               << "6"
               << "7"
               << "8"
               << "9"
               << "10";
    m_selectItem.set(tr("Select"), selectList);

    /* Enable menu item */
    m_enableItem.set(tr("Enable"), s_onOff);

    /* Label menu item */
    m_labelItem.set(tr("Label"), "");
    connect(&m_labelItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Content Menu Item */
    m_contentItem.set(tr("Content"), "");
    connect(&m_contentItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Edit Note Number item */
    m_editNoteItem.set(tr("Edit Note"), "");
    connect(&m_editNoteItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Print menu item */
    m_printItem.set(tr("Print"), "");
}

UserFieldMenu::~UserFieldMenu()
{
}

void UserFieldMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_selectItem);
    ui->menuItem1->layout()->addWidget(&m_enableItem);
    ui->menuItem2->layout()->addWidget(&m_labelItem);
    ui->menuItem3->layout()->addWidget(&m_contentItem);
    ui->menuItem4->layout()->addWidget(&m_editNoteItem);
    ui->menuItem5->layout()->addWidget(&m_printItem);
    m_selectItem.show();
    m_enableItem.show();
    m_labelItem.show();
    m_contentItem.show();
    m_editNoteItem.show();
    m_printItem.show();
}

void UserFieldMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_selectItem);
    ui->menuItem1->layout()->removeWidget(&m_enableItem);
    ui->menuItem2->layout()->removeWidget(&m_labelItem);
    ui->menuItem3->layout()->removeWidget(&m_contentItem);
    ui->menuItem4->layout()->removeWidget(&m_editNoteItem);
    ui->menuItem5->layout()->removeWidget(&m_printItem);
    m_selectItem.hide();
    m_enableItem.hide();
    m_labelItem.hide();
    m_contentItem.hide();
    m_editNoteItem.hide();
    m_printItem.hide();
}

void UserFieldMenu::show_input_dialog()
{
    InputPanelContext *inputPanel = new InputPanelContext;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->get_text();

    inputPanel->set_item_current_text(text);
    if (inputPanel->exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel->get_text());
    } else {
        menu->set_text(text);
    }
    delete inputPanel;
}

}
