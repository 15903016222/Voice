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
    ui->layout0->addWidget(&m_selectItem);
    ui->layout1->addWidget(&m_enableItem);
    ui->layout2->addWidget(&m_labelItem);
    ui->layout3->addWidget(&m_contentItem);
    ui->layout4->addWidget(&m_editNoteItem);
    ui->layout5->addWidget(&m_printItem);
    m_selectItem.show();
    m_enableItem.show();
    m_labelItem.show();
    m_contentItem.show();
    m_editNoteItem.show();
    m_printItem.show();
}

void UserFieldMenu::hide()
{
    ui->layout0->removeWidget(&m_selectItem);
    ui->layout1->removeWidget(&m_enableItem);
    ui->layout2->removeWidget(&m_labelItem);
    ui->layout3->removeWidget(&m_contentItem);
    ui->layout4->removeWidget(&m_editNoteItem);
    ui->layout5->removeWidget(&m_printItem);
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
