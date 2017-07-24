#include "flaw_record_menu.h"
#include "ui_base_menu.h"

namespace DplMeasurementMenu {

FlawRecordMenu::FlawRecordMenu(QWidget *parent) :
    BaseMenu(parent),
    m_addDeleteItem(new LabelMenuItem(this, tr("Add/Delete"))),
    m_flawImageItem(new ComboMenuItem(this, tr("Flaw Image"))),
    m_commentItem(new LabelMenuItem(this, tr("Comment"))),
    m_displayTableItem(new LabelMenuItem(this, tr("Display Table"))),
    m_exportRecordItem(new LabelMenuItem(this, tr("Export Record")))

{
    ui->layout0->addWidget(m_addDeleteItem);
    ui->layout1->addWidget(m_flawImageItem);
    ui->layout2->addWidget(m_commentItem);
    ui->layout3->addWidget(m_displayTableItem);
    ui->layout4->addWidget(m_exportRecordItem);

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

}
