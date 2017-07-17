#include "flaw_record_menu.h"
#include "label_menu_item.h"
#include "combo_menu_item.h"

namespace DplMeasurementMenu {

FlawRecordMenu::FlawRecordMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Add/Delete Menu Item */
    m_addDeleteItem.set(tr("Add/Delete"), "");

    /* Flaw Image menu item */
    m_flawImageItem.set(tr("Flaw Image"), s_onOff);

    /* Comment menu item */
    m_commentItem.set(tr("Comment"), "");
    connect(&m_commentItem, SIGNAL(clicked()), this, SLOT(do_comment_clicked()));

    /* Display Table Menu Item */
    m_displayTableItem.set(tr("Display Table"), s_onOff);

    /* Export Record Menu Item */
    m_exportRecordItem.set(tr("Export Record"), "");

}

FlawRecordMenu::~FlawRecordMenu()
{
}

void FlawRecordMenu::show()
{
    ui->layout0->addWidget(&m_addDeleteItem);
    ui->layout1->addWidget(&m_flawImageItem);
    ui->layout2->addWidget(&m_commentItem);
    ui->layout3->addWidget(&m_displayTableItem);
    ui->layout4->addWidget(&m_exportRecordItem);
    m_addDeleteItem.show();
    m_flawImageItem.show();
    m_commentItem.show();
    m_displayTableItem.show();
    m_exportRecordItem.show();
}

void FlawRecordMenu::hide()
{
    ui->layout0->removeWidget(&m_addDeleteItem);
    ui->layout1->removeWidget(&m_flawImageItem);
    ui->layout2->removeWidget(&m_commentItem);
    ui->layout3->removeWidget(&m_displayTableItem);
    ui->layout4->removeWidget(&m_exportRecordItem);
    m_addDeleteItem.hide();
    m_flawImageItem.hide();
    m_commentItem.hide();
    m_displayTableItem.hide();
    m_exportRecordItem.hide();
}

void FlawRecordMenu::do_comment_clicked()
{
    //    InputPanelContext inputPanel;
    //    MenuItem *widget = qobject_cast<MenuItem*>(sender());
    //    inputPanel.set_item_current_text(widget->get_label_text());
    //    inputPanel.exec();
    //    widget->set_label_text(inputPanel.get_text());
}

}
