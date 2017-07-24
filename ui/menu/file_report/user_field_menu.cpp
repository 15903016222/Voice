#include "user_field_menu.h"
#include "ui_base_menu.h"
#include "inputpanelcontext.h"

namespace DplFileReportMenu {

UserFieldMenu::UserFieldMenu(QWidget *parent) :
    BaseMenu(parent),
    m_selectItem(new ComboMenuItem(this, tr("Select"))),
    m_enableItem(new ComboMenuItem(this, tr("Enable"))),
    m_labelItem(new LabelMenuItem(this, tr("Label"))),
    m_contentItem(new LabelMenuItem(this, tr("Content"))),
    m_editNoteItem(new LabelMenuItem(this, tr("Edit Note"))),
    m_printItem(new LabelMenuItem(this, tr("Print")))
{
    ui->layout0->addWidget(m_selectItem);
    ui->layout1->addWidget(m_enableItem);
    ui->layout2->addWidget(m_labelItem);
    ui->layout3->addWidget(m_contentItem);
    ui->layout4->addWidget(m_editNoteItem);
    ui->layout5->addWidget(m_printItem);

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
    m_selectItem->set(selectList);

    /* Enable menu item */
    m_enableItem->set(s_onOff);

    connect(m_labelItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    connect(m_contentItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    connect(m_editNoteItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
}

UserFieldMenu::~UserFieldMenu()
{
}

void UserFieldMenu::show_input_dialog()
{
    InputPanelContext inputPanel;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->text();

    inputPanel.set_item_current_text(text);
    if (inputPanel.exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel.get_text());
    } else {
        menu->set_text(text);
    }
}

}
