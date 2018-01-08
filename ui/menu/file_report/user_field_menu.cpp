#include "user_field_menu.h"

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
    m_layout0->addWidget(m_selectItem);
    m_layout1->addWidget(m_enableItem);
    m_layout2->addWidget(m_labelItem);
    m_layout3->addWidget(m_contentItem);
    m_layout4->addWidget(m_editNoteItem);
    m_layout5->addWidget(m_printItem);

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

void UserFieldMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_selectItem->set_title(tr("Select"));
        m_enableItem->set_title(tr("Enable"));
        m_labelItem->set_title(tr("Label"));
        m_contentItem->set_title(tr("Content"));
        m_editNoteItem->set_title(tr("Edit Note"));
        m_printItem->set_title(tr("Print"));

        s_onOff.clear();
        s_onOff << tr("On") << tr("Off");
        m_enableItem->retranslate_items(s_onOff);

        return;
    }
    BaseMenu::changeEvent(e);
}

}
