#include "flaw_record_menu.h"


namespace DplMeasurementMenu {

FlawRecordMenu::FlawRecordMenu(QWidget *parent) :
    BaseMenu(parent),
    m_addDeleteItem(new LabelMenuItem(this, tr("Add/Delete"))),
    m_flawImageItem(new ComboMenuItem(this, tr("Flaw Image"))),
    m_commentItem(new LabelMenuItem(this, tr("Comment"))),
    m_displayTableItem(new LabelMenuItem(this, tr("Display Table"))),
    m_exportRecordItem(new LabelMenuItem(this, tr("Export Record")))

{
    m_layout0->addWidget(m_addDeleteItem);
    m_layout1->addWidget(m_flawImageItem);
    m_layout2->addWidget(m_commentItem);
    m_layout3->addWidget(m_displayTableItem);
    m_layout4->addWidget(m_exportRecordItem);

    /* Flaw Image menu item */
    m_flawImageItem->set(s_onOff);

    /* Comment menu item */
    connect(m_commentItem, SIGNAL(clicked()),
            this, SLOT(do_commentItem_clicked()));
}

FlawRecordMenu::~FlawRecordMenu()
{
}

void FlawRecordMenu::do_commentItem_clicked()
{
    //    InputPanelContext inputPanel;
    //    MenuItem *widget = qobject_cast<MenuItem*>(sender());
    //    inputPanel.set_item_current_text(widget->get_label_text());
    //    inputPanel.exec();
    //    widget->set_label_text(inputPanel.get_text());
}

void FlawRecordMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_addDeleteItem->set_title(tr("Add/Delete"));
        m_flawImageItem->set_title(tr("Flaw Image"));
        m_commentItem->set_title(tr("Comment"));
        m_displayTableItem->set_title(tr("Display Table"));
        m_exportRecordItem->set_title(tr("Export Record"));

        return;
    }

    BaseMenu::changeEvent(e);
}

}
